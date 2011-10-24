#ifndef __CURL_WRAP_COMMON_H__
#define __CURL_WRAP_COMMON_H__

enum ERequestResult 
{
	e_Ok,
	e_failToConnect,
	e_unknown
};

#include "../json/include/value.h"

//FData = Flexible Data
typedef Json::Value	FData;
#endif