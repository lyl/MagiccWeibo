#pragma once
#include "curl/curl.h"
#include "DownloadPicTask.h"
#include "DownloadEngine.h"
#include <map>

class CPicDownloadManage
{
public:
	CPicDownloadManage(void);
	~CPicDownloadManage(void);

public:
	bool StartUp();
	bool ShutDown();

public:
	void	AddDownloadTask(string strPicName,string strUrl,CControlUI *pControl);

public:
	void	TaskComplete(int key);

	static  CPicDownloadManage* Instance();
	static void ReleaseInstance();

private:
	static CPicDownloadManage *m_pInstance;
	std::map<int,HttpTaskPtr> m_taskList;
	CDownloadEngine *m_downloadEngine;
	HANDLE m_taskMutex;
};
