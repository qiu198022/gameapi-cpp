#ifndef _CPOST_H_
#define _CPOST_H_

#include "Curl/curl.h"
#include "Common.h"

 class CPost
{
public:
	enum EAddFormResult
	{
		e_formaddOk, /* first, no error */

		e_formaddMemory,
		e_formaddOption_twice,
		e_formaddNull,
		e_formaddUnknownOption,
		e_formaddIncomplete,
		e_formaddIllegalArray,
		e_formaddDisabled, /* libcurl was built with this disabled */

		e_formaddLast /* last */
	};
public:
	CPost();
	~CPost();

	EAddFormResult AddText(const char* fieldName, const char* value);
	EAddFormResult AddFile(const char* fileName, const char* filePath);
	EAddFormResult AddBuffer(const char* fieldName, const char* fileName, void* buffer, size_t bufferSize);
	
	
	curl_httppost* GetPostStart(void);
private:
	curl_httppost*	mFormPost;
	curl_httppost*	mLastPost;
	curl_slist*		mHeaderList;
};
#endif