#ifndef __CONNECTION_INTERFACE_H__
#define __CONNECTION_INTERFACE_H__

#include "CPlaytomicResponse.h"
#include "../Tools/FastDelegate.h"

typedef fastdelegate::FastDelegate1<CPlaytomicResponsePtr&> RequestDelegate;
class CPost;


class CConnectionInterface
{
	//singleton interface
public:
	static CConnectionInterface*	Get();
	static void						Destroy();

public:

	void Init();

	CPlaytomicResponsePtr PerformSyncRequest(const char* url, CPost* postData = NULL);

	void	PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, CPost* postData = NULL);

private:
	CConnectionInterface();
	~CConnectionInterface();

	static CConnectionInterface* sHandle;
};

#define gConnectionInterface CConnectionInterface::Get()

#endif