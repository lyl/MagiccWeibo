#include "StdAfx.h"
#include "LayoutManage.h"
#include <memory>
#include <functional>
#include <xmemory>

using namespace std::tr1;
using namespace std::tr1::placeholders;
using std::tr1::function;
using std::tr1::bind;

CLayoutManage::CLayoutManage(void)
{
}

CLayoutManage::~CLayoutManage(void)
{
}

void CLayoutManage::SetPaintManage( DuiLib::CPaintManagerUI *pManage )
{
	m_pPaintManage = pManage;
}


void CLayoutManage::UpdateUserProfile( LPCTSTR _name,LPCTSTR _picPath )
{
	CLabelUI *pScreenLabel = static_cast<CLabelUI*>(m_pPaintManage->FindControl(_T("currentUserScreenName")));
	if (pScreenLabel)
	{
		pScreenLabel->SetText(_name);
	}
	
	CButtonUI *pUsrPic = static_cast<CButtonUI*>(m_pPaintManage->FindControl(_T("currentUserPic")));
	if (pUsrPic)
	{
		pUsrPic->SetBkImage(_picPath);
	}

}

void CLayoutManage::UpdateUnread( int count )
{
	CLabelUI *pUnreadTimeline = static_cast<CLabelUI*>(m_pPaintManage->FindControl(_T("unreadTimelineCount")));
	CDuiString strUnRead(_T(""));
	if (count > 0)
	{
		strUnRead.Format(_T("%d"),count);
	}

	if (pUnreadTimeline)
	{
		pUnreadTimeline->SetText(strUnRead);
	}
}

void CLayoutManage::UpdateTimelineList( INT64 uid,LPCTSTR strUser,LPCTSTR strWeibo,LPCTSTR strUserPicPath )
{

	CListUI *pTimelineList = static_cast<CListUI*>(m_pPaintManage->FindControl(_T("timelineList")));
	if (pTimelineList)
	{
		pTimelineList->SetVisible(true);
	}

	CListContainerElementUI *pListContainerUI = NULL;

	CDialogBuilder dlgBuilder;

	pListContainerUI =static_cast<CListContainerElementUI*> (dlgBuilder.Create(_T("weibo_info_list.xml"),NULL,NULL,m_pPaintManage,NULL));

	if (pListContainerUI == NULL)
	{
		return;
	}

	CRichEditUI *pWeiboInfo = static_cast<CRichEditUI*>(m_pPaintManage->FindSubControlByName(pListContainerUI,_T("weiboInfo")));
	if (pWeiboInfo)
	{
		pWeiboInfo->SetText(strWeibo);
	}

	CButtonUI *pUsrPic = static_cast<CButtonUI*>(m_pPaintManage->FindSubControlByName(pListContainerUI,_T("userLogo")));
	if (pUsrPic)
	{
		pUsrPic->SetBkImage(strUserPicPath);
	}

	CLabelUI *pUserName = static_cast<CLabelUI*>(m_pPaintManage->FindSubControlByName(pListContainerUI,_T("userScreenName")));
	if (pUserName)
	{
		pUserName->SetText(strUser);
	}

	pListContainerUI->SetFixedHeight(150);

	if (pTimelineList)
	{
		pTimelineList->AddAt(pListContainerUI,0);
	}

// 	std::tr1::function<void(int,int)> funSetUrl = [&](int startPos,int endPos){
// 		pWeiboInfo->SetSel(startPos,endPos);
// 		CHARFORMAT2   cf; 
// 		ZeroMemory(&cf, sizeof(CHARFORMAT2));
// 		cf.cbSize = sizeof(CHARFORMAT2); 
// 		cf.dwMask = CFM_LINK; 
// 		cf.dwEffects |= CFE_LINK; 
// 		pWeiboInfo->SetSelectionCharFormat(cf);
// 		pWeiboInfo->SetSel(0,0);
// 	};

	CDuiString strWeiboText(strWeibo);
	int atPos = strWeiboText.Find('@');
	while (atPos != -1)
	{
		int colonPos =	strWeiboText.Find(':',atPos + 1);
		if (colonPos != -1)
		{
			pWeiboInfo->SetSel(atPos,colonPos);
			CHARFORMAT2   cf; 
			ZeroMemory(&cf, sizeof(CHARFORMAT2));
			cf.cbSize = sizeof(CHARFORMAT2); 
			cf.dwMask = CFM_LINK; 
			cf.dwEffects |= CFE_LINK;

			pWeiboInfo->SetSelectionCharFormat(cf);
			pWeiboInfo->SetSel(0,0);
		}
		atPos = strWeiboText.Find('@',colonPos + 1);
	}

	int firstTopicSep = strWeiboText.Find('#');
	while (firstTopicSep != -1)
	{
		int secondTopicPos = strWeiboText.Find('#',firstTopicSep + 1);
		if (secondTopicPos != -1)
		{
			pWeiboInfo->SetSel(firstTopicSep,secondTopicPos);
			CHARFORMAT2   cf; 
			ZeroMemory(&cf, sizeof(CHARFORMAT2));
			cf.cbSize = sizeof(CHARFORMAT2); 
			cf.dwMask = CFM_LINK; 
			cf.dwEffects |= CFE_LINK; 
			pWeiboInfo->SetSelectionCharFormat(cf);
			pWeiboInfo->SetSel(0,0);
		}
		firstTopicSep = strWeiboText.Find('#',secondTopicPos + 1);
	}
}
