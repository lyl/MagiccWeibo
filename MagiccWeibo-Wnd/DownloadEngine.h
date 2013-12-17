#pragma once
#include "HttpTask.h"
#include <util/threading/Lock.hxx>
#include <memory>
#include <list>
using namespace std::tr1;
class Util::Mutex;

class CDownloadEngine
{
public:
	CDownloadEngine(void);
	virtual ~CDownloadEngine(void);

public:
	virtual void Run();
	virtual void Shutdown();

	bool IsShutdown() const;
	bool IsRunning() const;

	virtual void ThreadProc();

	
	typedef std::list<HttpTaskPtr> HttpTaskList;

	void AddTask(HttpTaskPtr ptr);

private:
	void ScanPrepareTaskList();
	bool ScanRunningTaskList(CURLM *multi_curl);
	bool PerformMutliCurl(CURLM *multi_curl,bool &bHasHandle);

	void DispatchTaskStatus(CURLM *multi_curl);
	void TaskListClearnUp(CURLM *multi_curl);

protected:
	bool m_shutdown;
	mutable Util::Mutex m_shutdownMutex;
	mutable Util::Mutex m_queneMutex;
	HANDLE m_thread;
	unsigned int m_threadId;

	HttpTaskList m_prepareTaskList;
	HttpTaskList m_runningTaskList;

protected:
	static void * __stdcall Wrapper(void *param);
};
