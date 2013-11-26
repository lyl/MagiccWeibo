#include "StdAfx.h"
#include "main_frame.h"
#include "RichEditUIEx.h"
#include "MagiccWebBrowserEventHandler.h"

main_frame::main_frame(void)
{
}

main_frame::~main_frame(void)
{
	PostQuitMessage(0);
}

LPCTSTR main_frame::GetWindowClassName() const
{
	return _T("MagiccWeiboWnd");
}

void main_frame::OnFinalMessage( HWND hWnd )
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void main_frame::Init()
{
	m_PaintManager.SetBackgroundTransparent(true);
}

LRESULT main_frame::ResponseDefaultKeyEvent( WPARAM wParam )
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

DuiLib::CDuiString main_frame::GetSkinFile()
{
	return CDuiString(_T("main_frame.xml"));
}

DuiLib::CDuiString main_frame::GetSkinFolder()
{
	return CDuiString(_T("skin\\Magicc\\"));
}

LRESULT main_frame::MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled )
{
	return	WindowImplBase::MessageHandler(uMsg,wParam,lParam,bHandled);
}

CControlUI* main_frame::CreateControl( LPCTSTR pstrClass )
{
	if (_tcsicmp(pstrClass,_T("RichEditEx")) == 0)
	{
		CRichEditUIEx *pControl = new CRichEditUIEx;
		return pControl;
	}

	return NULL;
}

void main_frame::Notify( TNotifyUI& msg )
{
	if( msg.sType == _T("windowinit") ) 
		OnPrepare(msg);
	else if (_tcsicmp(msg.sType,_T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(),_T("closebtn")) == 0 )
		{	
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(),_T("minbtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(),_T("maxbtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(),_T("tagBtn")) == 0)
		{
			CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
			if (pRichEdit)
			{
				CDuiString strText = _T("#插入你的话题#");
				pRichEdit->SetText(strText);
				pRichEdit->SetSel(1,7);
				pRichEdit->SetFocus();
				
				CLabelUI *plabel = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("defaultShowText")));
				if (plabel)
				{
					plabel->SetVisible(false);
				}
				
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(),_T("sendWeiboBtn")) == 0)
		{
			CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
			if (pRichEdit)
			{
				CDuiString strWeibo = pRichEdit->GetText();
				if (strWeibo.GetLength() > 0)
				{
					DWORD dwNum = WideCharToMultiByte(CP_UTF8,NULL,strWeibo,-1,NULL,0,NULL,FALSE);
					char *psText;
					psText = new char[dwNum];
					if(!psText)
					{
						delete []psText;
					}
					WideCharToMultiByte (CP_UTF8,NULL,strWeibo,-1,psText,dwNum,NULL,FALSE);
					m_weiboPtr->getMethod()->postStatusesUpdate(psText, NULL, NULL);

					delete []psText;

					pRichEdit->SetText(_T(""));
				}
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(),_T("refreshBtn")) == 0)
		{
			m_weiboPtr->getMethod()->getStatusesFriendTimeline();
		}
	}
	
}

void main_frame::OnPrepare( TNotifyUI& msg )
{
	m_weiboPtr = weibo::WeiboFactory::getWeibo();

	m_weiboPtr->startup();
	m_weiboPtr->setOption(weibo::WOPT_CONSUMER, APP_KEY, APP_SECRET);

	m_weiboPtr->OnDelegateComplated += std::make_pair(this,&main_frame::OnWeiboRespComplated);
	m_weiboPtr->OnDelegateErrored += std::make_pair(this,&main_frame::OnWeiboRespErrored);
	m_weiboPtr->OnDelegateWillRelease += std::make_pair(this,&main_frame::OnWeiboRespStoped);

	CRichEditUI *pWeiboCotent = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
	if (pWeiboCotent)
	{
		pWeiboCotent->OnEvent += MakeDelegate(this,&main_frame::OnWeiboContentEvent);
		pWeiboCotent->OnNotify += MakeDelegate(this,&main_frame::OnWeiboContentNotify);
	}
	CWebBrowserUI *pLoginWeb = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("loginWnd")));
	if (pLoginWeb)
	{
		m_pWebBrowserEventHander = new CMagiccWebBrowserEventHandler;
		m_pWebBrowserEventHander->SetMainFrame(this);
		pLoginWeb->SetWebBrowserEventHandler(m_pWebBrowserEventHander);
		pLoginWeb->NavigateUrl(_T("https://api.weibo.com/oauth2/authorize?client_id=397065771&response_type=code&redirect_uri=www.baidu.com"));
	}

	CLabelUI *pUnreadTimeline = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("unreadTimelineCount")));
	if (pUnreadTimeline)
	{
		pUnreadTimeline->OnEvent += MakeDelegate(this,&main_frame::OnRefreshUnReadTimeline);
	}

}

void main_frame::OnExit( TNotifyUI& msg )
{
	

	Close();
}

void main_frame::OnTimer( TNotifyUI& msg )
{

}


LRESULT main_frame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{


	m_weiboPtr->OnDelegateComplated -= std::make_pair(this, &main_frame::OnWeiboRespComplated);
	m_weiboPtr->OnDelegateErrored -= std::make_pair(this, &main_frame::OnWeiboRespErrored);
	m_weiboPtr->OnDelegateWillRelease -= std::make_pair(this, &main_frame::OnWeiboRespStoped);
	m_weiboPtr->shutdown();



	if (m_pWebBrowserEventHander)
	{
		delete m_pWebBrowserEventHander;
		m_pWebBrowserEventHander = NULL;
	}

	int i = 255;
	int j = 0;
	HWND hwnd = m_PaintManager.GetPaintWindow();
	RECT rc;
	::GetWindowRect(hwnd,&rc);
	
	for (;i>0 && rc.top > 0;i -= 20)
	{
		::GetWindowRect(hwnd,&rc);
		
		m_PaintManager.SetTransparent(i);
		
		::SetWindowPos(hwnd,HWND_NOTOPMOST,rc.left,rc.top - j * 5,0,0,SWP_NOSIZE);
		j++;
		Sleep(20);
	}

	bHandled = FALSE;
	return 0;
}

bool main_frame::OnWeiboContentEvent( void *param )
{
	TEventUI *pEvent = (TEventUI*)param;
	if (pEvent->Type == UIEVENT_SETFOCUS )
	{
		CHorizontalLayoutUI *pWeiboCotentContainer = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("weiboContentContainer")));
		if (pWeiboCotentContainer)
		{
			pWeiboCotentContainer->SetBorderColor(RGB(0,0,255));
		}
		CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(pEvent->pSender);
		if (pRichEdit)
		{
			CDuiString strText = pRichEdit->GetText();
			if (strText.GetLength() == 0)
			{
				CLabelUI *plabel = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("defaultShowText")));
				if (plabel)
				{
					plabel->SetVisible(false);
				}
			}
		}
	}
	else if (pEvent->Type == UIEVENT_KILLFOCUS )
	{
		CHorizontalLayoutUI *pWeiboCotentContainer = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("weiboContentContainer")));
		if (pWeiboCotentContainer)
		{
			pWeiboCotentContainer->SetBorderColor(RGB(204,204,204));
		}
		CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
		if (pRichEdit)
		{
			CDuiString strText = pRichEdit->GetText();
			if (strText.GetLength() == 0)
			{
				CLabelUI *plabel = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("defaultShowText")));
				if (plabel)
				{
					plabel->SetVisible(true);
				}
			}
		}
	}
	else if (pEvent->Type == UIEVENT_MOUSELEAVE)
	{
		CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
		if (pRichEdit)
		{
			if (!pRichEdit->IsFocused())
			{
				CHorizontalLayoutUI *pWeiboCotentContainer = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("weiboContentContainer")));
				if (pWeiboCotentContainer)
				{
					pWeiboCotentContainer->SetBorderColor(RGB(204,204,204));
				}
			}
		}
	}
	else if (pEvent->Type == UIEVENT_MOUSEENTER)
	{
		CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
		if (pRichEdit)
		{
			if (!pRichEdit->IsFocused())
			{
				CHorizontalLayoutUI *pWeiboCotentContainer = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("weiboContentContainer")));
				if (pWeiboCotentContainer)
				{
					pWeiboCotentContainer->SetBorderColor(RGB(0,0,255));
				}
			}
		}
	}

	return true;
}

bool main_frame::OnWeiboContentNotify( void *param )
{
	TNotifyUI *pNotify = (TNotifyUI *)param;
	if (_tcsicmp(pNotify->pSender->GetName() ,  _T("weiboContent")) == 0)
	{
		CRichEditUI *pRichEdit = static_cast<CRichEditUI*>(pNotify->pSender);
		if (pRichEdit && (_tcsicmp(pNotify->sType,_T("richEditTxViewChanged")) == 0))
		{
			CDuiString strText = pRichEdit->GetText();
			int length = strText.GetLength();
			if (length < 140)
			{
				CDuiString strLimit;
				strLimit.Format(_T("%d"),140-length);
				CLabelUI *pLabel = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("limitTextLength")));
				if (pLabel)
				{
					pLabel->SetText(strLimit);
				}
			}
		}

	}	
	return true;
}

void main_frame::OnWeiboRespComplated( unsigned int optionId, const char* httpHeader, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask )
{
	if (result)
	{
		ParsingObject* tempObject = new ParsingObject(*result);
		ParsingObjectPtr objPtr(tempObject);
		// The special event.
		switch(optionId)
		{
		case WBOPT_OAUTH2_ACCESS_TOKEN:
			{
				USES_CONVERSION;
				ParsingOauthRet ret;
				ret.doParse(objPtr);

				m_strUid = ret.uid;
				
				//std::string access_token = objPtr->getSubStringByKey("access_token");

				m_weiboPtr->setOption(WOPT_ACCESS_TOKEN, ret.access_token.c_str());
				
				m_weiboPtr->getMethod()->getStatusesFriendTimeline();

			}
			break;
		case WBOPT_POST_STATUSES_UPDATE:
			{
				//m_logInfo.AppendText(_T("\r\n微博发送成功!"));
			}
			break;
		case WBOPT_GET_REMIND_UNREAD_COUNT:
			{
				USES_CONVERSION;
				string strCountUnRead = objPtr->getSubStringByKey("status");
				int count = atoi(strCountUnRead.c_str());
				CDuiString strUnRead;
				strUnRead.Format(_T("%d"),count);

				CLabelUI *pUnreadTimeline = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("unreadTimelineCount")));
				if (pUnreadTimeline)
				{
					pUnreadTimeline->SetText(strUnRead);
				}
			}
			break;
		case WBOPT_GET_STATUSES_FRIENDS_TIMELINE:
			{
				RefreshTimeline(objPtr);
			}
			break;

		default:
			break;
		}
	}
}

void main_frame::OnWeiboRespErrored( unsigned int optionId, const int errCode, const int errSubCode, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask )
{

}

void main_frame::OnWeiboRespStoped( unsigned int optionId, const weibo::UserTaskInfo* pTask )
{

}

void main_frame::OnAuthSuccess( VARIANT *&url )
{
	USES_CONVERSION;
	LPCTSTR lpstrAddress = (LPCTSTR)url->bstrVal;

	CDuiString str(lpstrAddress);

	int pos  = -1;
	pos = str.Find('=');

	CDuiString retnCode = str.Right(str.GetLength() - pos - 1);

	m_weiboPtr->getMethod()->oauth2Code(W2A(retnCode), REDIRECT_URL , NULL);

	CWebBrowserUI *pLoginWeb = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("loginWnd")));
	if (pLoginWeb)
	{
		pLoginWeb->SetVisible(false);
	}

	CLabelUI *pUnReadTimelineCount = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("unreadTimelineCount")));
	if (pUnReadTimelineCount)
	{
		m_PaintManager.SetTimer(pUnReadTimelineCount,1,1000*10);
	}
}

void main_frame::OnAuthSuccess( CDuiString &strUrl )
{

	USES_CONVERSION;
	int pos  = -1;
	pos = strUrl.Find('=');

	CDuiString retnCode = strUrl.Right(strUrl.GetLength() - pos - 1);

	m_weiboPtr->getMethod()->oauth2Code(W2A(retnCode), REDIRECT_URL , NULL);

	CWebBrowserUI *pLoginWeb = static_cast<CWebBrowserUI*>(m_PaintManager.FindControl(_T("loginWnd")));
	if (pLoginWeb)
	{
		pLoginWeb->SetVisible(false);
	}
	
	CLabelUI *pUnReadTimelineCount = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("unreadTimelineCount")));
	if (pUnReadTimelineCount)
	{
		m_PaintManager.SetTimer(pUnReadTimelineCount,1,1000*10);
	}
}

void main_frame::RefreshTimeline(ParsingObjectPtr &parsingObjPtr)
{
	USES_CONVERSION;
	ParsingObjectPtr pAllNewWeibo = parsingObjPtr->getSubObjectByKey("statuses");

	if (pAllNewWeibo == NULL)
	{
		return;
	}

	CListUI *pTimelineList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("timelineList")));
	if (pTimelineList)
	{
		pTimelineList->SetVisible(true);
	}

	for (int i = pAllNewWeibo->getSubCounts() - 1 ; i >= 0 ; i --)
	{
		ParsingObjectPtr pWeibo = pAllNewWeibo->getSubObjectByIndex(i);
		string strText = pWeibo->getSubStringByKey("text");
	//	m_lastWeiboID = atoi(pWeibo->getSubStringByKey("id").c_str());
		ParsingObjectPtr pUser = pWeibo->getSubObjectByKey("user");
		string strUser = "";
		if (pUser)
		{
			strUser = pUser->getSubStringByKey("screen_name");
		}
		else
		{
			continue;
		}

		DWORD dwNum = MultiByteToWideChar(CP_UTF8,NULL,strUser.c_str(),-1,NULL,0);
		WCHAR *psText;
		psText = new WCHAR[dwNum];
		if(!psText)
		{
			delete []psText;
		}
		MultiByteToWideChar (CP_UTF8,NULL,strUser.c_str(),-1,psText,dwNum);


		dwNum = MultiByteToWideChar(CP_UTF8,NULL,strText.c_str(),-1,NULL,0);
		WCHAR *psWeiboText;
		psWeiboText = new WCHAR[dwNum];
		if(!psWeiboText)
		{
			delete []psText;
		}
		MultiByteToWideChar (CP_UTF8,NULL,strText.c_str(),-1,psWeiboText,dwNum);


	

		CListContainerElementUI *pListContainerUI = NULL;

		if (!m_dlgBuilder.GetMarkup()->IsValid())
		{
			pListContainerUI =static_cast<CListContainerElementUI*> (m_dlgBuilder.Create(_T("weibo_info_list.xml"),NULL,NULL,&m_PaintManager,NULL));
		}
		else
		{
			pListContainerUI = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(NULL,&m_PaintManager));
		}

		if (pListContainerUI == NULL)
		{
			continue;
		}
		
		CLabelUI *pUserName = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pListContainerUI,_T("userScreenName")));
		if (pUserName)
		{
			pUserName->SetText(psText);
		}
		CTextUI *pWeiboInfo = static_cast<CTextUI*>(m_PaintManager.FindSubControlByName(pListContainerUI,_T("weiboInfo")));
		if (pWeiboInfo)
		{
			pWeiboInfo->SetText(psWeiboText);
		}

		if (pTimelineList)
		{
			pTimelineList->AddAt(pListContainerUI,0);
		}
		
		pListContainerUI->SetFixedHeight(150);

		delete []psText;
		delete []psWeiboText;
	}
}

bool main_frame::OnRefreshUnReadTimeline( void *param )
{
	m_weiboPtr->getMethod()->getRemindUnreadCount(m_strUid.c_str());

	return true;
}
