#ifndef WEIBOSDK_PARSINGOBJECT_HXX
#define WEIBOSDK_PARSINGOBJECT_HXX

#include "compat.hxx"
#include <boost/shared_ptr.hpp>

namespace weibo
{
	class ParsingHandle;

	/** pasing object, wrapped how to parsing.
	*
	* @author welbon
	* 
	* @date 2011-10-13
	*/
	class WEIBO_SDK_API ParsingObject
	{
	public:
		ParsingObject(const char* source);
		ParsingObject(boost::shared_ptr<ParsingHandle> actHandlPtr);
		ParsingObject(ParsingObject& object);

		virtual ~ParsingObject();

		bool isUseable();
		const char* getErrorMessage();
		const char* getOriginString();

		std::string getKeyName();
		std::string asAString();
		long long asANumberic();

		unsigned int getSubCounts();

		long long getSubNumbericByKey(const char* key);
		std::string getSubStringByKey(const char* key);
		boost::shared_ptr<ParsingObject> getSubObjectByKey(const char* key);

		long long getSubNumbericByIndex(const int index);
		std::string getSubStringByIndex(const int index);
		boost::shared_ptr<ParsingObject> getSubObjectByIndex(const int index);

		typedef void (*EnumAllSubCall)(const boost::shared_ptr<ParsingObject> object, void* usrData);
		void enumAllSub(EnumAllSubCall callback, void* usrData);

	private:
		boost::shared_ptr<ParsingHandle> mParsingHandle;
	};
}

#endif //PARSING_PARSINGOBJECT_HXX