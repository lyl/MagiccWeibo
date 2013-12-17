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

	return true;
}

bool CPicDownloadManage::ShutDown()
{
	m_downloadEngine->Shutdown();
	
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
	srand((unsigned int)time(NULL));
	int key = rand();
	HttpTaskPtr task(new CDownloadPicTask(strUrl,key,strPicName));
	task->CompleteCallback = std::tr1::bind(&CPicDownloadManage::TaskComplete,this,_1);
	task->SetData(pControl);
	{
		Util::Lock lock(m_taskListMutex);
		m_taskList.insert(std::make_pair(key,task));
	}
	m_downloadEngine->AddTask(task);

}

void CPicDownloadManage::TaskComplete( int key )
{
	Util::Lock lock(m_taskListMutex);
	std::map<int,HttpTaskPtr>::iterator itor = m_taskList.find(key);
	if (itor != m_taskList.end())
	{
		std::tr1::shared_ptr<CDownloadPicTask> pDownPicTask = dynamic_pointer_cast<CDownloadPicTask>(itor->second);
		if (pDownPicTask)
		{
			CControlUI *pControl =(CControlUI *) pDownPicTask->GetData();
			string strPicPath = pDownPicTask->GetPicPath();
			int pos = strPicPath.find_last_of("Temp");
			if (pos != -1)
			{
				string subStr = strPicPath.substr(pos,strPicPath.length() - pos - 1);
				USES_CONVERSION;
				pControl->SetBkImage(A2W(subStr.c_str()));
			}
		}
		m_taskList.erase(itor);
	}
}

CPicDownloadManage* CPicDownloadManage::Instance()
{
	if (NULL == m_pInstace)
	{
		m_pInstace = new CPicDownloadManage;
	}

	return m_pInstace;
}

void CPicDownloadManage::ReleaseInstance()
{
	if (NULL != m_pInstace)
	{
		delete m_pInstace;
		m_pInstace = NULL;
	}
}
