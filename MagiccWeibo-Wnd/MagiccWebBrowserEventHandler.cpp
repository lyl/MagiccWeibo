#include "StdAfx.h"
#include "MagiccWebBrowserEventHandler.h"
#include "main_frame.h"

CMagiccWebBrowserEventHandler::CMagiccWebBrowserEventHandler(void)
{
}

CMagiccWebBrowserEventHandler::~CMagiccWebBrowserEventHandler(void)
{
}

 void CMagiccWebBrowserEventHandler::DocumentComplete( IDispatch *pDisp,VARIANT *&url )
 {
 	if (m_pMainFrame)
 	{
 		CDuiString strUrl =  url->bstrVal;
 		int pos = -1;
 
 		pos = strUrl.Find(_T("www.baidu.com/?code="));
 		if (pos >= 0)
 		{
 			m_pMainFrame->OnAuthSuccess(url);
 		}
 	}
 }

void CMagiccWebBrowserEventHandler::SetMainFrame( main_frame *pFrame )
{
	m_pMainFrame = pFrame;
}

void CMagiccWebBrowserEventHandler::DownloadBegin( CDuiString &strUrl )
{
	if (m_pMainFrame)
	{
		
		int pos = -1;
		pos = strUrl.Find(_T("www.baidu.com/?code="));
		if (pos >= 0)
		{
			m_pMainFrame->OnAuthSuccess(strUrl);
		}
	}
}
