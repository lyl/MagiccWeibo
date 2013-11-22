#pragma once

class CRichEditUIEx : public CRichEditUI
{
public:
	CRichEditUIEx(void);
	~CRichEditUIEx(void);

public:
	 virtual bool OnTxViewChanged();
};
