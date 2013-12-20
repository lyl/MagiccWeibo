#include "StdAfx.h"
#include "LayoutManage.h"
#include "PicDownloadManage.h"
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


void CLayoutManage::UpdateUserProfile( wstring _name,string _picPath ,string _picUrl)
{
	CLabelUI *pScreenLabel = static_cast<CLabelUI*>(m_pPaintManage->FindControl(_T("currentUserScreenName")));
	if (pScreenLabel)
	{
		pScreenLabel->SetText(_name.c_str());
	}
	
	CButtonUI *pUsrPic = static_cast<CButtonUI*>(m_pPaintManage->FindControl(_T("currentUserPic")));
	if (pUsrPic)
	{
		CPicDownloadManage::Instance()->AddDownloadTask(_picPath,_picUrl,pUsrPic);
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

void CLayoutManage::UpdateTimelineList( INT64 uid,LPCTSTR strUser,LPCTSTR strWeibo,string strUserPicPath ,string _picUrl)
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

		struct linkPos
		{
			int startpos;
			int endpos;
			wstring slink;
		};

		std::vector<linkPos> linkList;
		wstring rex(_T("http://t.cn/[a-zA-Z0-9]+"));
		std::tr1::wsmatch  res;  
		std::tr1::wregex rx(rex.c_str());

		std::wstring::const_iterator itS = strWeiboText.begin();// not include the date prefix
		std::wstring::const_iterator itE = strWeiboText.end();

		if (std::tr1::regex_search(itS , itE , res, rx))
		{
			for (size_t i = 0; i < res.size() ; i ++)
			{
				linkPos pos;
				pos.startpos = res.position(i);
				pos.endpos = res.position(i) + res.length(i);
				pos.slink = res.str(i);
				linkList.push_back(pos);
			}
		}

		for (int i = linkList.size() - 1 ; i >= 0 ; i --)
		{
			strWeiboText.insert(linkList[i].endpos,_T("{/a}"));
			wstring stemp = _T("{a ");
			stemp.append(linkList[i].slink);
			stemp.append(_T("}"));
			strWeiboText.insert(linkList[i].startpos,stemp);
		}

		linkList.clear();

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
					linkPos pos;
					pos.startpos = atPos;
					pos.endpos = spacePos;
					pos.slink = strWeiboText.substr(atPos,spacePos - atPos);

					linkList.push_back(pos);

					endPos = spacePos;
				}
				else if (colonPos<spacePos && (colonPos - atPos) <= 10)
				{

					linkPos pos;
					pos.startpos = atPos;
					pos.endpos = colonPos;
					pos.slink = strWeiboText.substr(atPos,colonPos - atPos);

					linkList.push_back(pos);

					endPos = colonPos;
				}
			}
			else if (colonPos == -1 && spacePos != -1 && (spacePos - atPos) <= 24)
			{

				linkPos pos;
				pos.startpos = atPos;
				pos.endpos = spacePos;
				pos.slink = strWeiboText.substr(atPos,spacePos - atPos);

				linkList.push_back(pos);

				endPos = spacePos;
			}
			else if (spacePos == -1 && colonPos != -1 && (colonPos - atPos) <= 10)
			{
				linkPos pos;
				pos.startpos = atPos;
				pos.endpos = colonPos;
				pos.slink = strWeiboText.substr(atPos,colonPos - atPos);

				linkList.push_back(pos);

				endPos = colonPos;
			}
			else
				break;

			atPos = strWeiboText.find('@',endPos + 1);
		}

		for (int i = linkList.size() - 1 ; i >= 0 ; i --)
		{
			strWeiboText.insert(linkList[i].endpos,_T("{/a}"));
			wstring stemp = _T("{a ");
			stemp.append(linkList[i].slink);
			stemp.append(_T("}"));
			strWeiboText.insert(linkList[i].startpos,stemp);
		}

		linkList.clear();

		int firstTopicSep = strWeiboText.find('#');
		while (firstTopicSep != -1)
		{
			int secondTopicPos = strWeiboText.find('#',firstTopicSep + 1);
			if (secondTopicPos != -1)
			{
				linkPos pos;
				pos.startpos = firstTopicSep;
				pos.endpos = secondTopicPos + 1;
				pos.slink = strWeiboText.substr(firstTopicSep,secondTopicPos - firstTopicSep + 1);
				linkList.push_back(pos);
			}
			firstTopicSep = strWeiboText.find('#',secondTopicPos+2);
		}

		for (int i = linkList.size() - 1 ; i >= 0 ; i --)
		{
			strWeiboText.insert(linkList[i].endpos,_T("{/a}"));
			wstring stemp = _T("{a ");
			stemp.append(linkList[i].slink);
			stemp.append(_T("}"));
			strWeiboText.insert(linkList[i].startpos,stemp);
		}

		pWeiboInfo->SetText(strWeiboText.c_str());
	}

	CButtonUI *pUsrPic = static_cast<CButtonUI*>(m_pPaintManage->FindSubControlByName(pListContainerUI,_T("userLogo")));
	if (pUsrPic)
	{
		CPicDownloadManage::Instance()->AddDownloadTask(strUserPicPath,_picUrl,pUsrPic);
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
		pTimelineList->SelectItem(0);
	}



// 	if (pWeiboInfo)
// 	{
// 		RECT rcContent = pWeiboInfo->EstimateSize();
// 		RECT rcName = pUserName->GetPos();
// 		pListContainerUI->SetFixedHeight(abs(rcName.bottom - rcName.top) + abs(rcContent.bottom - rcContent.top));
// 	}
	
}
