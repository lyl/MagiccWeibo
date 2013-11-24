#ifndef WEIBOSDK_IWEIBOMETHOD_HXX
#define WEIBOSDK_IWEIBOMETHOD_HXX

#include "compat.hxx"
#include "IWeiboDef.hxx"


/** Weibo interface for weibo v4
* Please reference http://open.weibo.com/wiki/API%E6%96%87%E6%A1%A3_V2 
* 
* @author welbon
*
* @Email libo.weng@gmail.com
* 
* @date 2011-09-06
*/
namespace weibo
{
	enum eMethodAction
	{
		WBOPT_NONE,

		WBOPT_OAUTH2_ACCESS_TOKEN,
		WBOPT_OAUTH2_AUTHORIZE,
		WBOPT_END_SESSION,

		WBOPT_GET_STATUSES_PUBLIC_TIMELINE,//��ȡ���¸��µĹ���΢����Ϣ 
		WBOPT_GET_STATUSES_FRIENDS_TIMELINE,//��ȡ��ǰ�û�����ע�û�������΢����Ϣ (����: statuses/home_timeline) 
		WBOPT_GET_STATUSES_HOME_TIMELINE,//��ȡ��ǰ��¼�û���������ע�û�������΢����Ϣ
		WBOPT_GET_STATUSES_USER_TIMELINE,//��ȡ�û�������΢����Ϣ�б� 
		WBOPT_GET_STATUSES_TIMELINE_BATCH,//�������ָ����ĳһ���û���timeline
		WBOPT_GET_STATUSES_REPOST_TIMELINE,//����һ��΢��������n��ת��΢����Ϣ
		WBOPT_GET_STATUSES_REPOST_BYME,//�����û�ת��������n��΢����Ϣ
		WBOPT_GET_STATUSES_MENTIONS,//��ȡ@��ǰ�û���΢���б� 
		WBOPT_GET_STATUSES_SHOW,//����ID��ȡ����΢����Ϣ
		WBOPT_GET_STATUSES_SHOW_BATCH,//������ȡ΢����Ϣ
		WBOPT_GET_STATUSES_QUERYMID,//ͨ��id��ȡmid
		WBOPT_GET_STATUSES_QUERYID,//ͨ��mid��ȡid
		WBOPT_GET_STATUSES_REPOST_DAILY,//���췵������ת����
		WBOPT_GET_STATUSES_REPOST_WEEKLY,//���ܷ�������ת����
		WBOPT_GET_STATUSES_HOT_COMMENTS_DAILY,//���췵���������۰�
		WBOPT_GET_STATUSES_HOT_COMMENTS_WEEKLY,//���ܷ����������۰�
		WBOPT_POST_STATUSES_REPOST,//ת��һ��΢����Ϣ
		WBOPT_POST_STATUSES_DESTROY,//ɾ��΢��������Ϣ
		WBOPT_POST_STATUSES_UPDATE,//����һ��΢����Ϣ
		WBOPT_POST_STATUSES_UPLOAD_URL_TEXT,//����һ��΢����ͬʱָ���ϴ���ͼƬ��ͼƬurl
		WBOPT_POST_STATUSES_UPLOAD,//����һ��΢�����ϴ�ͼƬ������һ��΢����Ϣ

		WBOPT_GET_COMMENTS_SHOW,//��ȡĳ��΢���������б�
		WBOPT_GET_COMMENTS_BYME,//�ҷ����������б�
		WBOPT_GET_COMMENTS_TOME,//���յ��������б�
		WBOPT_GET_COMMENTS_TIMELINE,//��ȡ��ǰ�û����ͼ��յ��������б�
		WBOPT_GET_COMMENTS_MENTIONS,//@���ҵ�����
		WBOPT_GET_COMMENTS_SHOWBATCH,//@������ȡ��������

		WBOPT_POST_COMMENTS_CREATE,//����һ��΢��
		WBOPT_POST_COMMENTS_DESTROY,//ɾ��һ������
		WBOPT_POST_COMMENTS_DESTROY_BATCH ,//����ɾ������
		WBOPT_POST_COMMENTS_REPLY,//�ظ�һ������

		WBOPT_GET_DIRECTMESSAGES,//��ȡ��ǰ�û�����˽���б�
		WBOPT_GET_DIRECTMESSAGES_SENT,//��ȡ��ǰ�û����͵�����˽���б�
		WBOPT_GET_DIRECTMESSAGES_USER_LIST,//��ȡ˽�������û��б�
		WBOPT_GET_DIRECTMESSAGES_CONVERSATION,//��ȡ��ָ���û�������˽���б�
		WBOPT_GET_DIRECTMESSAGES_SHOW_BATCH,//������ȡ˽������
		WBOPT_GET_DIRECTMESSAGES_IS_CAPABLE,//�ж��Ƿ���Ը��Է���˽��
		WBOPT_POST_DIRECTMESSAGES_NEW,//����һ��˽��
		WBOPT_POST_DIRECTMESSAGES_DESTORY,//ɾ��һ��˽��
		WBOPT_POST_DIRECTMESSAGES_DESTORY_BATCH,//����ɾ��˽��

		WBOPT_GET_USERS_SHOW,//��ȡ�û�����
		WBOPT_GET_USERS_DOMAIN_SHOW,//ͨ������������ȡ�û���Ϣ
		WBOPT_GET_USERS_SHOW_BATCH,//������ȡ�û���Ϣ

		WBOPT_GET_ACCOUNT_PROFILE_BASIC, //��ȡ�û�������Ϣ
		WBOPT_GET_ACCOUNT_PROFILE_EDUCATION, //��ȡ������Ϣ
		WBOPT_GET_ACCOUNT_PROFILE_EDUCATION_BATCH, //������ȡ������Ϣ
		WBOPT_GET_ACCOUNT_PROFILE_CAREER, //��ȡְҵ��Ϣ
		WBOPT_GET_ACCOUNT_PROFILE_CAREER_BATCH, //������ȡְҵ��Ϣ
		WBOPT_GET_ACCOUNT_GET_PRIVACY, //��ȡ��˽������Ϣ
		WBOPT_GET_ACCOUNT_PROFILE_SCHOOL_LIST, //��ȡ����ѧУ�б�
		WBOPT_GET_ACCOUNT_RATE_LIMIT_STATUS, //��ȡ��ǰ�û�API����Ƶ������
		WBOPT_GET_ACCOUNT_GET_UID, //OAuth��Ȩ֮���ȡ�û�UID�������൱�ھɰ�ӿڵ�account/verify_credentials��
		WBOPT_POST_ACCOUNT_PROFILE_BASIC_UPDATE, // �����û�������Ϣ
		WBOPT_POST_ACCOUNT_PROFILE_EDU_UPDATE, // �����û�������Ϣ
		WBOPT_POST_ACCOUNT_PROFILE_EDU_DESTROY, // ɾ���û�������Ϣ
		WBOPT_POST_ACCOUNT_PROFILE_CAR_UPDATE, // �����û�ְҵ��Ϣ
		WBOPT_POST_ACCOUNT_PROFILE_CAR_DESTROY, // ɾ���û�ְҵ��Ϣ
		WBOPT_POST_ACCOUNT_AVATAR_UPLOAD, // �ϴ�ͷ��
		WBOPT_POST_ACCOUNT_UPDATE_PRIVACY, // ������˽����

		WBOPT_GET_FRIENDSHIPS_FRIENDS,//��ȡ�û��Ĺ�ע�б�
		WBOPT_GET_FRIENDSHIPS_IN_COMMON,//��ȡ��ͬ��ע���б�ӿ�
		WBOPT_GET_FRIENDSHIPS_BILATERAL,//��ȡ˫���ע�б�
		WBOPT_GET_FRIENDSHIPS_BILATERAL_IDS,//��ȡ˫���עID�б�
		WBOPT_GET_FRIENDSHIPS_FRIENDS_IDS,//��ȡ�û���ע����uid�б�
		WBOPT_GET_FRIENDSHIPS_FRIENDS_REMARK_BATCH,//������ȡ��ע
		WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS,//��ȡ�û���˿�б�ÿ����˿������һ��΢��
		WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_IDS,//��ȡ�û���˿����uid�б�
		WBOPT_GET_FRIENDSHIPS_FRIENDS_FOLLOWERS_ACTIVE,//��ȡ�û����ʷ�˿�б��ϵ��
		WBOPT_GET_FRIENDSHIPS_CHAIN_FOLLOWERS,//��ȡ�ҵĹ�ע���й�ע��ָ���û��ķ���
		WBOPT_GET_FRIENDSHIPS_SHOW,//��ȡ�����û���ϵ����ϸ���
		WBOPT_POST_FRIENDSHIPS_CREATE,//��עĳ�û�
		WBOPT_POST_FRIENDSHIPS_CREATE_BATCH,//������ע�û�
		WBOPT_POST_FRIENDSHIPS_DESTROY,//ȡ����עĳ�û�	
		WBOPT_POST_FRIENDSHIPS_FOLLOWERS_DESTORY,//�Ƴ���˿
		WBOPT_POST_FRIENDSHIPS_REMARK_UPDATE,//���¹�ע�˱�ע

		WBOPT_GET_FAVORITES,//��ȡ��ǰ��¼�û����ղ��б�
		WBOPT_GET_FAVORITES_SHOW,//��ȡ�����ղ���Ϣ
		WBOPT_GET_FAVORITES_BY_TAGS,//��ȡ��ǰ�û�ĳ����ǩ�µ��ղ��б�
		WBOPT_GET_FAVORITES_TAGS,//��ǰ��¼�û����ղر�ǩ�б�
		WBOPT_POST_FAVORITES_CREATE,//����ղ�
		WBOPT_POST_FAVORITES_DESTROY,//ɾ���ղ�
		WBOPT_POST_FAVORITES_DESTROY_BATCH,//����ɾ���ղ�
		WBOPT_POST_FAVORITES_TAGS_UPDATE,//�����ղر�ǩ
		WBOPT_POST_FAVORITES_TAGS_UPDATE_BATCH,//���µ�ǰ�û������ղ��µ�ָ����ǩ
		WBOPT_POST_FAVORITES_TAGS_DESTROY_BATCH,//ɾ����ǰ�û������ղ��µ�ָ����ǩ

		WBOPT_GET_TRENDS,//��ȡĳ�˻���
		WBOPT_GET_TRENDS_STATUSES,//��ȡĳһ�����µ�΢��
		WBOPT_GET_TRENDS_HOURLY,//�������һСʱ�ڵ����Ż���
		WBOPT_GET_TRENDS_DAILY,//�������һ���ڵ����Ż���
		WBOPT_GET_TRENDS_WEEKLY,//�������һ���ڵ����Ż���
		WBOPT_POST_TRENDS_FOLLOW,//��עĳ����
		WBOPT_POST_TRENDS_DESTROY,//ȡ����ע��ĳһ������

		WBOPT_GET_TAGS,//����ָ���û��ı�ǩ�б�
		WBOPT_GET_TAGS_TAGS_BATCH,//������ȡ�û���ǩ
		WBOPT_GET_TAGS_SUGGESTIONS,//����ϵͳ�Ƽ��ı�ǩ�б�
		WBOPT_POST_TAGS_CREATE,//����û���ǩ
		WBOPT_POST_TAGS_DESTROY,//ɾ���û���ǩ
		WBOPT_POST_TAGS_DESTROY_BATCH,//����ɾ���û���ǩ

		WBOPT_GET_SEARCH_SUGGESTIONS_USERS,//���û���������
		WBOPT_GET_SEARCH_SUGGESTIONS_STATUSES,//��΢����������
		WBOPT_GET_SEARCH_SUGGESTIONS_SCHOOLS,//��ѧУ��������
		WBOPT_GET_SEARCH_SUGGESTIONS_COMPANIES, //�ѹ�˾��������
		WBOPT_GET_SEARCH_SUGGESTIONS_APPS,//��Ӧ����������
		WBOPT_GET_SEARCH_SUGGESTIONS_AT_USERS, //@��������
		WBOPT_GET_SEARCH_SUGGESTIONS_INTEGRATE,  //�ۺ���������
		WBOPT_GET_SEARCH_STATUSES,//΢������ 
		WBOPT_GET_SEARCH_GEO_STATUSES, //����ָ����Χ�ڵ�΢��
		WBOPT_GET_SEARCH_USERS,//�����û�

		WBOPT_GET_SUGGESTIONS_FAVORITES_HOT,//�����ղ�
		WBOPT_GET_SUGGESTIONS_USERS_HOT,//��ȡϵͳ�Ƽ��û�
		WBOPT_GET_SUGGESTIONS_USERS_MAY_INTERESTED,//��ȡ�û����ܸ���Ȥ����
		WBOPT_POST_SUGGESTIONS_USERS_NOT_INTERESTED,//������Ȥ����
		WBOPT_GET_SUGGESTIONS_USERS_BY_STATUS,//����΢�������Ƽ��û�

		WBOPT_GET_SHORT_URL_SHORTEN, //��һ������������ת���ɶ�����
		WBOPT_GET_SHORT_URL_EXPAND, //��һ�����������ӻ�ԭ��ԭʼ�ĳ�����
		WBOPT_GET_SHORT_URL_SHARE_COUNTS, //ȡ��һ����������΢���ϵ�΢��������������ԭ����ת����΢����
		WBOPT_GET_SHORT_URL_SHARE_STATUSES, //ȡ�ð���ָ�����������ӵ�����΢������
		WBOPT_GET_SHORT_URL_COMMENT_COUNTS, //ȡ��һ����������΢���ϵ�΢��������
		WBOPT_GET_SHORT_URL_COMMENT_COMMENTS, //ȡ�ð���ָ�����������ӵ�����΢����������
		WBOPT_GET_SHORT_URL_INFO,

		WBOPT_GET_REMIND_UNREAD_COUNT,//��ȡĳ���û��ĸ�����Ϣδ����
		WBOPT_POST_STATUSES_RESET_COUNT,//������Ϣδ����

		// Groups
		WBOPT_GET_GROUPS_JOINED,
		WBOPT_GET_GROUPS_SHOW_BATCH,
		WBOPT_GET_GROUPS_GET_ANNOUNCEMENT,
		WBOPT_GET_GROUPS_ADMIN,
		WBOPT_GET_GROUPS_USERS,
		WBOPT_GET_GROUPS_SUGGESTION_MAY_INTERESTED,
		WBOPT_GET_GROUPS_CHAT_BLOCK,
		WBOPT_GET_GROUPS_CHAT_UNBLOCK,
		WBOPT_GET_GROUPS_CHAT_IS_BLOCKED,
		WBOPT_GET_GROUP_USERS_JOINED_STATUSES,

		//Image
		WEOPT_GET_IMPAGE_FROM_URL,

		WBOPT_END,
	};

	class WEIBO_SDK_API IWeiboMethod
	{
	public:
		virtual eWeiboResultCode oauth2(const char* userName, const char* password, UserTaskInfo* pTask) = 0;
		virtual eWeiboResultCode oauth2Code(const char* userName, const char* password, UserTaskInfo* pTask) = 0;
		virtual eWeiboResultCode endSession() = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ΢����ȡ
		virtual eWeiboResultCode getStatusesPublicTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesFriendTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesHomeTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesUserTimeline(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesTimelineBatch(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesRepostTimeline(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesRepostByMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesMentions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesShow(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesShowBatch(const char* inputIDs, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesQueryMID(const char *weiboId, const int type, const int is_batch = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesQueryID(const char *mId, const int type, const int is_batch = 0, const int inbox = 0, const int isBase62 = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesRepostDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesRepostWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesHotCommmentsDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getStatusesHotCommmentsWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// ΢��д��
		virtual eWeiboResultCode postStatusesRepost(const char *weiboId, const char *statusText, const int isComment, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postStatusesDestroy(const char *weiboId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postStatusesUpdate(const char* statusText, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postStatusesUploadUrlText(const char* statusText, const char *picInfo, bool isPicUrl, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postStatusesUpload(const char* statusText, const char *filePath, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���۶�ȡ
		virtual eWeiboResultCode getCommentsShow(const char *weiboId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getCommentsByMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getCommentsToMe(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getCommentsTimeline(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getCommentsMentions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// ����д��
		virtual eWeiboResultCode getCommentsShowBatch(const char* commentIds, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postCommentsCreate(const char* id, const char* comment, const int commentOri,VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postCommentsDestroy(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postCommentsDestroyBatch(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postCommentsReply(const char* commentId, const char* comment, const char* weiboId
			, const int withoutMention, const int commentOri, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ˽�Ŷ�ȡ
		virtual eWeiboResultCode getDirectMessages(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getDirectMessagesSent(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getDirectMessagesUserList(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getDirectMessagesCoversation(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getDirectMessagesShowBatch(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getDirectMessagesIsCapable(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// ˽��д��
		virtual eWeiboResultCode postDirectMessagesNew(const char* text, const ID& uid, const char* fields = NULL,
			const char* weiboId = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postDirectMessagesDestory(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postDirectMessagesDestoryBatch(const char* ids, const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �û���ȡ
		virtual eWeiboResultCode getUsersShow(ID& usrId, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getUsersDomainShow(const char* domain = NULL, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getUsersShowBatch(ID& usrId, const char* extend = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ��ע��ȡ
		virtual eWeiboResultCode getFriendshipsFriends(ID& usrId, const int order/*= 0*/, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsInCommon(const char* id, const char* suid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsBilateral(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsBilateralIDs(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsFriendIDs(ID& usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsFriendRemarkBatch(const char* uids, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;

		// ��˿��ȡ
		virtual eWeiboResultCode getFriendshipsFriendsFollowers(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsFriendsFollowersIDs(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getFriendshipsFriendsFollowersActive(ID &usrIDs, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;

		// ��ϵ����ȡ
		virtual eWeiboResultCode getFriendshipsFriendsChainFollowers(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;

		// ��ϵ״̬
		virtual eWeiboResultCode getFriendshipShow(ID& sourceId, ID& targetId, UserTaskInfo* pTask = NULL) = 0 ;

		// ��ϵд��
		virtual eWeiboResultCode postFriendshipsCreate(ID &usrId, const int skipCheck, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postFriendshipsCreateBatch(const char* uids, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postFriendshipsDestroy(ID &usrId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postFriendshipsFollowersDestroy(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postFriendshipsRemarkUpdate(const char* uid, const char* remark, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0 ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �ʺŶ�ȡ
		virtual eWeiboResultCode getAccountProfileBasic(const char *uid, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountProfileEducation(const char* uid, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountProfileEducationBatch(const char* uids, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountProfileCareer(const char* uid, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountProfileCareerBatch(const char* uids, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountGetPrivacy(UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountProfileSchoolList(const int province = 0, const int city = 0, const int area = 0, const int type = 0, 
			const char* capital = 0, const char* keyword = 0, const int counts = 0, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountRateLimitStatus(UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode getAccountGetUID(UserTaskInfo* pTask = NULL) = 0 ;

		// �ʺ�д��
		virtual eWeiboResultCode postAccountProfileBasicUpdate(const BasicInfo& basic, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountProfileEduUpdate(const EducationInfo& edu, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountProfileEduDestroy(const char* id, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountProfileCarUpdate(const CareerInfo& career, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountProfileCarDestroy(const char* id, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountAvatarUpload(const char* filePath, UserTaskInfo* pTask = NULL) = 0 ;
		virtual eWeiboResultCode postAccountUpdatePrivacy(const int comment = 0, const int geo = 0, const int message = 0,
			const int realname = 0, const int badge = 0, const int mobile = 0, UserTaskInfo* pTask = NULL) = 0 ;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �ղض�ȡ
		virtual eWeiboResultCode getFavorites(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getFavoritesShow(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getFavoritesByTags(const char* tid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getFavoritesTags(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// �ղ�д��
		virtual eWeiboResultCode postFavoritesCreate(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postFavoritesDestroy(const char* id, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postFavoritesDestroyBatch(const char* ids, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postFavoritesTagUpdate(const char* tagId, const char* tagName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postFavoritesTagsUpdateBatch(const char* tagId, const char* tagName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postFavoritesTagsDestroyBatch(const char* tagId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �����ȡ
		virtual eWeiboResultCode getTrends(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTrendsStatuses(const char* trendWords, const char* provinceId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTrendsHourly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTrendsDaily(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTrendsWeekly(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// ����д��
		virtual eWeiboResultCode postTrendsFollow(const char* trendName, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postTrendsDestroy(const char* trendId, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ��ǩ��ȡ
		virtual eWeiboResultCode getTags(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTagsTagsBatch(const char* uids, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getTagsSuggestions(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		// ��ǩд��
		virtual eWeiboResultCode postTagsCreate(const char* tags, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postTagsDestroy(const char* tagId, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postTagsDestroyBatch(const char* tagIds, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ����
		virtual eWeiboResultCode getSearchSuggestionsUsers(const char* q, const int count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsStatues(const char* q, const int count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsSchool(const char* q, const int count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsCompanies(const char* q, const int count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsApps(const char* q, const int count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsAtUsers(const char* q, const int type, const int count = 0, const int range = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchSuggestionsIntegrate(const char* query, const int sort_user = 0, const int sort_app = 0,
			const int sort_grp = 0, const int user_count = 0, const int app_count = 0, const int grp_count = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchStatuses(const char* q, const int filter_ori = 0, const int filter_pic = 0, const char* fuid = 0, 
			const int province = 0, const int city = 0, const char* starttime = NULL, const char* endtime = NULL, const int count = 0, 
			const int page = 0, const bool needcount = 0, const int base_app = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchGeoStatuses(const float longitude, const float latitudeconst, const int range = 0, const int time = 0,
			const int sort_type = 0, const int page = 0, const int count = 0, const int base_app = 0, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSearchUsers(const char* q, const int snick = 0, const int sdomain = 0, const int sintro = 0, const int stag = 0, 
			const int province = 0, const int city = 0, const char* gender = 0, const char* comorsch = 0, const int sort = 0,
			const int count = 0, const int page = 0, const int base_app = 0, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �Ƽ���ȡ
		virtual eWeiboResultCode getSuggestionsFavoritesHot(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSuggestionsUsersHot(const char* category, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSuggestionsUsersMayInterested(VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getSuggestionsUsersByStatus(const char* content, const int num = 0, const char* url = NULL, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �Ƽ�д��
		virtual eWeiboResultCode postSuggestionsUsersNotInterested(const char* uid, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �����ӿ�
		virtual eWeiboResultCode getShortURLShorten(const char* url_long, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortURLExpand(const char* url_short, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortURLShareCounts(const char* url_short, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortURLShareStatuses(const char* url_short, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortURLCommentCounts(const char* url_short, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortURLCommentComments(const char* url_short, VariableParams* var = NULL, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getShortUrlInfo(const char* shortUrlIDs, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Unread
		virtual eWeiboResultCode getRemindUnreadCount(const char* uid, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postStatusesResetCount(const int type, UserTaskInfo* pTask = NULL) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Groups
		virtual eWeiboResultCode getGroupsJoined(const char* uid, const int page, const int count, 
			const int type, const int filter, const int sort, const int member_limit, const int simplify, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsShowBatch(const char* gids, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsGetAnnouncement(const char* gid, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsAdmin(const char* gid, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsUsers(const char* gid, VariableParams* var, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsSuggestionMayInterested(const int count, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsChatIsBlocked(const char* gids, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postGroupsChatBlock(const char* gid, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode postGroupsChatUnblock(const char* gid, UserTaskInfo* pTask = NULL) = 0;
		virtual eWeiboResultCode getGroupsUsersJoinedStatuses(const char* uid,int simplify,VariableParams* var = NULL,UserTaskInfo* pTask = NULL)=0;

		//////////////////////////////////////////////////////////////////////////
		// Image
		virtual eWeiboResultCode getWeiboImage(const char *img_url,VariableParams *var=NULL,UserTaskInfo *pTask=NULL)=0;
	};

}

#endif //WEIBOSDK_IWEIBOMETHOD_HXX