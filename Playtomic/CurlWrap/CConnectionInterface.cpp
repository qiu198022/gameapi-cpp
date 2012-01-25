//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 10/20/11.
//  Copyright 2011 Playtomic LLC. All rights reserved.
//
//  Documentation is available at:
//  http://playtomic.com/api/cpp
//
// PLEASE NOTE:
// You may modify this SDK if you wish but be kind to our servers.  Be
// careful about modifying the analytics stuff as it may give you
// borked reports.
//
// If you make any awesome improvements feel free to let us know!
//
// -------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY PLAYTOMIC, LLC "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "CConnectionInterface.h"
#include "CPlaytomicResponse.h"
#include "CRequest.h"
#include "../json/include/json.h"
#ifdef __ANDROID__
#include "boostFix.h"
#endif
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"

#ifdef __ANDROID__
#include <android/log.h>
#define  LOG_TAG    "CLOGConnectionInterface"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

static boost::mutex mThreadListMutex;
static boost::mutex mRequestQeueMutex;

struct SThreadedRequest
{
	std::string		sUrl;
	CPostPtr		sPost;
	RequestDelegate sTargetDelegate;
	void operator()();
    void RequestFinish(CPlaytomicResponsePtr& response);
};  

void SThreadedRequest::RequestFinish(CPlaytomicResponsePtr &response)
{
    boost::this_thread::interruption_point();
    sTargetDelegate(response);
#ifdef __ANDROID__
	LOGI("Request Finished");
#endif
}

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
		RequestFinish(rtn);
		return;
	}
    
	if(data.data == NULL)
	{
		//send error message
		CPlaytomicResponsePtr rtn(new CPlaytomicResponse(true, 0));
		RequestFinish(rtn);
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
		RequestFinish(rtn);
		return;
	}
	else
	{
		if(errorCode.asInt() == 0)
		{
			
			//send Message
			CPlaytomicResponsePtr rtn( CPlaytomicResponsePtr(new CPlaytomicResponse(1)));
			RequestFinish(rtn);
			return;
		}
		//return;
		//send message
		CPlaytomicResponsePtr rtn(CPlaytomicResponsePtr(new CPlaytomicResponse(false, errorCode.asInt())));
		RequestFinish(rtn);
	}
}

class CAsyncRequest
{
public:
    CAsyncRequest( CConnectionInterface* owner) { mOwner = owner;}
    
    void Set(const std::string url, CPostPtr post, RequestDelegate targetDelegate);
    void Start(const std::string url, CPostPtr post, RequestDelegate targetDelegate);
    void Start();
    void Stop();

private:
    void ProcessRequest(const std::string url, CPostPtr post, RequestDelegate targetDelegate);
	void ProcessRequest();
    ThreadPtr mThreadPtr;
    SThreadedRequest request;
    CConnectionInterface* mOwner;
};

void CAsyncRequest::Set(const std::string url, CPostPtr post, RequestDelegate targetDelegate)
{
    request.sUrl = url;
    request.sPost = post;
    request.sTargetDelegate = targetDelegate;
}

void CAsyncRequest::Start()
{
   mThreadPtr = ThreadPtr(new boost::thread(boost::bind( &CAsyncRequest::ProcessRequest, this))); 
}

void CAsyncRequest::ProcessRequest(const std::string url, CPostPtr post , RequestDelegate targetDelegate)
{

    request();
    mOwner->ThreadFinish(this);
}

void CAsyncRequest::ProcessRequest()
{
	request();
	mOwner->ThreadFinish(this);
}


void CAsyncRequest::Start(const std::string url, CPostPtr post, RequestDelegate targetDelegate)
{
    mThreadPtr = ThreadPtr(new boost::thread(boost::bind( &CAsyncRequest::ProcessRequest, this, url, post, targetDelegate))); 
}

void CAsyncRequest::Stop()
{
    mThreadPtr->interrupt();
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
    std::list<CAsyncRequest*>::iterator it = mRequestQeue.begin();
    
    for(; it != mRequestQeue.end(); it++)
    {
        (*it)->Stop();
        delete (*it);
    }
    mThreadList.clear();
    
    it = mThreadList.begin();
    for(; it != mThreadList.end(); it++)
    {
        (*it)->Stop();
        delete (*it);
    }
    mThreadList.clear();
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

void CConnectionInterface::PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, bool forceToSend)
{
	PerformAsyncRequest(url, targetDelegate, CPostPtr(), forceToSend);
}

void CConnectionInterface::PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, CPostPtr postData , bool forceToSend)
{
    
    CAsyncRequest* request = new CAsyncRequest(this);
    request->Set(url, postData, targetDelegate);
    if( mThreadList.size() < kThreadLimit || forceToSend)
    {
		mThreadListMutex.lock();
		mThreadList.push_back(request);
		mThreadListMutex.unlock();
        request->Start();
    }
    else
    {
        mRequestQeueMutex.lock();
        mRequestQeue.push_back(request);
        mRequestQeueMutex.unlock();
    }
}

void CConnectionInterface::ThreadFinish(CAsyncRequest *thread)
{
    mThreadListMutex.lock();
    mThreadList.remove(thread);
    mThreadListMutex.unlock();
    delete thread;    
    if(mRequestQeue.size() > 0 && mThreadList.size() < kThreadLimit)
    {
        mRequestQeueMutex.lock();
        CAsyncRequest* newRequest = mRequestQeue.front();
        mRequestQeue.pop_front();
        newRequest->Start();
        mRequestQeueMutex.unlock();
        mThreadListMutex.lock();
        mThreadList.push_back(newRequest);
        mThreadListMutex.unlock();
    }
}

