#include "CExceptionHandler.h"
#include <signal.h>
#include "CConnectionInterface.h"
#include "CPlaytomic.h"

#define _CRT_DEBUGGER_IGNORE 1
namespace Playtomic
{

signalCallback CExceptionHandler::mCallback = NULL;
    
void HandleSignal(int signal)
{

    const char* sigtype[NSIG];
    sigtype[SIGABRT] = "SIGABRT";   
    sigtype[SIGFPE] = "SIGFPE";
    sigtype[SIGILL] = "SIGILL";
    sigtype[SIGSEGV] = "SIGSEGV";
    
	std::string stackTrace;
    stackTrace += "signal = ";
    stackTrace += sigtype[signal];
    stackTrace += "\n";

    if(CExceptionHandler::mCallback)
    {
        CExceptionHandler::mCallback(signal);
    }
	CExceptionHandler::GetStackTrace(stackTrace);
	CExceptionHandler::SendStackTrace(stackTrace.c_str());
    CExceptionHandler::UnsetHandlers();
}

CExceptionHandler::CExceptionHandler(void)
{
	
}


CExceptionHandler::~CExceptionHandler(void)
{
}

void CExceptionHandler::SetHandlers()
{
	signal(SIGILL, &HandleSignal);
	signal(SIGINT, &HandleSignal);
	signal(SIGFPE, &HandleSignal);
	signal(SIGSEGV , &HandleSignal);
	signal(SIGABRT, &HandleSignal);
    
    signal(SIGABRT, &HandleSignal);

    signal(SIGFPE, &HandleSignal);
    signal(SIGILL, &HandleSignal);
    
    signal(SIGSEGV, &HandleSignal);
 //   signal(SIGHUP, HandleSignal);
//    signal(SIGBUS, &HandleSignal);
//    signal(SIGPIPE, HandleSignal);
}

void CExceptionHandler::UnsetHandlers()
{
	signal(SIGILL, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGSEGV , SIG_DFL);
	signal(SIGABRT, SIG_DFL);
}

void CExceptionHandler::SendStackTrace(const char* stacktrace)
{
	CPost post;

	std::string sourceUrl = CPlaytomic::Get()->GetSourceUrl();
	std::string baseUrl   = gPlaytomic->GetBaseUrl();

	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string trackUrl = kBasetrackUrlPart1;
	trackUrl += gPlaytomic->GetGameGuid() + ".api.playtomic.com/tracker/e.aspx?swfid=";
	trackUrl += IdString;
	trackUrl += kBaseTrackUrlPart3;
	trackUrl += sourceUrl;
	trackUrl += "&debug=y";

	post.AddText("stacktrace", stacktrace);

	gConnectionInterface->PerformSyncRequest(trackUrl.c_str(), &post);
}

    
void CExceptionHandler::SetSignalCallbackk(signalCallback callback  )
{
    CExceptionHandler::mCallback = callback;
}
    
}//namespace
