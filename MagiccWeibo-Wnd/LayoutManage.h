#pragma once


class DuiLib::CPaintManagerUI;
class CLayoutManage
{
public:
	CLayoutManage(void);
	~CLayoutManage(void);

public:
	void SetPaintManage(DuiLib::CPaintManagerUI *pManage);
	
	void UpdateUserProfile(wstring _name,string _picPath,string _picUrl);
	void UpdateUnread(int count);
	void UpdateTimelineList(INT64 uid,LPCTSTR strUser,LPCTSTR strWeibo,string userPicPath,string _picUrl);
private:
	DuiLib::CPaintManagerUI *m_pPaintManage;
};
