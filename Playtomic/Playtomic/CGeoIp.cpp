#include "CGeoIP.h"
#include "CPlaytomic.h"
#include "../CurlWrap/CConnectionInterface.h"
#include <string>


namespace Playtomic
{

CGeoIP::CGeoIP()
{
}

CPlaytomicResponsePtr CGeoIP::Load()
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kGeoIpUrl1 + gPlaytomic->GetGameGuid() + kGeoIpUrl2 +
					 IdString + kGeoIpUrl3;

	return gConnectionInterface->PerformSyncRequest(url.c_str());
}

void CGeoIP::LoadAsync( RequestDelegate targetDelegate)
{
	
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kGeoIpUrl1 + gPlaytomic->GetGameGuid() + kGeoIpUrl2 +
		IdString + kGeoIpUrl3;

	gConnectionInterface->PerformAsyncRequest(url.c_str(), targetDelegate);
}

}