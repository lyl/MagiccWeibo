#pragma once

#include <IWeibo.hxx>
#include <IWeiboMethod.hxx>
#include <util/threading/Lock.hxx>
#include <IWeiboDef.hxx>
#include <IWeiboMethod.hxx>
#include <ParsingObject.hxx>
#include "ParsingDefine.hxx"
#include "ParsingDataStruct.h"

#include "PicDownloadManage.h"
#include <memory>
#include <functional>

using namespace weibo;
using namespace std::tr1;
using namespace std::tr1::placeholders;
using std::tr1::function;
using std::tr1::bind;

#define APP_KEY "397065771"
#define APP_SECRET "8b1a204835edfbde7e933a48b24cd79b"
#define REDIRECT_URL "http://www.baidu.com"

class CWeiboManage
{
public:
	CWeiboManage(void);
	~CWeiboManage(void);

public:
	void StartUp();
	void ShutDown();
	
public:
	void PostNewWeibo(char* pText);
	bool GetRemindUnreadCount();
	bool RefreshTimeline();
	weibo::IWeiboMethod *GetMethod();
	weibo::IWeibo *		GetWeibo();
	bool	CheckExistUser();
	void	InitWeibo();

public:
	void OnWeiboRespComplated(unsigned int optionId, const char* httpHeader, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);
	void OnWeiboRespErrored(unsigned int optionId, const int errCode, const int errSubCode, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);
	void OnWeiboRespStoped(unsigned int optionId, const weibo::UserTaskInfo* pTask);

public:
	std::tr1::function<void(LPCTSTR,LPCSTR,LPCSTR)> UpdateUserProfile;
	std::tr1::function<void(int)> UpdateUnread;
	std::tr1::function<void(INT64,LPCTSTR,LPCTSTR,LPCSTR,LPCSTR)> UpdateTimelineList;

protected:
	void RefreshTimeline(ParsingObjectPtr &parsingObjPtr);

private:
	boost::shared_ptr<weibo::IWeibo> m_weiboPtr;

	CPicDownloadManage m_picDownload;

	INT64 m_lastWeiboId;

	string m_strUid;
	string m_accessToken;

	Util::Mutex mutex;
};
