#include "CConnectionInterface.h"
#include "CPlaytomicResponse.h"
#include "CRequest.h"
#include "../json/include/json.h"
#ifdef __ANDROID__
#include "boostFix.h"
#endif
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"

struct SThreadedRequest
{
	std::string		sUrl;
	CPostPtr		sPost;
	RequestDelegate sTargetDelegate;
	void operator()();
};

void SThreadedRequest::operator()()
{
	CRequest request;
	SRequestResult data;

	request.CreateQuery(sUrl.c_str());

	if(sPost.get() != NULL)
	{

		request.SetPostData(sPost.get());
	}
	ERequestResult res = request.Perform(&data);

	if(res != e_Ok)
	{
		//send error message
		//return ( CPlaytomicResponsePtr(new CPlaytomicResponse(1)));
		CPlaytomicResponsePtr rtn(new CPlaytomicResponse(1));
		sTargetDelegate(rtn);
		return;
	}

	if(data.data == NULL)
	{
		//send error message
		CPlaytomicResponsePtr rtn(new CPlaytomicResponse(true, 0));
		sTargetDelegate(rtn);
		return;
	}

	Json::Reader parser;
	FData root;
	bool parserResult = parser.parse(data.data,root,false);

	Json::Value status;
	status = root.get("Status", status);

	FData errorCode;
	errorCode = root.get("ErrorCode",errorCode);
	if ( status.asInt() == 1)
	{		
		FData returnData;
		returnData = root.get("Data",returnData);
		//send message
		CPlaytomicResponsePtr rtn(CPlaytomicResponsePtr( new CPlaytomicResponse(true,errorCode.asInt(),returnData, returnData.size())));
		sTargetDelegate(rtn);
		return;
	}
	else
	{
		if(errorCode.asInt() == 0)
		{
			
			//send Message
			CPlaytomicResponsePtr rtn( CPlaytomicResponsePtr(new CPlaytomicResponse(1)));
			sTargetDelegate(rtn);
			return;
		}
		//return;
		//send message
		CPlaytomicResponsePtr rtn(CPlaytomicResponsePtr(new CPlaytomicResponse(false, errorCode.asInt())));
		sTargetDelegate(rtn);
	}
}

CConnectionInterface* CConnectionInterface::sHandle = NULL;

//static members
//==============================================================================
//==============================================================================
CConnectionInterface* CConnectionInterface::Get()
{
	if(sHandle == NULL)
	{
		sHandle = new CConnectionInterface();
	}
	return sHandle;
}

void CConnectionInterface::Destroy()
{
	if (sHandle)
	{
		delete sHandle;
		sHandle = NULL;
	}
}


//instance members
//==============================================================================
//==============================================================================
CConnectionInterface::CConnectionInterface()
{

}

CConnectionInterface::~CConnectionInterface()
{

}

void CConnectionInterface::Init()
{
	curl_global_init(CURL_GLOBAL_ALL);
}

CPlaytomicResponsePtr CConnectionInterface::PerformSyncRequest(const char* url, CPost* postData)
{
	CRequest request;
	SRequestResult data;
	request.CreateQuery(url);
	if(postData)
	{
		request.SetPostData(postData);
	}
	ERequestResult res = request.Perform(&data);
	if(res != e_Ok)
	{
		return ( CPlaytomicResponsePtr(new CPlaytomicResponse(1)));
	}

	if(data.data == NULL)
	{
		return CPlaytomicResponsePtr(new CPlaytomicResponse(true, 0));
	}

	Json::Reader parser;
	FData root;
	bool parserResult = parser.parse(data.data,root,false);

	Json::Value status;
	status = root.get("Status", status);
	
	FData errorCode;
	errorCode = root.get("ErrorCode",errorCode);
	if ( status.asInt() == 1)
	{		
		FData returnData;
		returnData = root.get("Data",returnData);
		return (CPlaytomicResponsePtr( new CPlaytomicResponse(true,errorCode.asInt(),returnData, returnData.size())));
	}
	else
	{
		if(errorCode.asInt() == 0)
		{
			return ( CPlaytomicResponsePtr(new CPlaytomicResponse(1)));
		}
		return (CPlaytomicResponsePtr(new CPlaytomicResponse(false, errorCode.asInt())));
	}

	
}

void CConnectionInterface::PerformAsyncRequest(const char* url, RequestDelegate targetDelegate)
{
	PerformAsyncRequest(url, targetDelegate, CPostPtr());
}

void CConnectionInterface::PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, CPostPtr postData )
{
	SThreadedRequest x;
	x.sPost = postData;
	x.sUrl = url;
	x.sTargetDelegate = targetDelegate;
	boost::thread thread(x);
}

