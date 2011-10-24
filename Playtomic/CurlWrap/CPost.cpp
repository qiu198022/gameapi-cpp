#include "CPost.h"
#include "CRequest.h"

CPost::CPost()
{
	mFormPost = NULL;
	mLastPost = NULL;
	mHeaderList = NULL;
}

CPost::~CPost()
{
	if (mFormPost)
	{
		curl_formfree(mFormPost);
	}
}

CPost::EAddFormResult CPost::AddText(const char* fieldName, const char* value)
{
	return (EAddFormResult)curl_formadd(&mFormPost, &mLastPost, CURLFORM_COPYNAME, fieldName, CURLFORM_COPYCONTENTS, value, CURLFORM_END);
}

CPost::EAddFormResult CPost::AddFile(const char* fileName, const char* filePath)
{
	return (EAddFormResult)curl_formadd(&mFormPost, &mFormPost, CURLFORM_COPYNAME, fileName, CURLFORM_FILENAME, filePath, CURLFORM_END);
}

CPost::EAddFormResult CPost::AddBuffer(const char* fieldName, const char* fileName, void* buffer, size_t bufferSize)
{
	return (EAddFormResult) curl_formadd(&mFormPost, &mLastPost, 
		         CURLFORM_COPYNAME, fieldName,
				 CURLFORM_BUFFER, fileName,
				 CURLFORM_BUFFERPTR, buffer,
				 CURLFORM_BUFFERLENGTH, bufferSize, CURLFORM_END);
}

curl_httppost* CPost::GetPostStart()
{
	return mFormPost;
}