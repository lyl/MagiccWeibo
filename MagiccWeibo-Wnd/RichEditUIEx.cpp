#include "StdAfx.h"
#include "RichEditUIEx.h"

CRichEditUIEx::CRichEditUIEx(void)
{
}

CRichEditUIEx::~CRichEditUIEx(void)
{
}

bool CRichEditUIEx::OnTxViewChanged()
{
	GetManager()->SendNotify(this,_T("richEditTxViewChanged"));

	return true;
}
