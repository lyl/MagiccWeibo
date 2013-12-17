#pragma once
#include "httptask.h"

class CDownloadPicTask :
	public CHttpTask
{
public:
	CDownloadPicTask(string url,int key,string strPicPath);
	~CDownloadPicTask(void);

public:
	virtual size_t WriteImpl(void *ptr, size_t size , size_t nmemb);
	virtual void   OnStart();
	virtual void   OnComplete();

	void	SetPicPath(string name);
	string	GetPicPath(){return m_picPath;}
private:
	string m_picPath;
	FILE *fp;
};
