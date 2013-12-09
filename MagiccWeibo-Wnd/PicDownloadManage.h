#pragma once
#include "curl/curl.h"

class CPicDownloadManage
{
public:
	CPicDownloadManage(void);
	~CPicDownloadManage(void);

public:
	bool StartUp();
	bool ShutDown();

public:
	void  SetPicName(string name);
	bool  DownloadPic(string &strUrl);

public:
	static size_t WriteFun( void *ptr, size_t size, size_t nmemb, void *data);

private:
	CURL *m_pCurl;
	string m_strPicName;
};
