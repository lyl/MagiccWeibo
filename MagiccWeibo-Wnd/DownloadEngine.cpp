#include "StdAfx.h"
#include "DownloadEngine.h"
#include <process.h>
#include <WinSock2.h>

#define SLEEP_MS 50
typedef unsigned(__stdcall *THREAD_START_ROUTINE)(void*);

CDownloadEngine::CDownloadEngine(void)
:m_shutdown(false),
m_thread(0),
m_threadId(0)
{
	curl_global_init(CURL_GLOBAL_ALL);
}

CDownloadEngine::~CDownloadEngine(void)
{
	curl_global_cleanup();
	if (m_thread)
	{
		CloseHandle(m_thread);
	}
}

void * __stdcall CDownloadEngine::Wrapper( void *param )
{
	CDownloadEngine *pEngine = static_cast<CDownloadEngine*>(param);
	assert(pEngine);
	pEngine->ThreadProc();
	return 0;
}


void CDownloadEngine::Run()
{
	m_thread =(HANDLE) _beginthreadex(NULL,0,THREAD_START_ROUTINE(CDownloadEngine::Wrapper),this,0,&m_threadId);
}

void CDownloadEngine::Shutdown()
{
	Util::Lock lock(m_shutdownMutex);
	if (!m_shutdown)
	{
		m_shutdown = true;
	}
}

bool CDownloadEngine::IsShutdown() const
{
	Util::Lock lock(m_shutdownMutex);

	return m_shutdown;
}

bool CDownloadEngine::IsRunning() const
{
	DWORD exitCode;
	BOOL retn = GetExitCodeThread(m_thread,&exitCode);
	if (retn != -0 && exitCode == STILL_ACTIVE && m_thread)
		return true;

	return false;
}

void CDownloadEngine::ThreadProc()
{
	CURLM *multi_curl = curl_multi_init();
	if (!multi_curl)
	{
		return;
	}

	while (!IsShutdown())
	{
		ScanPrepareTaskList();
		
		int still_running = 0;
		curl_multi_perform(multi_curl,&still_running);

		bool bHasHandle = ScanRunningTaskList(multi_curl);

		if (!bHasHandle)
		{
			::Sleep(SLEEP_MS);
			continue;
		}

		PerformMutliCurl(multi_curl,bHasHandle);

		DispatchTaskStatus(multi_curl);
	}
	
	TaskListClearnUp(multi_curl);
	curl_multi_cleanup(multi_curl);
}

void CDownloadEngine::AddTask( HttpTaskPtr ptr )
{
	Util::Lock lock(m_queneMutex);
	m_prepareTaskList.push_back(ptr);
}

void CDownloadEngine::ScanPrepareTaskList()
{
	HttpTaskPtr ptr;
	{
		Util::Lock lock(m_queneMutex);
		if (!m_prepareTaskList.empty())
		{
			ptr = m_prepareTaskList.front();
			m_prepareTaskList.pop_front();
		}
	}
	if (ptr)
	{
		m_runningTaskList.push_back(ptr);
	}
}

bool CDownloadEngine::ScanRunningTaskList( CURLM *multi_curl )
{
	if (!multi_curl)
	{
		return false;
	}

	if (m_runningTaskList.empty())
	{
		return false;
	}
	
	bool bHasHandle = false;

	HttpTaskList::iterator itor = m_runningTaskList.begin();
	while (itor != m_runningTaskList.end())
	{
		bool bNeedRelease = false;

		switch ((*itor)->GetStatus())
		{
		case TASK_STATUS_START:
			{
				if ((*itor)->GetCurl() == NULL)
				{
					(*itor)->InitTask();
					CURLMcode res = curl_multi_add_handle(multi_curl,(*itor)->GetCurl());
					if (res == CURLM_OK)
					{
						(*itor)->OnStart();
					}
					else
					{
						(*itor)->SetStatus(TASK_STATUS_ERROR);
					}
				}
			}
			break;
		case TASK_STATUS_ERROR:
			{
				bNeedRelease = true;
				(*itor)->OnError();
			}
			break;
		case TASK_STATUS_COMPLETE:
			{
				bNeedRelease = true;
				(*itor)->OnComplete();
			}
			break;
		default:
			break;
		}
		if (bNeedRelease)
		{
			curl_multi_remove_handle(multi_curl,(*itor)->GetCurl());
			(*itor)->UnInitTask();

			m_runningTaskList.erase(itor ++);

			continue;
		}

		itor ++;
		bHasHandle = true;
	}

	return bHasHandle;
}

bool CDownloadEngine::PerformMutliCurl( CURLM *multi_curl,bool &bHasHandle )
{
	if (!bHasHandle)
	{
		return false;
	}

	if (!multi_curl)
	{
		return false;
	}

	int still_running = 0;

	/* we start some action by calling perform right away */ 
	CURLMcode code = curl_multi_perform(multi_curl, &still_running);

	if/*while*/(still_running /*&& !isShutdown()*/) 
	{
		struct timeval timeout;
		int rc; /* select() return code */ 

		fd_set fdread;
		fd_set fdwrite;
		fd_set fdexcep;
		int maxfd = -1;

		long curl_timeo = -1;

		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexcep);

		/* set a suitable timeout to play around with */ 
		timeout.tv_sec = 0;
		timeout.tv_usec = SLEEP_MS * 1000;

		curl_multi_timeout(multi_curl, &curl_timeo);
		if(curl_timeo >= 0 && curl_timeo < SLEEP_MS)
		{
			timeout.tv_usec = curl_timeo * 1000;
		}

		/* get file descriptors from the transfers */ 
		curl_multi_fdset(multi_curl, &fdread, &fdwrite, &fdexcep, &maxfd);

		/* In a real-world program you OF COURSE check the return code of the
		function calls.  On success, the value of maxfd is guaranteed to be
		greater or equal than -1.  We call select(maxfd + 1, ...), specially in
		case of (maxfd == -1), we call select(0, ...), which is basically equal
		to sleep. */ 

		rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

		//
		switch(rc) 
		{
		case -1:
			{
				/* select error */ 
				::Sleep(SLEEP_MS);
			}
			break;
		case 0: /* timeout */
		default: /* action */ 
			curl_multi_perform(multi_curl, &still_running);
			break;
		}
		return true;
	}
	return false;

}

void CDownloadEngine::DispatchTaskStatus( CURLM *multi_curl )
{
	int msgs_left = 0;
	CURLMsg* msg = NULL;
	while((msg = curl_multi_info_read(multi_curl, &msgs_left))) 
	{
		HttpTaskList::iterator itor = m_runningTaskList.begin();
		while( itor != m_runningTaskList.end()) 
		{
			if ((*itor)->GetCurl() == msg->easy_handle
				&& (*itor)->GetStatus() == TASK_STATUS_START
				&& msg->msg == CURLMSG_DONE) 
			{
				(*itor)->SetStatus((CURLE_OK == msg->data.result) ? TASK_STATUS_COMPLETE : TASK_STATUS_ERROR);
			}
			itor ++;
		}
	}
}

void CDownloadEngine::TaskListClearnUp( CURLM *multi_curl )
{
	if (!multi_curl)
	{
		return;
	}

	HttpTaskList::iterator itor = m_runningTaskList.begin();
	while (itor != m_runningTaskList.end())
	{
		if ((*itor)->GetCurl() != NULL)
		{
			curl_multi_remove_handle(multi_curl,(*itor)->GetCurl());
			(*itor)->UnInitTask();
		}
		itor ++;
	}

	m_runningTaskList.clear();
}

