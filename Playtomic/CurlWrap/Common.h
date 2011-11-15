#ifndef __CURL_WRAP_COMMON_H__
#define __CURL_WRAP_COMMON_H__

#ifdef CREATE_DLL
#define DllExport __declspec(dllexport)
#else
#ifdef LINK_DLL
#define DllExport __declspec(dllimport)
#else
#define DllExport
#endif
#endif


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