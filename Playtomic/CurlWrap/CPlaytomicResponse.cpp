#include "CPlaytomicResponse.h"

CPlaytomicResponse::CPlaytomicResponse()
	: mResponseError(0),
	mResponseSucceded(false),
	mNumResult(0),
	mResponseData( Json::nullValue)
{

}

CPlaytomicResponse::CPlaytomicResponse(int errorCode)
	: mResponseError(errorCode),
	mResponseSucceded(false),
	mNumResult(0),
	mResponseData( Json::nullValue)
{
}


CPlaytomicResponse::CPlaytomicResponse(bool success, int errorCode)
	: mResponseError(errorCode),
	mResponseSucceded(success),
	mNumResult(0),
	mResponseData( Json::nullValue)
{
}

CPlaytomicResponse::CPlaytomicResponse(
	bool success, 
	int errorCode, 
	const FData& source,
	int resultCount)
	: mResponseError(errorCode),
	mResponseSucceded(success),
	mNumResult(resultCount),
	mResponseData(source)
{
}

CPlaytomicResponse::CPlaytomicResponse(const CPlaytomicResponse& source)
{
	*this = source;
}

bool CPlaytomicResponse::ResponseSucceded() const
{ 
	return mResponseSucceded;
}
void CPlaytomicResponse::ResponseSucceded(bool val)
{ 
	mResponseSucceded = val; 
}

int CPlaytomicResponse::ResponseError() const 
{ 
	return mResponseError;
}

void CPlaytomicResponse::ResponseError(int val) 
{ 
	mResponseError = val; 
}

const FData& CPlaytomicResponse::ResponseData() const
{
	return mResponseData;
}

void CPlaytomicResponse::ResponseData(const FData& val)
{ 
	mResponseData = val;
}

int CPlaytomicResponse::NumResult() const 
{ 
	return mNumResult; 
}

void CPlaytomicResponse::NumResult(int val)
{ 
	mNumResult = val; 
}


CPlaytomicResponse& CPlaytomicResponse::operator= (const CPlaytomicResponse& source)
{
	mNumResult = source.mNumResult;
	mResponseData = source.mResponseData;
	mResponseError = source.mResponseError;
	mResponseSucceded = source.mResponseSucceded;
	return *this;
}