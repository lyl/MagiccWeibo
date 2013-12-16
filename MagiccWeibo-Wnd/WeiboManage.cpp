#include "StdAfx.h"
#include "WeiboManage.h"

CWeiboManage::CWeiboManage(void)
{
	m_lastWeiboId = 0;
	m_picDownload.StartUp();
}

CWeiboManage::~CWeiboManage(void)
{
	m_picDownload.ShutDown();
}


void CWeiboManage::OnWeiboRespComplated( unsigned int optionId, const char* httpHeader, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask )
{

	Util::Lock lock(mutex);

	if (result)
	{
		USES_CONVERSION;
		ParsingObject* tempObject = new ParsingObject(*result);
		ParsingObjectPtr objPtr(tempObject);
		// The special event.
		switch(optionId)
		{
		case WBOPT_OAUTH2_ACCESS_TOKEN:
			{

				ParsingOauthRet ret;
				ret.doParse(objPtr);

				m_strUid = ret.uid;

				m_weiboPtr->setOption(WOPT_ACCESS_TOKEN, ret.access_token.c_str());

				TCHAR cPath[MAX_PATH];
				GetModuleFileName(NULL,cPath,MAX_PATH);
				CString strPath = CString(cPath);
				strPath = strPath.Left(strPath.ReverseFind('\\'));
				strPath += _T("\\Config.ini");

				WritePrivateProfileString(_T("Main"),_T("access_token"),A2W(ret.access_token.c_str()),strPath);
				WritePrivateProfileString(_T("Main"),_T("uid"),A2W(m_strUid.c_str()),strPath);

				ID var(ID::IDT_ID,m_strUid.c_str());

				m_weiboPtr->getMethod()->getUsersShow(var);
				m_weiboPtr->getMethod()->getStatusesFriendTimeline();

			}
			break;
		case WBOPT_GET_USERS_SHOW:
			{
				ParsingUser user;
				user.doParse(objPtr);

				string uid = user.id;
				if (uid == m_strUid)
				{
					string screen_name = user.screen_name;
					DWORD dwNum = MultiByteToWideChar(CP_UTF8,NULL,screen_name.c_str(),-1,NULL,0);
					WCHAR *psText;
					psText = new WCHAR[dwNum];
					if(!psText)
					{
						delete []psText;
					}
					MultiByteToWideChar (CP_UTF8,NULL,screen_name.c_str(),-1,psText,dwNum);

					string profile_image_url = user.profile_image_url;

					CDuiString resPath = CPaintManagerUI::GetResourcePath();

					string picPath(W2A(resPath));
					string relativePath = "Temp//" + uid + ".jpg"; 
					picPath += relativePath;

					m_picDownload.SetPicName(picPath);
					bool bSuccess = m_picDownload.DownloadPic(profile_image_url);

					UpdateUserProfile(psText,A2W(relativePath.c_str()));

					delete[] psText;
				}
			}
			break;
		case WBOPT_POST_STATUSES_UPDATE:
			{
				//m_logInfo.AppendText(_T("\r\nÎ¢²©·¢ËÍ³É¹¦!"));
			}
			break;
		case WBOPT_GET_REMIND_UNREAD_COUNT:
			{
				string strCountUnRead = objPtr->getSubStringByKey("status");
				int count = atoi(strCountUnRead.c_str());

				UpdateUnread(count);
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

void CWeiboManage::OnWeiboRespErrored( unsigned int optionId, const int errCode, const int errSubCode, weibo::ParsingObject* result, const weibo::UserTaskInfo* pTask )
{
	if (optionId == WBOPT_OAUTH2_ACCESS_TOKEN)
	{
		int err = errCode;
	}
}

void CWeiboManage::OnWeiboRespStoped( unsigned int optionId, const weibo::UserTaskInfo* pTask )
{

}

void CWeiboManage::RefreshTimeline(ParsingObjectPtr &parsingObjPtr)
{

 	USES_CONVERSION;
 	ParsingObjectPtr pAllNewWeibo = parsingObjPtr->getSubObjectByKey("statuses");
 
 	if (pAllNewWeibo == NULL)
 	{
 		return;
 	}
 
 	int newWeiboCount = pAllNewWeibo->getSubCounts();
 
 	for (int i = newWeiboCount - 1 ; i >= 0 ; i --)
 	{
 		ParsingObjectPtr pWeibo = pAllNewWeibo->getSubObjectByIndex(i);
 		string strText = pWeibo->getSubStringByKey("text");
 		m_lastWeiboId = _atoi64(pWeibo->getSubStringByKey("id").c_str());
 		ParsingObjectPtr pUser = pWeibo->getSubObjectByKey("user");
 
 		string strUser = "";
 		string profile_image_url = "";
 		string uid = "";
 		if (pUser)
 		{
 			uid = pUser->getSubStringByKey("id");
 			strUser = pUser->getSubStringByKey("screen_name");
 			profile_image_url = pUser->getSubStringByKey("profile_image_url");
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
 			delete []psWeiboText;
 		}
 		MultiByteToWideChar (CP_UTF8,NULL,strText.c_str(),-1,psWeiboText,dwNum);
 
		CDuiString resPath = CPaintManagerUI::GetResourcePath();
 
 		string picPath(W2A(resPath));
 		string relativePath = "Temp//" + uid + ".jpg"; 
 		picPath += relativePath;
 
 		m_picDownload.SetPicName(picPath);
 		bool bSuccess = m_picDownload.DownloadPic(profile_image_url);

		UpdateTimelineList(m_lastWeiboId,psText,psWeiboText,A2W(relativePath.c_str()));



 		delete []psText;
 		delete []psWeiboText;
 	}
//  
//  	CLabelUI *pUnReadTimelineCount = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("unreadTimelineCount")));
//  	if (pUnReadTimelineCount)
//  		pUnReadTimelineCount->SetText(_T(""));
}

bool CWeiboManage::RefreshTimeline()
{
	VariableParams var;
	var.since_id = m_lastWeiboId;
	weibo::eWeiboResultCode res = m_weiboPtr->getMethod()->getStatusesFriendTimeline(&var);
	return res == WRC_OK;
}

void CWeiboManage::StartUp()
{
	m_weiboPtr = weibo::WeiboFactory::getWeibo();

	m_weiboPtr->startup();
	m_weiboPtr->setOption(weibo::WOPT_CONSUMER, APP_KEY, APP_SECRET);

	m_weiboPtr->OnDelegateComplated += std::make_pair(this,&CWeiboManage::OnWeiboRespComplated);
	m_weiboPtr->OnDelegateErrored += std::make_pair(this,&CWeiboManage::OnWeiboRespErrored);
	m_weiboPtr->OnDelegateWillRelease += std::make_pair(this,&CWeiboManage::OnWeiboRespStoped);

}

void CWeiboManage::ShutDown()
{

	m_weiboPtr->OnDelegateComplated -= std::make_pair(this, &CWeiboManage::OnWeiboRespComplated);
	m_weiboPtr->OnDelegateErrored -= std::make_pair(this, &CWeiboManage::OnWeiboRespErrored);
	m_weiboPtr->OnDelegateWillRelease -= std::make_pair(this, &CWeiboManage::OnWeiboRespStoped);
	m_weiboPtr->shutdown();
}

void CWeiboManage::PostNewWeibo( char* pText )
{
	m_weiboPtr->getMethod()->postStatusesUpdate(pText);
}

weibo::IWeiboMethod * CWeiboManage::GetMethod()
{
	return m_weiboPtr->getMethod();
}

weibo::IWeibo * CWeiboManage::GetWeibo()
{
	return m_weiboPtr.get();
}

bool CWeiboManage::CheckExistUser()
{
	USES_CONVERSION;

	TCHAR cPath[MAX_PATH];
	GetModuleFileName(NULL,cPath,MAX_PATH);
	CString strPath = CString(cPath);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strPath += _T("\\Config.ini");

	TCHAR access_token[128] = {0};
	TCHAR uid[128] = {0};

	GetPrivateProfileStringW(_T("Main"),_T("access_token"),_T(""),access_token,128,strPath);
	GetPrivateProfileStringW(_T("Main"),_T("uid"),_T(""),uid,128,strPath);

	CDuiString strUid(uid);
	CDuiString token(access_token);
	if (strUid != _T("") && token != _T(""))
	{
		m_strUid = W2A(strUid);
		m_accessToken = W2A(token);
		return true;
	}
	
	return false;
}

void CWeiboManage::InitWeibo()
{
	m_weiboPtr->setOption(weibo::WOPT_ACCESS_TOKEN,m_accessToken.c_str());
	ID var(ID::IDT_ID,m_strUid.c_str());
	m_weiboPtr->getMethod()->getUsersShow(var);
	m_weiboPtr->getMethod()->getStatusesFriendTimeline();
}

bool CWeiboManage::GetRemindUnreadCount()
{
	weibo::eWeiboResultCode res	= m_weiboPtr->getMethod()->getRemindUnreadCount(m_strUid.c_str());
	return res == WRC_OK;
}
