#ifndef __CONNECTION_INTERFACE_H__
#define __CONNECTION_INTERFACE_H__

#include "CPlaytomicResponse.h"
#include "../Tools/FastDelegate.h"

#ifndef _CPOST_H_
#include "CPost.h"
#endif

typedef fastdelegate::FastDelegate1<CPlaytomicResponsePtr&> RequestDelegate;


typedef boost::shared_ptr<CPost> CPostPtr;

class CConnectionInterface
{
	//singleton interface
public:
	static CConnectionInterface*	Get();
	static void						Destroy();

public:

	void Init();

	CPlaytomicResponsePtr PerformSyncRequest(const char* url, CPost* postData = NULL);

	void	PerformAsyncRequest(const char* url, RequestDelegate targetDelegate);
	void	PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, CPostPtr postData);

private:
	CConnectionInterface();
	~CConnectionInterface();

	static CConnectionInterface* sHandle;
};

#define gConnectionInterface CConnectionInterface::Get()

#endif