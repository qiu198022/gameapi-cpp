#ifndef __EXCEPTION_HANDLER_H__
#define __EXCEPTION_HANDLER_H__

#include "PlaytomicDefines.h"

namespace Playtomic
{

    typedef void (*signalCallback)(int, std::string& dest);
class DllExport CExceptionHandler
{
public:
	CExceptionHandler(void);
	~CExceptionHandler(void);

	static void SetHandlers();
	static void UnsetHandlers();

	static void SendStackTrace(const char* stacktrace);

	static void GetStackTrace(std::string& dest);
    
    static void SetSignalCallbackk(signalCallback callback );

    static signalCallback mCallback;
};

}//namespace

#endif