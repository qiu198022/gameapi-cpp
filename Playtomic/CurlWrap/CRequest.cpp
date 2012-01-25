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
#include "CRequest.h"
#include "CPost.h"
#include <cstring>

#if defined(__ANDROID__) && defined(_DEBUG_ANDROID_CONNECTION_)
#include <android/log.h>
#define  LOG_TAG    "playtomicTest"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

size_t WriteMemory(void *contents, size_t size, size_t nmemb, void* userp)
{
	size_t realsize = size * nmemb;
	SRequestResult *mem =(SRequestResult*)userp;

	SRequestResult newBuffer;
	newBuffer.data = new char[realsize+ mem->size + 1];
	if(mem->data)
	{
		memcpy(newBuffer.data, mem->data, mem->size);
	}	
	memcpy(newBuffer.data+mem->size, contents, realsize);
	if(mem->data)
	{
		delete mem->data;
	}
	
	newBuffer.size = mem->size + realsize;
	newBuffer.data[newBuffer.size] = 0;
	*mem = newBuffer;
	newBuffer.data = NULL;
	return realsize;
}

SRequestResult::SRequestResult()
{
	data = NULL;
	size = 0;
}

SRequestResult::~SRequestResult()
{
	Clear();
}

void SRequestResult::Clear()
{
	if(data)
	{
		delete data;
		data = NULL;
	}

	size = 0;
}


CRequest::CRequest()
{
	mHandle = NULL;
}

CRequest::~CRequest()
{
	if(mHandle != NULL)
	{
		curl_easy_cleanup(mHandle);
		mHandle = NULL;
	}
}

void CRequest::SetPostData( CPost* post )
{
	if(mHandle != NULL)
	{
		curl_easy_setopt(mHandle, CURLOPT_HTTPPOST, post->GetPostStart());
	}
}

void CRequest::CreateQuery( const char* addres )
{
	
	if(mHandle != NULL)
	{
		curl_easy_cleanup(mHandle);
	}
	mHandle = curl_easy_init();

	if(mHandle)
	{
		curl_easy_setopt(mHandle, CURLOPT_URL, addres);
		curl_easy_setopt(mHandle, CURLOPT_WRITEFUNCTION, WriteMemory);
	}
	
}

ERequestResult CRequest::Perform(SRequestResult* dest)
{
	if(!mHandle)
	{
		mLastResult = e_unknown;
		return mLastResult;
	}
	
	curl_easy_setopt(mHandle, CURLOPT_WRITEDATA, dest);
	curl_easy_setopt(mHandle, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(mHandle, CURLOPT_TIMEOUT, 60);
	curl_easy_setopt(mHandle, CURLOPT_NOSIGNAL, 1);
	CURLcode res;
	res = curl_easy_perform(mHandle);
	
	curl_easy_cleanup(mHandle);
	mHandle = NULL;
	if(res == CURLE_OK)
	{
		mLastResult = e_Ok;
	}
	else
	{
		mLastResult = e_failToConnect;
	}

	return mLastResult;
}
