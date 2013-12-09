#pragma once


class DuiLib::CPaintManagerUI;
class CLayoutManage
{
public:
	CLayoutManage(void);
	~CLayoutManage(void);

public:
	void SetPaintManage(DuiLib::CPaintManagerUI *pManage);
	
	void UpdateUserProfile(LPCTSTR _name,LPCTSTR _picPath);
	void UpdateUnread(int count);
	void UpdateTimelineList(INT64 uid,LPCTSTR strUser,LPCTSTR strWeibo,LPCTSTR userPicPath);
private:
	DuiLib::CPaintManagerUI *m_pPaintManage;
};
