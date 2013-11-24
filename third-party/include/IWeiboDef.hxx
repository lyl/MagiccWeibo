#ifndef WEIBOSDK_IWEIBODEF_HXX
#define WEIBOSDK_IWEIBODEF_HXX

#include <string>

namespace weibo
{
	/** Please refer to the document for open api V4*/
	struct VariableParams
	{
		VariableParams()
		{
			// based variable
			since_id = 0;
			max_id = 0;
			count = 0;
			page = 0;
			base_app = 0;
			feature = 0;
			is_encoded = 0;

			// variable for statuses
			filter_by_source = 0;
			filter_by_author = 0;
			filter_by_type = 0;
			trim_user = 0;
			trim_status = 0;
			sort = 0;
			cursor = 0;
		}

		std::ostream& operator << (std::ostream &os)
		{
			return os;
		}

		// based variable
		long long since_id;
		long long max_id;
		int count;
		int page;
		int base_app;
		int feature;
		int is_encoded;
		int sort;
		int cursor; //first page is -1,if next_cursor == 0, page end.

		// variable for statuses
		int filter_by_source;
		int filter_by_author;
		int filter_by_type;
		int trim_user;
		int trim_status;
		std::string simplify;
	};

	struct ID
	{
		enum IDType
		{
			IDT_ID,
			IDT_SCREENNAME,
		};

		ID(IDType type, const char *text, const char* key = NULL)
			: idType(type)
			, id(text ? text : "")
			, keyName(key ? keyName : "")
		{
		}

		bool isEmpty()
		{
			return id.empty();
		}

		IDType idType;
		std::string id;
		std::string keyName;
	};

	enum eWeiboRequestFormat
	{
		WRF_UNKNOW = -1,
		WRF_JSON,
		WRF_XML,
	};

	enum eWeiboResultCode
	{
		WRC_UNKNOW = -1,
		WRC_OK,
		WRC_USERID_NULL,
		WRC_WEIBOID_NULL,
		WRC_LISTID_NULL,
		WRC_TAGID_NULL,
		WRC_TEXT_NULL,
		WRC_PASSWORD_NULL,
		WRC_SOURCE_NULL, ///< App key or app secret is null.
		WRC_TOKEN_NULL,  ///< Access token or access secret is null.
		WRC_FILEPATH_NULL,///< File path is null.
		WRC_NOT_IMPL,///< 
		WRC_INVALIDE_PARAM,
		WRC_INTERNAL_ERROR, ///< Internal error.
		WRC_TASK_EXIST, ///< Already has this task.
	};

	enum eWeiboProxyType
	{
		EPT_NONE,
		EPT_HTTP,
		EPT_SOCKS4,
		EPT_SOCKS5,
	};

	enum eWeiboOption
	{
		WOPT_CONSUMER,     ///< const char *appkey, const char *appsecret
		WOPT_PROXY,        ///< eWeiboProxyType type, char *host, int port, char *proxyuser, char *password
		WOPT_RESPONSE_FORMAT, ///< const eWeiboRequestFormat format.
		WOPT_ACCESS_TOKEN, ///< const char* accesstoken.
		WOPT_LOG_FILE, ///< const char* fullLogFileName
	};

	enum eWeiboPriorityLevel
	{
		TPL_NORMAL,
		TPL_HIGH,
		TPL_IMMED,
	};

	struct UserTaskInfo
	{
		char mTaskId[255];
		void *mUsrData;
	};

	// For http response code.
	enum eWeiboErrorCode
	{
		WERR_UNKNOW = -1,
		WERR_OK,
		WERR_CURL,     ///< Sub code: reference eWeiboErrorSubCode.
		WERR_PROTOCOL, ///< Sub code: OK == 200.
	};

	enum eWeiboErrorSubCode
	{
		WES_OK = 0,
		WES_UNSUPPORTED_PROTOCOL,    /* 1 */
		WES_FAILED_INIT,             /* 2 */
		WES_URL_MALFORMAT,           /* 3 */
		WES_OBSOLETE4,               /* 4 - NOT USED */
		WES_COULDNT_RESOLVE_PROXY,   /* 5 */
		WES_COULDNT_RESOLVE_HOST,    /* 6 */
		WES_COULDNT_CONNECT,         /* 7 */
		WES_FTP_WEIRD_SERVER_REPLY,  /* 8 */
		WES_REMOTE_ACCESS_DENIED,    /* 9 a service was denied by the server
									due to lack of access - when login fails
									this is not returned. */
		WES_OBSOLETE10,              /* 10 - NOT USED */
		WES_FTP_WEIRD_PASS_REPLY,    /* 11 */
		WES_OBSOLETE12,              /* 12 - NOT USED */
		WES_FTP_WEIRD_PASV_REPLY,    /* 13 */
		WES_FTP_WEIRD_227_FORMAT,    /* 14 */
		WES_FTP_CANT_GET_HOST,       /* 15 */
		WES_OBSOLETE16,              /* 16 - NOT USED */
		WES_FTP_COULDNT_SET_TYPE,    /* 17 */
		WES_PARTIAL_FILE,            /* 18 */
		WES_FTP_COULDNT_RETR_FILE,   /* 19 */
		WES_OBSOLETE20,              /* 20 - NOT USED */
		WES_QUOTE_ERROR,             /* 21 - quote command failure */
		WES_HTTP_RETURNED_ERROR,     /* 22 */
		WES_WRITE_ERROR,             /* 23 */
		WES_OBSOLETE24,              /* 24 - NOT USED */
		WES_UPLOAD_FAILED,           /* 25 - failed upload "command" */
		WES_READ_ERROR,              /* 26 - couldn't open/read from file */
		WES_OUT_OF_MEMORY,           /* 27 */
		/* Note: WES_OUT_OF_MEMORY may sometimes indicate a conversion error
		   instead of a memory allocation error if CURL_DOES_CONVERSIONS
		   is defined
		*/
		WES_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
		WES_OBSOLETE29,              /* 29 - NOT USED */
		WES_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
		WES_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
		WES_OBSOLETE32,              /* 32 - NOT USED */
		WES_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
		WES_HTTP_POST_ERROR,         /* 34 */
		WES_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
		WES_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
		WES_FILE_COULDNT_READ_FILE,  /* 37 */
		WES_LDAP_CANNOT_BIND,        /* 38 */
		WES_LDAP_SEARCH_FAILED,      /* 39 */
		WES_OBSOLETE40,              /* 40 - NOT USED */
		WES_FUNCTION_NOT_FOUND,      /* 41 */
		WES_ABORTED_BY_CALLBACK,     /* 42 */
		WES_BAD_FUNCTION_ARGUMENT,   /* 43 */
		WES_OBSOLETE44,              /* 44 - NOT USED */
		WES_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
		WES_OBSOLETE46,              /* 46 - NOT USED */
		WES_TOO_MANY_REDIRECTS ,     /* 47 - catch endless re-direct loops */
		WES_UNKNOWN_TELNET_OPTION,   /* 48 - User specified an unknown option */
		WES_TELNET_OPTION_SYNTAX ,   /* 49 - Malformed telnet option */
		WES_OBSOLETE50,              /* 50 - NOT USED */
		WES_PEER_FAILED_VERIFICATION, /* 51 - peer's certificate or fingerprint
									 wasn't verified fine */
		WES_GOT_NOTHING,             /* 52 - when this is a specific error */
		WES_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
		WES_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as
									default */
		WES_SEND_ERROR,              /* 55 - failed sending network data */
		WES_RECV_ERROR,              /* 56 - failure in receiving network data */
		WES_OBSOLETE57,              /* 57 - NOT IN USE */
		WES_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
		WES_SSL_CIPHER,              /* 59 - couldn't use specified cipher */
		WES_SSL_CACERT,              /* 60 - problem with the CA cert (path?) */
		WES_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized transfer encoding */
		WES_LDAP_INVALID_URL,        /* 62 - Invalid LDAP URL */
		WES_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
		WES_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
		WES_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind
									that failed */
		WES_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
		WES_LOGIN_DENIED,            /* 67 - user, password or similar was not
									accepted and we failed to login */
		WES_TFTP_NOTFOUND,           /* 68 - file not found on server */
		WES_TFTP_PERM,               /* 69 - permission problem on server */
		WES_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
		WES_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
		WES_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
		WES_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
		WES_TFTP_NOSUCHUSER,         /* 74 - No such user */
		WES_CONV_FAILED,             /* 75 - conversion failed */
		WES_CONV_REQD,               /* 76 - caller must register conversion
									callbacks using curl_easy_setopt options
									CURLOPT_CONV_FROM_NETWORK_FUNCTION,
									CURLOPT_CONV_TO_NETWORK_FUNCTION, and
									CURLOPT_CONV_FROM_UTF8_FUNCTION */
		WES_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing
									or wrong format */
		WES_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
		WES_SSH,                     /* 79 - error from the SSH layer, somewhat
									generic so the error message will be of
									interest when this has happened */

		WES_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL
									connection */
		WES_AGAIN,                   /* 81 - socket is not ready for send/recv,
									wait till it's ready and try again (Added
									in 7.18.2) */
		WES_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or
									wrong format (Added in 7.19.0) */
		WES_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in
									7.19.0) */
		WES_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
		WES_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
		WES_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Identifiers */
		WES_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
		WES_CHUNK_FAILED,            /* 88 - chunk callback reported error */
	};

	struct BasicInfo
	{
		std::string id; //用户UID
		std::string name; //用户名
		std::string screen_name; //用户昵称
		std::string city; //所在城市代码ID
		std::string province; //所在省份代码ID
		std::string location; //所在地信息
		std::string created_at; //用户创建时间
		std::string description; //用户描述信息
		std::string domain; //个性化域名
		std::string gender; //性别，m：男、f：女
		std::string credentials_num; //证件号码
		std::string credentials_type; //证件类型
		std::string lang; //语言设置
		std::string profile_image_url; //头像地址
		std::string birthday; //生日信息
		std::string birthday_visible; //生日隐私类型，0：保密、1：只显示月日、2：只显示星座、3：所有人可见
		std::string email; //联系邮箱地址
		std::string email_visible; //邮箱地址隐私类型，0：自己可见、1：我关注人可见、2：所有人可见
		std::string msn; //账号信息
		std::string msn_visible; //账号隐私类型，0：自己可见、1：我关注人可见、2：所有人可见
		std::string qq; //号码
		std::string qq_visible; //号码隐私类型，0：自己可见、1：我关注人可见、2：所有人可见
		std::string real_name; //真实姓名
		std::string real_name_visible; //真实姓名隐私类型，0：自己可见、1：我关注人可见、2：所有人可见
		std::string url_string; //用户博客地址
		std::string url_visible; //用户博客地址隐私类型，0：自己可见、1：我关注人可见、2：所有人可见
	};

	struct EducationInfo
	{
		std::string id; //学校ID
		std::string type;//学校类型，1：大学、2：高中、3：中专技校、4：初中、5：小学
		std::string school;//学校名称
		std::string department;//学校院系名称
		std::string year;//入学年份
		std::string visible;//可见设置类型，0：自己可见、1：我关注人可见、2：所有人可见
	};

	struct CareerInfo
	{
		std::string id;//公司ID
		std::string city;//城市代码ID
		std::string province;//省份代码ID
		std::string start;//入职时间
		std::string end;//离职时间
		std::string company;//公司名称
		std::string department;//公司部门名称
		std::string visible;//可见设置类型，0：自己可见、1：我关注人可见、2：所有人可见
	};
}


#endif //WEIBOSDK_IWEIBODEFINE_HXX