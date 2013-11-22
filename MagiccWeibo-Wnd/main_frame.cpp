#include "StdAfx.h"
#include "main_frame.h"
#include "RichEditUIEx.h"

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
	}
	
}

void main_frame::OnPrepare( TNotifyUI& msg )
{
	CRichEditUI *pWeiboCotent = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("weiboContent")));
	if (pWeiboCotent)
	{
		pWeiboCotent->OnEvent += MakeDelegate(this,&main_frame::OnWeiboContentEvent);
		pWeiboCotent->OnNotify += MakeDelegate(this,&main_frame::OnWeiboContentNotify);
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
