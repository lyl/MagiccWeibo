#include "StdAfx.h"
#include "HttpTask.h"


CHttpTask::CHttpTask(string url ,int key, HTTP_TASK_TYPE type )
:m_url(url),
m_key(key),
m_httpType(type),
m_pCurl(NULL),
m_httpStatus(TASK_STATUS_START),
CompleteCallback(NULL)
{

}

CHttpTask::~CHttpTask(void)
{
	
}

void CHttpTask::OnStart()
{

}

void CHttpTask::OnComplete()
{

}

void CHttpTask::OnError()
{

}

void CHttpTask::UnInitTask()
{
	if (m_pCurl)
	{
		curl_easy_cleanup(m_pCurl);
		m_pCurl = NULL;
	}
}

void CHttpTask::InitTask()
{
	m_pCurl = curl_easy_init();

	curl_easy_setopt(m_pCurl,CURLOPT_URL,m_url.c_str());

	if (m_httpType == HTTP_TASK_GET)
	{
		curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,&CHttpTask::WriteProc);
		curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,this);
	}
}

size_t CHttpTask::WriteImpl( void *ptr, size_t size , size_t nmemb )
{
	return size * nmemb;
}



size_t CHttpTask::WriteProc( void *ptr, size_t size, size_t nmemb, void *data )
{
	CHttpTask *pTask = static_cast<CHttpTask*>(data);
	return pTask->WriteImpl(ptr,size,nmemb);
}
