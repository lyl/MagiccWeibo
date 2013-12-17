#include "StdAfx.h"
#include "DownloadPicTask.h"

CDownloadPicTask::CDownloadPicTask(string url,int key,string strPicPath)
:CHttpTask(url,key),
fp(NULL),
m_picPath(strPicPath)
{
}

CDownloadPicTask::~CDownloadPicTask(void)
{
}

size_t CDownloadPicTask::WriteImpl( void *ptr, size_t size , size_t nmemb )
{
	if (fp)
	{
		fwrite(ptr,size,nmemb,fp);
	}

	return size * nmemb;
}

void CDownloadPicTask::OnStart()
{
	fp = fopen(m_picPath.c_str(),"wb");
}

void CDownloadPicTask::OnComplete()
{
	fclose(fp);
	if (CompleteCallback)
	{
		CompleteCallback(m_key);
	}
}

void CDownloadPicTask::SetPicPath( string name )
{
	m_picPath = name;
}
