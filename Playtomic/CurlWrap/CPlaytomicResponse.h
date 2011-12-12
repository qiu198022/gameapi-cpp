#ifndef __CPLAYTOMIC_RESPONSE_H__
#define __CPLAYTOMIC_RESPONSE_H__

#include "Common.h"
#ifdef __ANDROID__
#include "boostFix.h"
#endif
#include "boost/shared_ptr.hpp"


class DllExport CPlaytomicResponse
{
public:
	CPlaytomicResponse();
	CPlaytomicResponse(int errorCode);
	CPlaytomicResponse(bool success, int errorCode);
	CPlaytomicResponse(bool success, int errorCode, const FData& source, int resultCount);
	CPlaytomicResponse(const CPlaytomicResponse& source);

	bool ResponseSucceded() const;
	void ResponseSucceded(bool val) ;
	int ResponseError() const;
	void ResponseError(int val);
	const FData& ResponseData() const ;
	void ResponseData(const FData& val) ;
	int NumResult() const ;
	void NumResult(int val);

	CPlaytomicResponse& operator=(const CPlaytomicResponse& source);
private:
	bool		mResponseSucceded;	
	int			mResponseError;	
	FData		mResponseData;	
	int			mNumResult;
	
};

typedef boost::shared_ptr<CPlaytomicResponse> CPlaytomicResponsePtr;
#endif
