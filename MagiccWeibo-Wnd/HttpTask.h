#pragma once
#include "curl/curl.h"
#include <memory>
#include <functional>

enum HTTP_TASK_TYPE
{
	HTTP_NULL = 0,
	HTTP_TASK_GET = 1,
	HTTP_TASK_POST = 2,
};

enum HTTP_TASK_STATUS
{
	TASK_STATUS_START = 1,
	TASK_STATUS_COMPLETE = 2,
	TASK_STATUS_ERROR = 3,
};



class CHttpTask
{
public:
	CHttpTask(string url,int key,HTTP_TASK_TYPE type = HTTP_TASK_GET);
	virtual ~CHttpTask(void);

public:
	virtual size_t WriteImpl(void *ptr, size_t size , size_t nmemb);
	virtual void   OnStart();
	virtual void   OnComplete();
	virtual void   OnError();

public:
	void	InitTask();
	void	UnInitTask();
	CURL*	GetCurl(){return m_pCurl;}
	void	SetStatus(HTTP_TASK_STATUS status){m_httpStatus = status;}
	HTTP_TASK_STATUS GetStatus(){return m_httpStatus;}
	void	SetData(void *pData){m_pUserData = pData;}
	void*	GetData(){return m_pUserData;}

	std::tr1::function<void(int)> CompleteCallback;
public:
	static size_t WriteProc( void *ptr, size_t size, size_t nmemb, void *data); 

protected:
	HTTP_TASK_TYPE m_httpType;
	HTTP_TASK_STATUS m_httpStatus;
	CURL *m_pCurl;
	string m_url;
	int	   m_key;
	void *m_pUserData;
};

typedef std::tr1::shared_ptr<CHttpTask> HttpTaskPtr;