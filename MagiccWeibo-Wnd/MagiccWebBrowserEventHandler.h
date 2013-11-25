#pragma once
class main_frame;
class CMagiccWebBrowserEventHandler :
	public CWebBrowserEventHandler
{
public:
	CMagiccWebBrowserEventHandler(void);
	~CMagiccWebBrowserEventHandler(void);

public:
	virtual void DocumentComplete(IDispatch *pDisp,VARIANT *&url);
	virtual void DownloadBegin(CDuiString &strUrl);

	void SetMainFrame(main_frame *pFrame);

private:
	main_frame *m_pMainFrame;
};
