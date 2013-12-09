#include "StdAfx.h"
#include "PicDownloadManage.h"

CPicDownloadManage::CPicDownloadManage(void)
{
}

CPicDownloadManage::~CPicDownloadManage(void)
{
}

bool CPicDownloadManage::StartUp()
{
	CURLcode retnCode;
	retnCode = curl_global_init(CURL_GLOBAL_ALL);
	if (CURLE_OK != retnCode)
	{
		return false;
	}

	m_pCurl = curl_easy_init();
	if (NULL == m_pCurl)
	{
		curl_global_cleanup();
		return false;
	}

}

bool CPicDownloadManage::ShutDown()
{
	curl_easy_cleanup(m_pCurl);
	curl_global_cleanup();
	return true;
}

void  CPicDownloadManage::SetPicName( string name )
{
	m_strPicName = name;
}

size_t CPicDownloadManage::WriteFun( void *ptr, size_t size, size_t nmemb, void *data )
{
	FILE *fp = (FILE*)data;
	if (fp && size > 0)
	{
		int written = fwrite(ptr,size,nmemb,fp);
		return written;
	}
	return size * nmemb;
}

bool  CPicDownloadManage::DownloadPic( string &strUrl )
{
	FILE *fp = fopen(m_strPicName.c_str(),"wb");
	if (!fp)
	{
		return false;
	}
	
	curl_easy_setopt(m_pCurl,CURLOPT_URL,strUrl.c_str());
	curl_easy_setopt(m_pCurl,CURLOPT_WRITEFUNCTION,&CPicDownloadManage::WriteFun);
	curl_easy_setopt(m_pCurl,CURLOPT_WRITEDATA,fp);

	CURLcode retn = curl_easy_perform(m_pCurl);
	if (retn != CURLE_OK)
	{
		fclose(fp);
		return false;
	}
	fclose(fp);

	return true;

}
