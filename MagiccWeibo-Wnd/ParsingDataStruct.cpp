#include "stdafx.h"
#include <string.h>
#include "ParsingDataStruct.h"
#include <IWeiboDef.hxx>
#include "make_shared.hpp"

using namespace weibo;

ParsingBase::~ParsingBase()
{
}

bool ParsingBase::doParse(const char* source, std::string* errMsg)
{
	if (!source || source[0] != '\0')
	{
		return false;
	}

	ParsingObjectPtr objectPtr = make_shared<ParsingObject>(source);
	if (objectPtr->isUseable())
	{
		doParse(objectPtr);
		return true;
	}
	else
	{
		if (errMsg)
		{
			objectPtr->getErrorMessage();
		}
	}
	return false;
}

bool ParsingBase::doParse(const ParsingObjectPtr objectPtr)
{
	// Do noting!
	return false;
}

const char* ParsingBase::getID()
{
	return "";
}

////////////////////////////////////////////////////////////////////////
// User
bool ParsingUser::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		id = objectPtr->getSubStringByKey("id");
		screen_name = objectPtr->getSubStringByKey("screen_name");
		name = objectPtr->getSubStringByKey("name");
		province = objectPtr->getSubStringByKey("province");
		city = objectPtr->getSubStringByKey("city");
		location = objectPtr->getSubStringByKey("location");
		description = objectPtr->getSubStringByKey("description");
		url = objectPtr->getSubStringByKey("url");
		profile_image_url = objectPtr->getSubStringByKey("profile_image_url");
		domain = objectPtr->getSubStringByKey("domain");
		gender = objectPtr->getSubStringByKey("gender");
		followers_count = objectPtr->getSubStringByKey("followers_count");
		friends_count = objectPtr->getSubStringByKey("friends_count");
		statuses_count = objectPtr->getSubStringByKey("statuses_count");
		favourites_count = objectPtr->getSubStringByKey("favourites_count");
		created_at = objectPtr->getSubStringByKey("created_at");
		following = objectPtr->getSubStringByKey("following");
		verified = objectPtr->getSubStringByKey("verified");
		verified_type = objectPtr->getSubStringByKey("verified_type");
		allow_all_act_msg = objectPtr->getSubStringByKey("allow_all_act_msg");
		allow_all_comment = objectPtr->getSubStringByKey("allow_all_comment");
		follow_me = objectPtr->getSubStringByKey("follow_me");
		avatar_large = objectPtr->getSubStringByKey("avatar_large");
		verified_reason = objectPtr->getSubStringByKey("verified_reason");
		online_status = objectPtr->getSubStringByKey("online_status");
		bi_followers_count = objectPtr->getSubStringByKey("bi_followers_count");
		remark = objectPtr->getSubStringByKey("remark");
		lang = objectPtr->getSubStringByKey("lang");

		// status
		status.reset();
		ParsingObjectPtr objectStatusPtr = objectPtr->getSubObjectByKey("retweeted_status");
		if (objectStatusPtr)
		{
			status = make_shared<ParsingStatus>();
			if (status)
			{
				status->doParse(objectStatusPtr);
			}
		}
		return true;
	}
	return false;
}

const char* ParsingUser::getID()
{
	return id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Status
bool ParsingStatus::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{

		created_at = objectPtr->getSubStringByKey("created_at");
		id = objectPtr->getSubStringByKey("id");
		text = objectPtr->getSubStringByKey("text");
		source = objectPtr->getSubStringByKey("source");
		favorited = objectPtr->getSubStringByKey("favorited");
		in_reply_to_status_id = objectPtr->getSubStringByKey("in_reply_to_status_id");
		in_reply_to_user_id = objectPtr->getSubStringByKey("in_reply_to_user_id");
		in_reply_to_screen_name = objectPtr->getSubStringByKey("in_reply_to_screen_name");
		thumbnail_pic = objectPtr->getSubStringByKey("thumbnail_pic");
		bmiddle_pic = objectPtr->getSubStringByKey("bmiddle_pic");
		original_pic = objectPtr->getSubStringByKey("original_pic");
		reposts_count = objectPtr->getSubStringByKey("reposts_count");
		comments_count = objectPtr->getSubStringByKey("comments_count");
		mid = objectPtr->getSubStringByKey("mid");
		annotations = objectPtr->getSubStringByKey("annotations");

		// geo
		geo.reset();
		ParsingObjectPtr objectGeoPtr = objectPtr->getSubObjectByKey("geo");
		if (objectGeoPtr)
		{
			geo = make_shared<ParsingGeo>();
			if (geo)
			{
				geo->doParse(objectGeoPtr);
			}
		}

		// user
		user.reset();
		ParsingObjectPtr objectUserPtr = objectPtr->getSubObjectByKey("user");
		if (objectUserPtr)
		{
			user = make_shared<ParsingUser>();
			if (user)
			{
				user->doParse(objectUserPtr);
			}
		}

		// retweeted_status
		retweeted_status.reset();
		ParsingObjectPtr objectRetweetedPtr = objectPtr->getSubObjectByKey("retweeted_status");
		if (objectRetweetedPtr)
		{
			retweeted_status = make_shared<ParsingStatus>();
			if (retweeted_status)
			{
				retweeted_status->doParse(objectRetweetedPtr);
			}
		}
		return true;
	}
	return false;
}

const char* ParsingStatus::getID()
{
	return id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Comment
bool ParsingComment::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		id = objectPtr->getSubStringByKey("id");
		text = objectPtr->getSubStringByKey("text");
		source = objectPtr->getSubStringByKey("source");
		created_at = objectPtr->getSubStringByKey("created_at");

		// user
		user.reset();
		ParsingObjectPtr objectUserPtr = objectPtr->getSubObjectByKey("user");
		if (objectUserPtr)
		{
			user = make_shared<ParsingUser>();
			if (user)
			{
				user->doParse(objectUserPtr);
			}
		}

		// status
		status.reset();
		ParsingObjectPtr objectStatusPtr = objectPtr->getSubObjectByKey("status");
		if (objectStatusPtr)
		{
			status = make_shared<ParsingStatus>();
			if (status)
			{
				status->doParse(objectStatusPtr);
			}
		}

		// status
		reply_comment.reset();
		ParsingObjectPtr objectReplyCommentPtr = objectPtr->getSubObjectByKey("reply_comment");
		if (objectReplyCommentPtr)
		{
			reply_comment = make_shared<ParsingComment>();
			if (reply_comment)
			{
				reply_comment->doParse(objectReplyCommentPtr);
			}
		}
		return true;
	}
	return false;
}

const char* ParsingComment::getID()
{
	return id.c_str();
}

////////////////////////////////////////////////////////////////////////
// DirectMessage
bool ParsingDirectMessage::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		id = objectPtr->getSubStringByKey("id");
		text = objectPtr->getSubStringByKey("text");
		sender_id = objectPtr->getSubStringByKey("sender_id");
		recipient_id = objectPtr->getSubStringByKey("recipient_id");
		created_at = objectPtr->getSubStringByKey("created_at");
		sender_screen_name = objectPtr->getSubStringByKey("sender_screen_name");
		recipient_screen_name = objectPtr->getSubStringByKey("recipient_screen_name");
		fids = objectPtr->getSubStringByKey("fids");
		status_id = objectPtr->getSubStringByKey("status_id");

		// user
		sender.reset();
		ParsingObjectPtr objectSender = objectPtr->getSubObjectByKey("sender");
		if (objectSender)
		{
			sender = make_shared<ParsingUser>();
			if (sender)
			{
				sender->doParse(objectSender);
			}
		}

		// recipient
		recipient.reset();
		ParsingObjectPtr objectRecipient = objectPtr->getSubObjectByKey("recipient");
		if (objectRecipient)
		{
			recipient = make_shared<ParsingUser>();
			if (recipient)
			{
				recipient->doParse(objectRecipient);
			}
		}
		return true;
	}
	return false;
}

const char* ParsingDirectMessage::getID()
{
	return id.c_str();
}

////////////////////////////////////////////////////////////////////////
// ParsingFavorite
bool ParsingFavorite::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		tags.reset();
		ParsingObjectPtr objTags = objectPtr->getSubObjectByKey("tags");
		if (objTags)
		{
			tags = make_shared<ParsingFavoriteTagsList>("");
			if (tags)
			{
				tags->doParse(objTags);
			}
		}

		status.reset();
		ParsingObjectPtr objStatus = objectPtr->getSubObjectByKey("status");
		if (objStatus)
		{
			status = make_shared<ParsingStatus>();
			if (status )
			{
				status ->doParse(objStatus);
			}
		}
		favorited_time = objectPtr->getSubStringByKey("favorited_time");
	}
	return false;
}

const char* ParsingFavorite::getID()
{
	return status->id.c_str();
}

bool ParsingFavoriteTag::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr)
	{
		id = objectPtr->getSubStringByKey("id");
		tags = objectPtr->getSubStringByKey("tags");
		count = objectPtr->getSubStringByKey("count");
		return true;
	}
	return false;
}

const char* ParsingFavoriteTag::getID()
{
	return id.c_str();
}


////////////////////////////////////////////////////////////////////////
// Geo
bool ParsingGeo::doParse(const ParsingObjectPtr objectPtr)
{
	return false;
}

////////////////////////////////////////////////////////////////////////
// Account
bool ParsingAccount::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		if (!mBasicPtr)
		{
			mBasicPtr = make_shared<struct weibo::BasicInfo>();
		}

		mBasicPtr->id = objectPtr->getSubStringByKey("id");
		mBasicPtr->name = objectPtr->getSubStringByKey("name");
		mBasicPtr->screen_name = objectPtr->getSubStringByKey("screen_name");
		mBasicPtr->city = objectPtr->getSubStringByKey("city");
		mBasicPtr->province = objectPtr->getSubStringByKey("province");
		mBasicPtr->location = objectPtr->getSubStringByKey("location");
		mBasicPtr->created_at = objectPtr->getSubStringByKey("created_at");
		mBasicPtr->description = objectPtr->getSubStringByKey("description");
		mBasicPtr->domain = objectPtr->getSubStringByKey("domain");
		mBasicPtr->gender = objectPtr->getSubStringByKey("gender");
		mBasicPtr->credentials_num = objectPtr->getSubStringByKey("credentials_num");
		mBasicPtr->credentials_type = objectPtr->getSubStringByKey("credentials_type");
		mBasicPtr->lang = objectPtr->getSubStringByKey("lang");
		mBasicPtr->profile_image_url = objectPtr->getSubStringByKey("profile_image_url");
		mBasicPtr->birthday = objectPtr->getSubStringByKey("birthday");
		mBasicPtr->birthday_visible = objectPtr->getSubStringByKey("birthday_visible");
		mBasicPtr->email = objectPtr->getSubStringByKey("email");
		mBasicPtr->email_visible = objectPtr->getSubStringByKey("email_visible");
		mBasicPtr->msn = objectPtr->getSubStringByKey("msn");
		mBasicPtr->msn_visible = objectPtr->getSubStringByKey("msn_visible");
		mBasicPtr->qq = objectPtr->getSubStringByKey("qq");
		mBasicPtr->qq_visible = objectPtr->getSubStringByKey("qq_visible");
		mBasicPtr->real_name = objectPtr->getSubStringByKey("real_name");
		mBasicPtr->real_name_visible = objectPtr->getSubStringByKey("real_name_visible");
		mBasicPtr->url_string = objectPtr->getSubStringByKey("url_string");
		mBasicPtr->url_visible = objectPtr->getSubStringByKey("url_visible");

		return true;
	}
	return false;
}

const char* ParsingAccount::getID()
{
	return mBasicPtr->id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Education
bool ParsingEducation::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		if (!mEducationPtr)
		{
			mEducationPtr = make_shared<struct weibo::EducationInfo>();
		}

		mEducationPtr->id = objectPtr->getSubStringByKey("id");
		mEducationPtr->type = objectPtr->getSubStringByKey("type");
		mEducationPtr->school = objectPtr->getSubStringByKey("school");
		mEducationPtr->department = objectPtr->getSubStringByKey("department");
		mEducationPtr->year = objectPtr->getSubStringByKey("year");
		mEducationPtr->visible = objectPtr->getSubStringByKey("visible");

		return true;
	}
	return false;
}

const char* ParsingEducation::getID()
{
	return mEducationPtr->id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Career
bool ParsingCareer::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		if (!mCareerPtr)
		{
			mCareerPtr = make_shared<struct weibo::CareerInfo>();
		}

		mCareerPtr->id = objectPtr->getSubStringByKey("id");
		mCareerPtr->city = objectPtr->getSubStringByKey("city");
		mCareerPtr->province = objectPtr->getSubStringByKey("province");
		mCareerPtr->start = objectPtr->getSubStringByKey("start");
		mCareerPtr->end = objectPtr->getSubStringByKey("end");
		mCareerPtr->company = objectPtr->getSubStringByKey("company");
		mCareerPtr->department = objectPtr->getSubStringByKey("department");
		mCareerPtr->visible = objectPtr->getSubStringByKey("visible");

		return true;
	}
	return false;
}

const char* ParsingCareer::getID()
{
	return mCareerPtr->id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Parsing tag
bool ParsingTag::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		id = objectPtr->getKeyName();
		if (!id.empty())
		{
			value = objectPtr->getSubStringByKey(id.c_str());
		}
		weight = objectPtr->getSubStringByKey("weight");

		return true;
	}
	return false;
}

const char* ParsingTag::getID()
{
	return id.c_str();
}

////////////////////////////////////////////////////////////////////////
// Parsing trend
bool ParsingTrend::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		num = objectPtr->getSubStringByKey("num");
		hotword = objectPtr->getSubStringByKey("hotword");
		trend_id = objectPtr->getSubStringByKey("trend_id");
		return true;
	}
	return false;
}

const char* ParsingTrend::getID()
{
	return trend_id.c_str();
}


////////////////////////////////////////////////////////////////////////
// Limite
bool ParsingLimit::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		ip_limit = objectPtr->getSubStringByKey("ip_limit");
		limit_time_unit = objectPtr->getSubStringByKey("limit_time_unit");
		remaining_ip_hits = objectPtr->getSubStringByKey("remaining_ip_hits");
		remaining_user_hits = objectPtr->getSubStringByKey("remaining_user_hits");
		reset_time = objectPtr->getSubStringByKey("reset_time");
		reset_time_in_seconds = objectPtr->getSubStringByKey("reset_time_in_seconds");
		user_limit = objectPtr->getSubStringByKey("user_limit");

		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
// Result
ParsingResult::ParsingResult(const ResultKeyList &keyList)
: _reulstKeylist(keyList)
{
}

bool ParsingResult::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr->isUseable())
	{
		ResultKeyList::iterator it = _reulstKeylist.begin();
		while (it != _reulstKeylist.end())
		{
			if (!it->empty())
			{
				_resultMap.insert(std::make_pair(it->c_str(), objectPtr->getSubStringByKey(it->c_str())));
			}
			++ it;
		}
		return true;
	}
	return false;
}

const char* ParsingResult::asAString(const char* key)
{
	ResultMap::iterator it = _resultMap.find(key);
	if (it != _resultMap.end())
	{
		return it->second.c_str();
	}
	return NULL;
}

int split_url_param(const char*& next, const char*& key, const char*& qe, const char*& split, const char endflag)
{
	if( !next || *next == '\0' )
		return -1;

	key = next; 

	// 前面的空格除掉
	do
	{
		if (*key != 0x20 || *key == '\0')
		{
			break;
		}
		++ key;
	}
	while(1);

	qe = strchr(key, '=');
	if (!qe)
	{
		return -1;
	}

	split = strchr((qe+1), endflag);

	if(split)
	{
		next = (split + 1 );
	}
	else
	{
		next = 0;
	}
	return 0;
}

int split_url_copy_keyval(char* val , const char* start , const char* end)
{
	if (!val || !start || *start == '\0')
	{
		return -1;
	}

	if (end && end <= start)
	{
		return -1;
	}

	if (!end || *end == '\0')
	{
		strcpy(val, start );
	}
	else
	{
		strncpy(val, start, end - start);
	}
	return 0;
}

/**
* split and parse URL parameters replied by the test-server
* into <em>oauth_token</em> and <em>oauth_token_secret</em>.
*/
int wb_parse_oauth(const char *reply, char *token, char *secret, char* userid)
{
	int tokenok = 0;
	int secretok = 0; 
	const char* key = 0;
	const char* qe  = 0;
	const char* split = 0;
	const char* s = reply;

	while (0 == split_url_param(s, key, qe, split, '&'))
	{
		if((strncmp(key,"oauth_token_secret=",18 ) == 0) && secret)
		{
			split_url_copy_keyval(secret, (qe + 1), split);
			secretok = 1;
		}
		else if((strncmp(key, "oauth_token=", 11) == 0) && token)
		{
			split_url_copy_keyval(token, (qe + 1), split);
			tokenok = 1;
		}
		else if((strncmp(key,"user_id=", 7) == 0) && userid)
		{
			split_url_copy_keyval(userid, (qe + 1), split); 
		}
	}
	return (tokenok || secretok);
}


////////////////////////////////////////////////////////////////////////
// App Error
ParsingApiError::ParsingApiError(bool usingV3Parse)
: mUsingV3Parse(usingV3Parse)
{
}

bool ParsingApiError::doParse(const char* source, std::string *errMsg)
{
	//if (mUsingV3Parse)
	//{
	//	split_url_param();
	//}
	//else
	//{
	//	return __super::doParse(source);
	//}
	//return false;
	return ParsingBase::doParse(source, errMsg);
}

bool ParsingApiError::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		error_code = objectPtr->getSubStringByKey("error_code");
		request = objectPtr->getSubStringByKey("request");
		error = objectPtr->getSubStringByKey("error");
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
// Oauth parse
ParsingOauthRet::ParsingOauthRet(bool usingV3Parse)
: mUsingV3Parse(usingV3Parse)
{

}

bool ParsingOauthRet::doParse(const char* source, std::string *errMsg)
{
	if (!source || source[0] != '\0')
	{
		return false;
	}

	bool ret = false;
	if (mUsingV3Parse)
	{
		char oauthToken[255] = { 0 };
		char oauthSecret[255] = { 0 };
		char oauthUid[255] = { 0 };
		wb_parse_oauth(source, (char*)oauthToken, oauthSecret, oauthUid);
		access_token = oauthToken;
		access_token = oauthSecret;
		uid = oauthUid;
		ret = true;
	}
	else
	{
		ret = ParsingBase::doParse(source, errMsg);
	}
	return ret;
}

bool ParsingOauthRet::doParse(const ParsingObjectPtr objectPtr)
{
	if (objectPtr && objectPtr->isUseable())
	{
		access_token = objectPtr->getSubStringByKey("access_token");
		expires_in = objectPtr->getSubStringByKey("expires_in");
		refresh_token = objectPtr->getSubStringByKey("refresh_token");
		uid = objectPtr->getSubStringByKey("uid");
		return true;
	}
	return false;
}
