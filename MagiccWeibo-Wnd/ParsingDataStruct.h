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

		std::string id;///<�û�UID
		std::string screen_name;///< ΢���ǳ�
		std::string name;///< �Ѻ���ʾ���ƣ���Bill Gates,�����м�Ŀո�������ʾ(�������ݲ�֧��)
		std::string province;///< ʡ�ݱ��루�ο�ʡ�ݱ����
		std::string city;///< ���б��루�ο����б����
		std::string location;///<��ַ
		std::string description;///< ��������
		std::string url;///< �û����͵�ַ
		std::string profile_image_url;///< �Զ���ͼ��
		std::string domain;///< �û����Ի�URL
		std::string gender;///< �Ա�,m--�У�f--Ů,n--δ֪
		std::string followers_count;///< ��˿��
		std::string friends_count;///< ��ע��
		std::string statuses_count;///< ΢����
		std::string favourites_count;///< �ղ���
		std::string created_at;///< ����ʱ��
		std::string following;///< �Ƿ��ѹ�ע
		std::string verified;///< ��V��ʾ���Ƿ�΢����֤�û�
		std::string verified_type;///<��֤����
		std::string allow_all_act_msg;///<�Ƿ����������˸��ҷ�˽��
		std::string allow_all_comment;///<�Ƿ����������˶��ҵ�΢����������
		std::string follow_me;///<���û��Ƿ��ע��
		std::string avatar_large;///<��ͷ���ַ
		std::string verified_reason;///<��֤ԭ��
		std::string online_status;///<�û�����״̬
		std::string bi_followers_count;///<������
		std::string remark;///<��ע��Ϣ���ڲ�ѯ�û���ϵʱ�ṩ���ֶΡ�
		std::string lang;///<�û����԰汾

		ParsingStatusPtr status;///<�û�����һ��΢��
	};

	////////////////////////////////////////////////////////////////////////
	// Status
	class  ParsingStatus : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string created_at; ///< ����ʱ��
		std::string id; ///< ΢��ID
		std::string text; ///<΢����Ϣ����
		std::string source; ///< ΢����Դ
		std::string favorited; ///< �Ƿ����ղ�
		std::string in_reply_to_status_id; ///< �ظ�ID
		std::string in_reply_to_user_id; ///< �ظ���UID
		std::string in_reply_to_screen_name; ///< �ظ����ǳ�
		std::string thumbnail_pic; ///< ����ͼ��û��ʱ�����ش��ֶ�
		std::string bmiddle_pic; ///<����ͼƬ��û��ʱ�����ش��ֶ�
		std::string original_pic; ///<ԭʼͼƬ��û��ʱ�����ش��ֶ�
		std::string reposts_count; ///<ת����
		std::string comments_count; ///<������
		std::string mid; ///<΢��MID
		std::string annotations; ///<Ԫ���ݣ�û��ʱ�����ش��ֶ�

		ParsingGeoPtr geo; ///<������Ϣ�����澭γ�ȣ�û��ʱ�����ش��ֶ�
		ParsingUserPtr user; ///< ������Ϣ
		ParsingStatusPtr retweeted_status; ///<ת���Ĳ��ģ�����Ϊstatus���������ת������û�д��ֶ�
	};

	////////////////////////////////////////////////////////////////////////
	// Comment
	class  ParsingComment : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;///< ����ID
		std::string text;///< ��������
		std::string source;///< ������Դ
		std::string created_at;///< ����ʱ��

		ParsingUserPtr user;///< ��������Ϣ,�ṹ�ο�user
		ParsingStatusPtr status;///< ���۵�΢��,�ṹ�ο�status
		ParsingCommentPtr reply_comment;///< ������Դ�����ݽṹ��commentһ��
	};

	////////////////////////////////////////////////////////////////////////
	// Direct message
	class  ParsingDirectMessage : public ParsingBase
	{
	public:
		virtual bool doParse(const ParsingObjectPtr objectPtr);
		virtual const char* getID();

		std::string id;///< ˽��ID
		std::string text;///< ˽������
		std::string sender_id;///< ������UID
		std::string recipient_id;///< ������UID
		std::string created_at;///< ����ʱ��
		std::string sender_screen_name;///< �������ǳ�
		std::string recipient_screen_name;///< �������ǳ�
		std::string fids;///< ������ID���飬û��ʱ�����ش��ֶ�
		std::string status_id;///< ת����΢��ID

		ParsingUserPtr sender;///< ��������Ϣ���ο�user˵��
		ParsingUserPtr recipient;///< ��������Ϣ���ο�user˵��
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
