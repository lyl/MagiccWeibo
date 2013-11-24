#ifndef WEIBOSDK_PARSING_PARSINGDATASTRUCT_HXX
#define WEIBOSDK_PARSING_PARSINGDATASTRUCT_HXX

#include <list>
#include <map>
#include <boost/shared_ptr.hpp>
#include <ParsingObject.hxx>
#include "ParsingDefine.hxx"

namespace weibo
{
	struct BasicInfo;
	struct EducationInfo;
	struct CareerInfo;
}

namespace weibo
{
	////////////////////////////////////////////////////////////////////////
	//Parsing base function
	class  ParsingBase
	{
	public:
		virtual ~ParsingBase();

		// if Return false, the errMsg return error information.
		virtual bool doParse(const char* source, std::string* errMsg = NULL);
		virtual bool doParse(const ParsingObjectPtr objectPtr);

		virtual const char* getID();
	};

	////////////////////////////////////////////////////////////////////////
	// User
	class  ParsingUser
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;///<用户UID
		std::string screen_name;///< 微博昵称
		std::string name;///< 友好显示名称，如Bill Gates,名称中间的空格正常显示(此特性暂不支持)
		std::string province;///< 省份编码（参考省份编码表）
		std::string city;///< 城市编码（参考城市编码表）
		std::string location;///<地址
		std::string description;///< 个人描述
		std::string url;///< 用户博客地址
		std::string profile_image_url;///< 自定义图像
		std::string domain;///< 用户个性化URL
		std::string gender;///< 性别,m--男，f--女,n--未知
		std::string followers_count;///< 粉丝数
		std::string friends_count;///< 关注数
		std::string statuses_count;///< 微博数
		std::string favourites_count;///< 收藏数
		std::string created_at;///< 创建时间
		std::string following;///< 是否已关注
		std::string verified;///< 加V标示，是否微博认证用户
		std::string verified_type;///<认证类型
		std::string allow_all_act_msg;///<是否允许所有人给我发私信
		std::string allow_all_comment;///<是否允许所有人对我的微博进行评论
		std::string follow_me;///<此用户是否关注我
		std::string avatar_large;///<大头像地址
		std::string verified_reason;///<验证原因
		std::string online_status;///<用户在线状态
		std::string bi_followers_count;///<互粉数
		std::string remark;///<备注信息，在查询用户关系时提供此字段。
		std::string lang;///<用户语言版本

		ParsingStatusPtr status;///<用户最新一条微博
	};

	////////////////////////////////////////////////////////////////////////
	// Status
	class  ParsingStatus : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string created_at; ///< 创建时间
		std::string id; ///< 微博ID
		std::string text; ///<微博信息内容
		std::string source; ///< 微博来源
		std::string favorited; ///< 是否已收藏
		std::string in_reply_to_status_id; ///< 回复ID
		std::string in_reply_to_user_id; ///< 回复人UID
		std::string in_reply_to_screen_name; ///< 回复人昵称
		std::string thumbnail_pic; ///< 缩略图，没有时不返回此字段
		std::string bmiddle_pic; ///<中型图片，没有时不返回此字段
		std::string original_pic; ///<原始图片，没有时不返回此字段
		std::string reposts_count; ///<转发数
		std::string comments_count; ///<评论数
		std::string mid; ///<微博MID
		std::string annotations; ///<元数据，没有时不返回此字段

		ParsingGeoPtr geo; ///<地理信息，保存经纬度，没有时不返回此字段
		ParsingUserPtr user; ///< 作者信息
		ParsingStatusPtr retweeted_status; ///<转发的博文，内容为status，如果不是转发，则没有此字段
	};

	////////////////////////////////////////////////////////////////////////
	// Comment
	class  ParsingComment : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;///< 评论ID
		std::string text;///< 评论内容
		std::string source;///< 评论来源
		std::string created_at;///< 评论时间

		ParsingUserPtr user;///< 评论人信息,结构参考user
		ParsingStatusPtr status;///< 评论的微博,结构参考status
		ParsingCommentPtr reply_comment;///< 评论来源，数据结构跟comment一致
	};

	////////////////////////////////////////////////////////////////////////
	// Direct message
	class  ParsingDirectMessage : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;///< 私信ID
		std::string text;///< 私信内容
		std::string sender_id;///< 发送人UID
		std::string recipient_id;///< 接受人UID
		std::string created_at;///< 发送时间
		std::string sender_screen_name;///< 发送人昵称
		std::string recipient_screen_name;///< 接受人昵称
		std::string fids;///< 附件的ID数组，没有时不返回此字段
		std::string status_id;///< 转发到微博ID

		ParsingUserPtr sender;///< 发送人信息，参考user说明
		ParsingUserPtr recipient;///< 接受人信息，参考user说明
	};

	////////////////////////////////////////////////////////////////////////
	// Favorites
	class  ParsingFavorite : public ParsingBase 
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		ParsingStatusPtr status;
		ParsingFavoriteTagsListPtr tags;
		std::string favorited_time;
	};

	////////////////////////////////////////////////////////////////////////
	// Favorites
	class  ParsingFavoriteTag : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;
		std::string tags;
		std::string count;
	};

	////////////////////////////////////////////////////////////////////////
	// Geo
	class  ParsingGeo : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
	};

	////////////////////////////////////////////////////////////////////////
	// Account
	class  ParsingAccount : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		boost::shared_ptr<weibo::BasicInfo> mBasicPtr;
	};

	////////////////////////////////////////////////////////////////////////
	// Education
	class  ParsingEducation : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		boost::shared_ptr<weibo::EducationInfo> mEducationPtr;
	};

	////////////////////////////////////////////////////////////////////////
	// Career
	class  ParsingCareer : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		boost::shared_ptr<weibo::CareerInfo> mCareerPtr;
	};

	////////////////////////////////////////////////////////////////////////
	// Parsing tag
	class  ParsingTag : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;
		std::string value;
		std::string weight;
	};

	////////////////////////////////////////////////////////////////////////
	// Parsing tag
	class  ParsingTrend : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string num;
		std::string hotword;
		std::string trend_id;
	};

	////////////////////////////////////////////////////////////////////////
	// 
	class  ParsingLimit : public ParsingBase 
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);

		std::string ip_limit;
		std::string limit_time_unit;
		std::string remaining_ip_hits;
		std::string remaining_user_hits;
		std::string reset_time;
		std::string reset_time_in_seconds;
		std::string user_limit;
	};

	////////////////////////////////////////////////////////////////////////
	// Result
	class  ParsingResult : public ParsingBase
	{
	public:
		typedef std::list<std::string> ResultKeyList;
		typedef std::map<std::string, std::string> ResultMap;

		ParsingResult(const ResultKeyList &keyList);
		virtual bool doParse(const ParsingObjectPtr objectPtr);
        
        const char* asAString(const char* key);

		ResultKeyList _reulstKeylist;
		ResultMap _resultMap;
	};

	// Error
	class  ParsingApiError : public ParsingBase
	{
	public:
		ParsingApiError(bool usingV3Parse = false);

		virtual bool doParse(const char* source, std::string *errMsg = NULL);
		virtual bool doParse(const ParsingObjectPtr objectPtr);

		std::string error_code;
		std::string request;
		std::string error;

	private:
		bool mUsingV3Parse;
	};

	// Oauth token.
	class  ParsingOauthRet : public ParsingBase
	{
	public:
		ParsingOauthRet(bool usingV3Parse = false);

		virtual bool doParse(const char* source, std::string *errMsg = NULL);
		virtual bool doParse(const ParsingObjectPtr objectPtr);

		std::string expires_in;
		std::string refresh_token;

		std::string access_token;
		std::string access_secret;
		std::string uid;

	private:
		bool mUsingV3Parse;
	};

	// List
	template<typename TData>
	class  ParsingList : public ParsingBase
	{
	public:
		typedef TData ElementDataType;
		typedef boost::shared_ptr<ElementDataType> TDataPtr;
		typedef std::list<TDataPtr> TParsingList;

		ParsingList(const char* tag = "")
			: mParsingTag(tag)
			, previous_cursor(0)
			, next_cursor(0)
			, total_number(0)
		{
		}

		virtual bool doParse(const ParsingObjectPtr objectPtr)
		{
			if (objectPtr && objectPtr->isUseable())
			{
				ParsingObjectPtr subObjPtr;
				if (mParsingTag.empty())
				{
					subObjPtr = objectPtr;//->getSubObjectByIndex(0);
				}
				else
				{
					subObjPtr = objectPtr->getSubObjectByKey(mParsingTag.c_str());
				}

				if (subObjPtr)
				{
					subObjPtr->enumAllSub(EnumAllStatusesCallBack, &mDataList);
				}

				previous_cursor = (unsigned int)objectPtr->getSubNumbericByKey("previous_cursor");
				next_cursor = (unsigned int)objectPtr->getSubNumbericByKey("next_cursor");
				total_number = (unsigned int)objectPtr->getSubNumbericByKey("total_number");
				return true;
			}
			return false;
		}

		TParsingList mDataList;
		unsigned int previous_cursor;
		unsigned int next_cursor;
		unsigned int total_number;

	protected:
		static void EnumAllStatusesCallBack(const ParsingObjectPtr object, void* usrData)
		{
            TParsingList* list = (TParsingList*)usrData;
			if (list)
			{
				TDataPtr dataPtr;//
				dataPtr.reset(new ElementDataType());

				if (dataPtr)
				{
					dataPtr->doParse(object);
					list->push_back(dataPtr);
				}
			}
		}
		std::string mParsingTag;
	};
}

#endif //PARSING_PARSINGDATASTRUCT_HXX
