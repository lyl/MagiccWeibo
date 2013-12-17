#pragma once


class DuiLib::CPaintManagerUI;
class CLayoutManage
{
public:
	CLayoutManage(void);
	~CLayoutManage(void);

public:
	void SetPaintManage(DuiLib::CPaintManagerUI *pManage);
	
	void UpdateUserProfile(LPCTSTR _name,LPCSTR _picPath,LPCSTR _picUrl);
	void UpdateUnread(int count);
	void UpdateTimelineList(INT64 uid,LPCTSTR strUser,LPCTSTR strWeibo,LPCSTR userPicPath,LPCSTR _picUrl);
private:
	DuiLib::CPaintManagerUI *m_pPaintManage;
};
