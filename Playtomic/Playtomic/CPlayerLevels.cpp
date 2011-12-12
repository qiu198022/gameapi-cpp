#include "CPlayerLevels.h"
#include "CPlaytomic.h"
#include "../CurlWrap/CConnectionInterface.h"
#include "../CurlWrap/CPost.h"

namespace Playtomic
{
CPlayerLevels::CPlayerLevels()
{
	mDelegate = 0;
}

void CPlayerLevels::SetDelegate(IPlayerLevelDelegate* targetDelegate)
{
	mDelegate = targetDelegate;
}

SLevelListPtr CPlayerLevels::LoadLevel( const std::string& levelId )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelUrl2 +
		IdString + kPlayerLevelUrl3 + levelId;

	CPlaytomicResponsePtr response = gConnectionInterface->PerformSyncRequest(url.c_str());
	SLevelListPtr returnList(new SLevelList);
	returnList->sErrorCode = response->ResponseError();
	returnList->sSucceded = response->ResponseSucceded();
	if(!response->ResponseSucceded())
	{
		return returnList;
	}
	AddLevel(response->ResponseData(), levelId, returnList->sLevelList);

	return returnList;
}

CPlaytomicResponsePtr CPlayerLevels::RateLevel( const std::string& levelId, int rating )
{
	if(rating > 10 || rating < 1)
    {
        return CPlaytomicResponsePtr(new CPlaytomicResponse(false, 401));
    }
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelRateUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelRateUrl2 +
		IdString + kPlayerLevelRateUrl3 + levelId + kPlayerLevelRateUrl4;
	sprintf_s(IdString,49,"%d", rating);
	url += IdString;

	CPlaytomicResponsePtr response = gConnectionInterface->PerformSyncRequest(url.c_str());
	return response;
}

SLevelListPtr CPlayerLevels::List( const std::string& mode, 
	int page, int perPage,
	bool includeData, bool includeThumbs,
	const CustomData& customFilter )
{
	std::string modeSafe = mode.empty() ? "popular" : (mode == "newest" || mode == "popular" ? mode : "popular");
	char dataSafe = includeData ? 'y': 'n';
	char thumSafe = includeThumbs ? 'y': 'n';

	
	
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelListUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelListUrl2 +
		IdString + kPlayerLevelListUrl3 + modeSafe;
	sprintf_s(IdString,49,"%d", page);
	url += kPlayerLevelListUrl4 + page;
	sprintf_s(IdString,49,"%d", perPage);
	url += kPlayerLevelListUrl5; url += IdString;
	url += kPlayerLevelListUrl6;
	url += dataSafe;
	url += kPlayerLevelListUrl7;
	url += thumSafe;
	sprintf_s(IdString,49,"%d", customFilter.size());
	url += kPlayerLevelListUrl10;
	url += IdString;

	CPost postData;

	if(!customFilter.empty())
	{
		int fieldNumber = 0;
		CustomData::const_iterator  it = customFilter.begin();
		for(; it != customFilter.end(); it++)
		{
			char buff[10];
			sprintf_s(buff,9,"%d", fieldNumber);
			std::string ckey("ckey");
			std::string cdata("cdata");
			ckey += buff;
			cdata += buff;
			
			postData.AddText(ckey.c_str(), it->first.c_str());
			postData.AddText(cdata.c_str(), it->second.c_str());
		}
	}
	CPlaytomicResponsePtr response = gConnectionInterface->PerformSyncRequest(url.c_str(), &postData);
	SLevelListPtr returnList( new SLevelList);
	returnList->sErrorCode = response->ResponseError();
	returnList->sSucceded = response->ResponseSucceded();
	if (!returnList->sSucceded)
	{
		return returnList;
	}
	FData	levelArray(Json::arrayValue);

	const FData& queryData = response->ResponseData();

	FData ScoreList;


	levelArray = queryData.get("Levels", levelArray);

	
	FData value;
	value = queryData.get("NumLevels", value);
	for (size_t i = 0; i < levelArray.size(); i++)
	{
		value = levelArray[(int)i].get("LevelId", value);

	
		AddLevel(levelArray[(int)i], value.asString(), returnList->sLevelList);
	}
	return returnList;
}

SLevelListPtr CPlayerLevels::SaveLevel( CLevel& level )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelSaveUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelSaveUrl2 +
		IdString + kPlayerLevelSaveUrl3 + gPlaytomic->GetSourceUrl();
	CPost postData;

	postData.AddText("data", level.GetData().c_str());
	postData.AddText("playerid", level.GetPlayerId().c_str());
	postData.AddText("playername", level.GetPlayerName().c_str());
	postData.AddText("playersource", level.GetPlayerSource().c_str());
	postData.AddText("name",level.GetName().c_str());
	postData.AddText("nothumb", "y");

	sprintf_s(IdString, 49, "%d", level.GetCustomData().size());
	postData.AddText("customfields", IdString);

	const CustomData& customData = level.GetCustomData();
	CustomData::const_iterator it = customData.begin();
	int fieldNumber = 0;
	for (; it != customData.end(); it++)
	{
		char buff[10];
		sprintf_s(buff,9,"%d", fieldNumber);
		std::string ckey("ckey");
		std::string cdata("cdata");
		ckey += buff;
		cdata += buff;

		postData.AddText(ckey.c_str(), it->first.c_str());
		postData.AddText(cdata.c_str(), it->second.c_str());
	}

	CPlaytomicResponsePtr response = gConnectionInterface->PerformSyncRequest(url.c_str(), &postData);
	SLevelListPtr returnList(new SLevelList);
	returnList->sErrorCode = response->ResponseError();
	returnList->sSucceded = response->ResponseSucceded();
	if(!response->ResponseSucceded())
	{
		return returnList;
	}

	FData id;
	id = response->ResponseData().get("LevelId", id);
	std::list<CLevel> levelList;
	AddLevel(response->ResponseData(), id.asString(), returnList->sLevelList);

	return returnList;
}

void CPlayerLevels::AddLevel( const FData& level, const std::string& levelId, std::list<CLevel>& levelList )
{
	FData value;
	value = level.get("PlayerId",value);
	if(!value.isString())
	{
		return;
	}
	std::string playerId(value.asString());
	value = level.get("PlayerName",value);
	std::string playerName(value.asString());
	value = level.get("PlayerSource",value);
	std::string playerSource(value.asString());
	value = level.get("Name",value);
	std::string name(value.asString());
	value = level.get("Data",value);
	std::string ldata(value.asString());
	value = level.get("thumb",value);
	std::string lthumb(value.asString());
	value = level.get("RDate",value);
	std::string relativeDate(value.asString());
	value = level.get("SDate",value);
	std::string date(value.asString());
	value = level.get("Plays",value);
	int plays = value.asInt();
	value = level.get("Votes",value);
	int votes = value.asInt();
	value = level.get("Score",value);
	int score = value.asInt();
	value = level.get("Rating",value);
	float rating = value.asFloat();
	value = level.get("CustomData",value);

	CustomData	customData;
	Json::ValueIterator it = value.begin();
	for(; it != value.end(); it++)
	{
		customData.insert(std::make_pair(it.key().asString(), (*it).asString()));
	}
	
	levelList.push_back( CLevel(name, playerName, playerId,
						playerSource, ldata, lthumb, votes, plays,
						rating, score, relativeDate, customData, levelId));
}


//ASYNC


void CPlayerLevels::LoadLevelAsync( const std::string& levelId )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelUrl2 +
		IdString + kPlayerLevelUrl3 + levelId;

	mLevelId = levelId;

	gConnectionInterface->PerformAsyncRequest(url.c_str(),fastdelegate::MakeDelegate(this, &CPlayerLevels::LoadLevelComplete));
}

void CPlayerLevels::RateLevelAsync( const std::string& levelId, int rating )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelRateUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelRateUrl2 +
		IdString + kPlayerLevelRateUrl3 + levelId + kPlayerLevelRateUrl4;
	sprintf_s(IdString,49,"%d", rating);
	url += IdString;

	gConnectionInterface->PerformAsyncRequest(url.c_str(), fastdelegate::MakeDelegate(this, &CPlayerLevels::RateLevelComplete));
}

void CPlayerLevels::ListAsync( const std::string& mode, 
	int page, int perPage,
	bool includeData, bool includeThumbs,
	const CustomData& customFilter )
{
	std::string modeSafe = mode.empty() ? "popular" : (mode == "newest" || mode == "popular" ? mode : "popular");
	char dataSafe = includeData ? 'y': 'n';
	char thumSafe = includeThumbs ? 'y': 'n';



	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelListUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelListUrl2 +
		IdString + kPlayerLevelListUrl3 + modeSafe;
	sprintf_s(IdString,49,"%d", page);
	url += kPlayerLevelListUrl4 + page;
	sprintf_s(IdString,49,"%d", perPage);
	url += kPlayerLevelListUrl5; url += IdString;
	url += kPlayerLevelListUrl6;
	url += dataSafe;
	url += kPlayerLevelListUrl7;
	url += thumSafe;
	sprintf_s(IdString,49,"%d", customFilter.size());
	url += kPlayerLevelListUrl10;
	url += IdString;

	CPostPtr postData(new CPost);

	if(!customFilter.empty())
	{
		int fieldNumber = 0;
		CustomData::const_iterator  it = customFilter.begin();
		for(; it != customFilter.end(); it++)
		{
			char buff[10];
			sprintf_s(buff,9,"%d", fieldNumber);
			std::string ckey("ckey");
			std::string cdata("cdata");
			ckey += buff;
			cdata += buff;

			postData->AddText(ckey.c_str(), it->first.c_str());
			postData->AddText(cdata.c_str(), it->second.c_str());
		}
	}
	gConnectionInterface->PerformAsyncRequest(url.c_str(), 
		fastdelegate::MakeDelegate(this, &CPlayerLevels::ListAsyncComplete), postData);
	
}

void CPlayerLevels::SaveLevelAsync( CLevel& level )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kPlayerLevelSaveUrl1 + gPlaytomic->GetGameGuid() +kPlayerLevelSaveUrl2 +
		IdString + kPlayerLevelSaveUrl3 + gPlaytomic->GetSourceUrl();
	CPostPtr postData(new CPost);

	postData->AddText("data", level.GetData().c_str());
	postData->AddText("playerid", level.GetPlayerId().c_str());
	postData->AddText("playername", level.GetPlayerName().c_str());
	postData->AddText("playersource", level.GetPlayerSource().c_str());
	postData->AddText("name",level.GetName().c_str());
	postData->AddText("nothumb", "y");

	sprintf_s(IdString, 49, "%d", level.GetCustomData().size());
	postData->AddText("customfields", IdString);

	const CustomData& customData = level.GetCustomData();
	CustomData::const_iterator it = customData.begin();
	int fieldNumber = 0;
	for (; it != customData.end(); it++)
	{
		char buff[10];
		sprintf_s(buff,9,"%d", fieldNumber);
		std::string ckey("ckey");
		std::string cdata("cdata");
		ckey += buff;
		cdata += buff;

		postData->AddText(ckey.c_str(), it->first.c_str());
		postData->AddText(cdata.c_str(), it->second.c_str());
	}

	gConnectionInterface->PerformAsyncRequest(url.c_str(), fastdelegate::MakeDelegate(this, &CPlayerLevels::SaveLevelComplete), postData);
	
}


void CPlayerLevels::LoadLevelComplete( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	SLevelList returnList;
	returnList.sErrorCode = response->ResponseError();
	returnList.sSucceded = response->ResponseSucceded();
	if(!response->ResponseSucceded())
	{
		mDelegate->LoadLevelComplete(returnList);
	}
	AddLevel(response->ResponseData(), mLevelId, returnList.sLevelList);

	mDelegate->LoadLevelComplete(returnList);
}

void CPlayerLevels::RateLevelComplete( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	mDelegate->RateLevelComplete(response);
}

void CPlayerLevels::ListAsyncComplete( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	SLevelList returnList;
	returnList.sErrorCode = response->ResponseError();
	returnList.sSucceded = response->ResponseSucceded();
	if (!returnList.sSucceded)
	{
		mDelegate->LevelListComple(returnList);
	}
	FData	levelArray(Json::arrayValue);

	const FData& queryData = response->ResponseData();

	FData ScoreList;


	levelArray = queryData.get("Levels", levelArray);


	FData value;
	value = queryData.get("NumLevels", value);
	for (size_t i = 0; i < levelArray.size(); i++)
	{
		value = levelArray[(int)i].get("LevelId", value);


		AddLevel(levelArray[(int)i], value.asString(), returnList.sLevelList);
	}
	mDelegate->LevelListComple(returnList);
}

void CPlayerLevels::SaveLevelComplete( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	SLevelList returnList;
	returnList.sErrorCode = response->ResponseError();
	returnList.sSucceded = response->ResponseSucceded();
	if(!response->ResponseSucceded())
	{
		mDelegate->SaveLevelComple(returnList);
	}

	FData id;
	id = response->ResponseData().get("LevelId", id);
	std::list<CLevel> levelList;
	AddLevel(response->ResponseData(), id.asString(), returnList.sLevelList);

	mDelegate->SaveLevelComple(returnList);
}

}


