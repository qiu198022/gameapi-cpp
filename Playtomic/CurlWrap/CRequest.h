#ifndef __CREQUEST_H__
#define __CREQUEST_H__

#include "Curl/curl.h"
#include "Common.h"

class CPost;

struct SRequestResult
{
public:
	char*	data;
	size_t	size;

	void Clear();
	SRequestResult();
	~SRequestResult();
};
class CRequest
{
public:
	
public:
	CRequest();
	~CRequest();


	void			CreateQuery(const char* addres);
	void			SetPostData(CPost* post);
	ERequestResult	Perform(SRequestResult* dest);
private:
	CURL *mHandle;

	ERequestResult mLastResult;

};

#endif