#include "CGameVars.h"
#include "CPlaytomic.h"
#include <string>

namespace Playtomic
{

CGameVars::CGameVars()
{

}

CPlaytomicResponsePtr CGameVars::Load()
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kGameVarsUrl1 + gPlaytomic->GetGameGuid() + kGameVarsUrl2 +
		IdString + kGameVarsUrl3;

	return gConnectionInterface->PerformSyncRequest(url.c_str());
}

void CGameVars::LoadAsync(RequestDelegate targetDelegate)
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kGameVarsUrl1 + gPlaytomic->GetGameGuid() + kGameVarsUrl2 +
		IdString + kGameVarsUrl3;

	gConnectionInterface->PerformAsyncRequest(url.c_str(), targetDelegate);
}
}