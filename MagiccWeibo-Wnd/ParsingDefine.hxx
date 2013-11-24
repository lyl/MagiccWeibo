#ifndef WEIBOSDK_PARSING_PARSINGDEFINE_HXX
#define WEIBOSDK_PARSING_PARSINGDEFINE_HXX

namespace weibo
{
	// Sub type for Parsing list.
	template<typename T>
	class ParsingList;

	class ParsingObject;
	typedef boost::shared_ptr<ParsingObject> ParsingObjectPtr;

	class ParsingBase;
	typedef boost::shared_ptr<ParsingBase> ParsingBasePtr;

	class ParsingUser;
	typedef boost::shared_ptr<ParsingUser> ParsingUserPtr;
	typedef ParsingList<ParsingUser> ParsingUsersList;
	typedef boost::shared_ptr<ParsingUsersList> ParsingUsersListPtr;

	class ParsingStatus;
	typedef boost::shared_ptr<ParsingStatus> ParsingStatusPtr;
	typedef ParsingList<ParsingStatus> ParsingStatusesList;
	typedef boost::shared_ptr<ParsingStatusesList> ParsingStatusesListPtr;

	class ParsingComment;
	typedef boost::shared_ptr<ParsingComment> ParsingCommentPtr;
	typedef ParsingList<ParsingComment> ParsingCommentsList;
	typedef boost::shared_ptr<ParsingCommentsList> ParsingCommentsListPtr;

	class ParsingDirectMessage;
	typedef boost::shared_ptr<ParsingDirectMessage> ParsingDirectMessagePtr;
	typedef ParsingList<ParsingDirectMessage> ParsingDirectMessagesList;
	typedef boost::shared_ptr<ParsingDirectMessagesList> ParsingDirectMessagesListPtr;

	class ParsingFavorite;
	typedef boost::shared_ptr<ParsingFavorite> ParsingFavoritePtr;
	typedef ParsingList<ParsingFavorite> ParsingFavoritesList;
	typedef boost::shared_ptr<ParsingFavoritesList> ParsingFavoritesListPtr;

	class ParsingFavoriteTag;
	typedef boost::shared_ptr<ParsingFavoriteTag> ParsingFavoriteTagPtr;
	typedef ParsingList<ParsingFavoriteTag> ParsingFavoriteTagsList;
	typedef boost::shared_ptr<ParsingFavoriteTagsList> ParsingFavoriteTagsListPtr;

	class ParsingGeo;
	typedef boost::shared_ptr<ParsingGeo> ParsingGeoPtr;

	class ParsingOauthRet;
	typedef boost::shared_ptr<ParsingOauthRet> ParsingOauthRetPtr;

	class ParsingResult;
	typedef boost::shared_ptr<ParsingResult> ParsingResultPtr;
	typedef ParsingList<ParsingResult> ParsingResultList;
	typedef boost::shared_ptr<ParsingResultList> ParsingResultListPtr;

	class ParsingApiError;
	typedef boost::shared_ptr<ParsingApiError> ParsingApiErrorPtr;

	class ParsingAccount;
	typedef boost::shared_ptr<ParsingAccount> ParsingAccountPtr;

	class ParsingEducation;
	typedef boost::shared_ptr<ParsingEducation> ParsingEducationPtr;
	typedef ParsingList<ParsingEducation> ParsingEducationsList;
	typedef boost::shared_ptr<ParsingEducationsList> ParsingEducationsListPtr;

	class ParsingCareer;
	typedef boost::shared_ptr<ParsingCareer> ParsingCareerPtr;
	typedef ParsingList<ParsingCareer> ParsingCareersList;
	typedef boost::shared_ptr<ParsingCareersList> ParsingCareersListPtr;

	class ParsingTag;
	typedef boost::shared_ptr<ParsingTag> ParsingTagPtr;
	typedef ParsingList<ParsingTag> ParsingTagsList;
	typedef boost::shared_ptr<ParsingTagsList> ParsingTagsListPtr;

	class ParsingTrend;
	typedef boost::shared_ptr<ParsingTrend> ParsingTrendPtr;
	typedef ParsingList<ParsingTrend> ParsingTrendsList;
	typedef boost::shared_ptr<ParsingTrendsList> ParsingTrendsListPtr;
}

#endif //WEIBOSDK_PARSING_PARSINGDEFINE_HXX