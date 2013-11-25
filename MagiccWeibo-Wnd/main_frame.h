#pragma once

#include <IWeibo.hxx>
#include <IWeiboMethod.hxx>
#include <util/threading/Lock.hxx>
#include <IWeiboDef.hxx>
#include <IWeiboMethod.hxx>
#include <ParsingObject.hxx>
#include "ParsingDefine.hxx"
#include "ParsingDataStruct.h"
#include <util/threading/Lock.hxx>
using namespace weibo;

#define APP_KEY "397065771"
#define APP_SECRET "8b1a204835edfbde7e933a48b24cd79b"
#define REDIRECT_URL "http://www.baidu.com"

class CMagiccWebBrowserEventHandler;
class main_frame : public WindowImplBase
{
public:
	main_frame(void);
	~main_frame(void);

public:
	LPCTSTR GetWindowClassName() const;	

	virtual void OnFinalMessage(HWND hWnd);

	virtual void Init();

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual CDuiString GetSkinFile();

	virtual CDuiString GetSkinFolder();

	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	bool OnWeiboContentEvent(void *param);
	bool OnWeiboContentNotify(void *param);
	bool OnRefreshUnReadTimeline(void *param);

public:

	void OnAuthSuccess(VARIANT *&url);
	void OnAuthSuccess(CDuiString &strUrl);

	void OnWeiboRespComplated(unsigned int optionId, const char* httpHeader, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);

	void OnWeiboRespErrored(unsigned int optionId, const int errCode, const int errSubCode, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask);

	void OnWeiboRespStoped(unsigned int optionId, const weibo::UserTaskInfo* pTask);

protected:	

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	void RefreshTimeline(ParsingObjectPtr &parsingObjPtr);
private:
	string m_strUid;
	CMagiccWebBrowserEventHandler*	m_pWebBrowserEventHander;
	boost::shared_ptr<weibo::IWeibo> m_weiboPtr;

	CDialogBuilder m_dlgBuilder;
};
