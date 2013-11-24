#ifndef WEIBOSDK_COMPAT_HXX
#define WEIBOSDK_COMPAT_HXX

#if defined(WIN32) || defined(_WIN32) 

#   if defined(_MSC_VER)
#      pragma warning(disable: 4251)  // warning C4251:  class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 
#   endif // #if defined(_MSC_VER)

#   ifdef WEIBO_SDK_EXPORTS
#      define WEIBO_SDK_API __declspec(dllexport)
#   elif defined(USE_WEIBO_DLL)
#      define WEIBO_SDK_API __declspec(dllimport)
#   else
#      define WEIBO_SDK_API 
#   endif
#else
#   define WEIBO_SDK_API 
#endif // #if defined(WIN32) || defined(_WIN32) 

#endif //WEIBOSDK_COMPAT_HXX