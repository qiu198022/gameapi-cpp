#include "CRequest.h"
#include "CPost.h"

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