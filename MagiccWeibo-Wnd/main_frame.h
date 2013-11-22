#pragma once
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

protected:	

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	
};
