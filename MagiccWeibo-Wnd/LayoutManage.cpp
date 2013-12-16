#include "StdAfx.h"
#include "LayoutManage.h"
#include <memory>
#include <functional>
#include <xmemory>
#include <string>
#include <regex>

using namespace std::tr1;
using namespace std::tr1::placeholders;
using std::tr1::function;
using std::tr1::bind;
using std::tr1::regex;

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

	CTextUI *pWeiboInfo = static_cast<CTextUI*>(m_pPaintManage->FindSubControlByName(pListContainerUI,_T("weiboInfo")));
	if (pWeiboInfo)
	{
		wstring strWeiboText(strWeibo);

		struct httpPos
		{
			int startpos;
			int endpos;
		};

		std::vector<httpPos> httpList;
		wstring rex(_T("http://t.cn/[a-zA-Z0-9]+"));
		std::tr1::wsmatch  res;  
		std::tr1::wregex rx(rex.c_str());

		std::wstring::const_iterator itS = strWeiboText.begin();// not include the date prefix
		std::wstring::const_iterator itE = strWeiboText.end();

		if (std::tr1::regex_search(itS , itE , res, rx))
		{
			for (size_t i = 0; i < res.size() ; i ++)
			{
				httpPos pos;
				pos.startpos = res.position(i);
				pos.endpos = res.position(i) + res.length(i);
				httpList.push_back(pos);
			}
		}

		for (int i = httpList.size() - 1 ; i >= 0 ; i --)
		{
			strWeiboText.insert(httpList[i].endpos,_T("{/a}"));
			strWeiboText.insert(httpList[i].startpos,_T("{a noUnderline}"));
		}

		int atPos = strWeiboText.find('@');
		while (atPos != -1)
		{
			int spacePos = strWeiboText.find(' ',atPos + 1);
			int colonPos =	strWeiboText.find(':',atPos + 1);
			int endPos = 0;
			if (colonPos != -1 && spacePos != -1)
			{
				if (spacePos < colonPos && (spacePos - atPos) <= 10)
				{
					strWeiboText.insert(spacePos,_T("{/a}"));
					strWeiboText.insert(atPos,_T("{a noUnderline}"));
					endPos = spacePos + 20;
				}
				else if (colonPos<spacePos && (colonPos - atPos) <= 10)
				{
					strWeiboText.insert(colonPos,_T("{/a}"));
					strWeiboText.insert(atPos,_T("{a noUnderline}"));
			
					endPos = colonPos + 20;
				}
			}
			else if (colonPos == -1 && spacePos != -1 && (spacePos - atPos) <= 24)
			{
				strWeiboText.insert(spacePos,_T("{/a}"));
				strWeiboText.insert(atPos,_T("{a noUnderline}"));
		
				endPos = spacePos + 20;
			}
			else if (spacePos == -1 && colonPos != -1 && (colonPos - atPos) <= 10)
			{
				strWeiboText.insert(colonPos,_T("{/a}"));
				strWeiboText.insert(atPos,_T("{a noUnderline}"));

				endPos = colonPos + 20;
			}
			else
				break;

			atPos = strWeiboText.find('@',endPos + 1);
		}

		int firstTopicSep = strWeiboText.find('#');
		while (firstTopicSep != -1)
		{
			int secondTopicPos = strWeiboText.find('#',firstTopicSep + 1);
			if (secondTopicPos != -1)
			{
				strWeiboText.insert(secondTopicPos+2,_T("{/a}"));
				strWeiboText.insert(firstTopicSep,_T("{a noUnderline}"));
			}
			firstTopicSep = strWeiboText.find('#',secondTopicPos + 20);
		}

		pWeiboInfo->SetText(strWeiboText.c_str());
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
	
}
