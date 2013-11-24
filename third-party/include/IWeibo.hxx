#ifndef WEIBOSDK_IWEIBOSDK_HXX
#define WEIBOSDK_IWEIBOSDK_HXX

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <util/delegate/delegate.hxx>

#include "compat.hxx"
#include "IWeiboDef.hxx"

namespace weibo
{
	class ParsingObject;
	class IWeiboMethod;

	/** weibo sdk interface
	* 
	* @author welbon
	*
	* @date 2011-08-20
	*/
	class WEIBO_SDK_API IWeibo
	{
	public:
		virtual ~IWeibo(){}

		virtual int startup() = 0;
		virtual int shutdown() = 0;
		virtual void stopAll() = 0;

		virtual void getOption(const eWeiboOption option, ...) = 0;
		virtual void setOption(const eWeiboOption option, ...) = 0;

		virtual IWeiboMethod *getMethod() = 0;

		// Delegate option
		Util::Delegate<void (unsigned int methodOption, const char* httpHeader, 
			ParsingObject* result, const UserTaskInfo* pTask)> OnDelegateComplated;

		Util::Delegate<void (unsigned int methodOption, const int errCode, const int subErrCode, 
			ParsingObject* result, const UserTaskInfo* pTask)> OnDelegateErrored;

		Util::Delegate<void (unsigned int methodOption, const UserTaskInfo* pTask)> OnDelegateWillRelease;
	};

	// Get singleton weibo object.
	class WEIBO_SDK_API WeiboFactory
	{
	public:
		static boost::shared_ptr<IWeibo> getWeibo();

	private:
		static boost::weak_ptr<IWeibo> mWeiboPtr;
	};
}


#endif //WEIBOSDK_IWEIBOSDK_H