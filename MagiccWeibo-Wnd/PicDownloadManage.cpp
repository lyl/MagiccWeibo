#include "StdAfx.h"
#include "PicDownloadManage.h"

using namespace std::tr1::placeholders;

static CPicDownloadManage* m_pInstace = NULL;

CPicDownloadManage::CPicDownloadManage(void)
{
}

CPicDownloadManage::~CPicDownloadManage(void)
{
}

bool CPicDownloadManage::StartUp()
{
	m_downloadEngine = new CDownloadEngine;
	m_downloadEngine->Run();	

	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa,sizeof(SECURITY_ATTRIBUTES));
	m_taskMutex = ::CreateMutex(&sa,false,_T("TaskMutex"));
	srand((unsigned int)time(NULL));
	return true;
}

bool CPicDownloadManage::ShutDown()
{
	m_downloadEngine->Shutdown();
	CloseHandle(m_taskMutex);
	return true;
}
// 
// void  CPicDownloadManage::SetPicName( string name )
// {
// 	m_strPicName = name;
// }
// 
// size_t CPicDownloadManage::WriteFun( void *ptr, size_t size, size_t nmemb, void *data )
// {
// 	FILE *fp = (FILE*)data;
// 	if (fp && size > 0)
// 	{
// 		int written = fwrite(ptr,size,nmemb,fp);
// 		return written;
// 	}
// 	return size * nmemb;
// }
// 
// bool  CPicDownloadManage::DownloadPic( string &strUrl )
// {
// 	FILE *fp = fopen(m_strPicName.c_str(),"wb");
// 	if (!fp)
// 	{
// 		return false;
// 	}
// 	m_pCurl = curl_easy_init();
// 	if (NULL == m_pCurl)
// 	{
// 		curl_global_cleanup();
// 		return false;
// 	}
// 	curl_easy_setopt(m_pCurl,CURLOPT_URL,strUrl.c_str());
// 	curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,&CPicDownloadManage::WriteFun);
// 	curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,fp);
// 	curl_easy_setopt(m_pCurl,CURLOPT_TIMEOUT,5);
// 
// 	CURLcode retn = curl_easy_perform(m_pCurl);
// 	if (retn != CURLE_OK)
// 	{
// 		curl_easy_cleanup(m_pCurl);
// 		fclose(fp);
// 		return false;
// 	}
// 	curl_easy_cleanup(m_pCurl);
// 	fclose(fp);
// 
// 	return true;
// 
// }



void CPicDownloadManage::AddDownloadTask( string strPicName,string strUrl,CControlUI *pControl )
{
	WaitForSingleObject(m_taskMutex,INFINITE);
	static int count = 0;
	int key = rand();

#ifdef _DEBUG
	CDuiString str;
	str.Format(_T("下载任务：%d,key : %d\n"),++ count,key);
	OutputDebugString(str);
#endif	

	HttpTaskPtr task(new CDownloadPicTask(strUrl,key,strPicName));
	task->CompleteCallback = std::tr1::bind(&CPicDownloadManage::TaskComplete,this,_1);
	task->SetData(pControl);
	m_taskList.insert(std::make_pair(key,task));

#ifdef _DEBUG
	str.Format(_T("任务列表个数：%d\n"),m_taskList.size());
	OutputDebugString(str);
#endif

	m_downloadEngine->AddTask(task);
	ReleaseMutex(m_taskMutex);
}

void CPicDownloadManage::TaskComplete( int key )
{
	WaitForSingleObject(m_taskMutex,INFINITE);

	std::map<int,HttpTaskPtr>::iterator itor = m_taskList.find(key);
	if (itor != m_taskList.end())
	{
		std::tr1::shared_ptr<CDownloadPicTask> pDownPicTask = dynamic_pointer_cast<CDownloadPicTask>(itor->second);
		if (pDownPicTask)
		{
			CControlUI *pControl =(CControlUI *) pDownPicTask->GetData();
			string strPicPath = pDownPicTask->GetPicPath();
			int pos = strPicPath.rfind("Temp");
		
			if (pos != -1)
			{
				int length = strPicPath.length();
				string subStr = strPicPath.substr(pos,length - pos);
				USES_CONVERSION;
				pControl->SetBkImage(A2W(subStr.c_str()));
			}
		}
		m_taskList.erase(itor);
	}
	ReleaseMutex(m_taskMutex);
}

CPicDownloadManage* CPicDownloadManage::Instance()
{
	
	if (NULL == m_pInstace)
	{
		m_pInstace = new CPicDownloadManage;
		m_pInstace->StartUp();
	}

	return m_pInstace;
}

void CPicDownloadManage::ReleaseInstance()
{
	if (NULL != m_pInstace)
	{
		m_pInstace->ShutDown();
		delete m_pInstace;
		m_pInstace = NULL;
	}
}
