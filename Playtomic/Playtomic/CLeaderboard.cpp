#include "CLeaderboard.h"
#include "../CurlWrap/CPost.h"
#include "../CurlWrap/CConnectionInterface.h"
#include "../Tools/MD5.h"
#include "CPlaytomic.h"
#include <list>

namespace Playtomic
{

CLeaderboard::CLeaderboard()
{
	mDelegate = NULL;
}

void CLeaderboard::SetDelegate(CLeaderboardDelegate* targetDelegate)
{
	mDelegate = targetDelegate;
}

CPlaytomicResponsePtr CLeaderboard::SaveTable( const std::string& tableName, const CScore& score, bool highest, bool allowDuplicates )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrl2 +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("name", score.GetName().c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", score.GetPoints());
	postData.AddText("points", buff);
	
	sprintf_s(buff,299,"%s%d",gPlaytomic->GetSourceUrl().c_str(), score.GetPoints());
	postData.AddText("auth", MD5(buff).hexdigest().c_str());

	CustomData customData = score.GetCustomData();
	sprintf_s(buff,299,"%d", customData.size());
	postData.AddText("customfields", buff);

	int fieldNumber = 0;
	CustomData::iterator it = customData.begin();
	for(;it != customData.end(); it++)
	{
		sprintf_s(buff,299,"%d", fieldNumber);
		std::string ckey("ckey");
		ckey += buff;
		std::string cdata("cdata");
		cdata += buff;
		std::string value = it->second;
		fieldNumber++;

		postData.AddText(ckey.c_str(), it->first.c_str() );
		postData.AddText(cdata.c_str(), it->second.c_str());
	}

	return gConnectionInterface->PerformSyncRequest(url.c_str(), &postData);
}

SSCoreTable CLeaderboard::ListTable( const std::string& tableName, bool highest, const std::string& mode, int page, int perPage, CustomData customFilter )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrlList +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("mode", mode.c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", page);
	postData.AddText("page", buff);
	sprintf_s(buff, 299,"%d", perPage);
	postData.AddText("perpage", buff);
	sprintf_s(buff, 299,"%d", customFilter.size());
	postData.AddText("numfilters", buff);

	if(customFilter.size() > 0)
	{
		int fieldNumber = 0;
		CustomData::iterator it = customFilter.begin();
		for(;it != customFilter.end(); it++)
		{
			sprintf_s(buff,299,"%d", fieldNumber);
			std::string ckey("ckey");
			ckey += buff;
			std::string cdata("cdata");
			cdata += buff;
			std::string value = it->second;
			fieldNumber++;

			postData.AddText(ckey.c_str(), it->first.c_str() );
			postData.AddText(cdata.c_str(), it->second.c_str());
		}		
	}


	CPlaytomicResponsePtr request = gConnectionInterface->PerformSyncRequest(url.c_str(),&postData);

	SSCoreTable returnScores;
	returnScores.sErrorCode = request->ResponseError();
	if(!request->ResponseSucceded())
	{
		returnScores.sSucceded = false;
		
		return returnScores;
	}
	returnScores.sSucceded = true;
	FData	scoreTable(Json::arrayValue);

	const FData& queryData = request->ResponseData();

	FData ScoreList;


	ScoreList = queryData.get("Scores", ScoreList);
	
	FData value;
	value = queryData.get("NumScores", value);
	returnScores.sScoreCount = value.asInt();
	for (size_t i = 0; i < ScoreList.size(); i++)
	{
		FData currentScore;

		currentScore = ScoreList[i];

		value = currentScore.get("Name", value);
		std::string userName = value.asString();
		value = currentScore.get("Points", value);

		int points = value.asInt();

		value = currentScore.get("RDate",value);
		std::string relativeDate = value.asString();

		value = currentScore.get("Rank", value);
		int rank = value.asInt();


		value = currentScore.get("CustomData", value);
		
		Json::ValueIterator it = value.begin();
		CustomData customData;
		for(; it != value.end(); it++)
		{
			customData.insert(std::make_pair((*it).asString(), (*it).asString()));
		}

		returnScores.sScoreList.push_back(CScore(userName, points, relativeDate, customData, rank));
	}
	
	return returnScores;
}

SSCoreTable CLeaderboard::SaveAndListTable( const std::string& tableName,
											const CScore& score, bool highest, 
											bool allowDuplicates, const std::string& mode,
											int perPage, CustomData customFilter )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrlSaveAndList +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("name", score.GetName().c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", score.GetPoints());
	postData.AddText("points", buff);

	sprintf_s(buff,299,"%s%d",gPlaytomic->GetSourceUrl().c_str(), score.GetPoints());
	postData.AddText("auth", MD5(buff).hexdigest().c_str());

	CustomData customData = score.GetCustomData();
	sprintf_s(buff,299,"%d", customData.size());
	postData.AddText("numfields", buff);

	int fieldNumber = 0;
	CustomData::iterator it = customData.begin();
	for(;it != customData.end(); it++)
	{
		sprintf_s(buff,299,"%d", fieldNumber);
		std::string ckey("ckey");
		ckey += buff;
		std::string cdata("cdata");
		cdata += buff;
		std::string value = it->second;
		fieldNumber++;

		postData.AddText(ckey.c_str(), it->first.c_str() );
		postData.AddText(cdata.c_str(), it->second.c_str());
	}

	//list fields
	postData.AddText("mode", mode.c_str());
	sprintf_s(buff, 299,"%d", perPage);
	postData.AddText("perpage", buff);
	sprintf_s(buff, 299,"%d", customFilter.size());
	postData.AddText("numfilters", buff);

	
	if(customFilter.size() > 0)
	{
		int fieldNumber = 0;
		CustomData::iterator it = customFilter.begin();
		for(;it != customFilter.end(); it++)
		{
			sprintf_s(buff,299,"%d", fieldNumber);
			std::string ckey("ckey");
			ckey += buff;
			std::string cdata("cdata");
			cdata += buff;
			std::string value = it->second;
			fieldNumber++;

			postData.AddText(ckey.c_str(), it->first.c_str() );
			postData.AddText(cdata.c_str(), it->second.c_str());
		}		
	}
	
	CPlaytomicResponsePtr request(gConnectionInterface->PerformSyncRequest(url.c_str(),&postData));

	SSCoreTable returnScores;
	returnScores.sErrorCode = request->ResponseError();
	if(!request->ResponseSucceded())
	{
		returnScores.sSucceded = false;

		return returnScores;
	}
	returnScores.sSucceded = true;
	FData	scoreTable(Json::arrayValue);

	const FData& queryData = request->ResponseData();

	FData ScoreList;


	ScoreList = queryData.get("Scores", ScoreList);

	FData value;
	value = queryData.get("NumScores", value);
	returnScores.sScoreCount = value.asInt();
	for (size_t i = 0; i < ScoreList.size(); i++)
	{
		FData currentScore;

		currentScore = ScoreList[i];

		value = currentScore.get("Name", value);
		std::string userName = value.asString();
		value = currentScore.get("Points", value);

		int points = value.asInt();

		value = currentScore.get("RDate",value);
		std::string relativeDate = value.asString();

		value = currentScore.get("Rank", value);
		int rank = value.asInt();


		value = currentScore.get("CustomData", value);

		Json::ValueIterator it = value.begin();
		CustomData customData;
		for(; it != value.end(); it++)
		{
			customData.insert(std::make_pair(it.key().asString(), (*it).asString()));
		}

		returnScores.sScoreList.push_back(CScore(userName, points, relativeDate, customData, rank));
	}

	return returnScores;
}

//async calls

void CLeaderboard::SaveTableAsync( const std::string& tableName, const CScore& score, bool highest, bool allowDuplicates )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrl2 +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("name", score.GetName().c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", score.GetPoints());
	postData.AddText("points", buff);

	sprintf_s(buff,299,"%s%d",gPlaytomic->GetSourceUrl().c_str(), score.GetPoints());
	postData.AddText("auth", MD5(buff).hexdigest().c_str());

	CustomData customData = score.GetCustomData();
	sprintf_s(buff,299,"%d", customData.size());
	postData.AddText("customfields", buff);

	int fieldNumber = 0;
	CustomData::iterator it = customData.begin();
	for(;it != customData.end(); it++)
	{
		sprintf_s(buff,299,"%d", fieldNumber);
		std::string ckey("ckey");
		ckey += buff;
		std::string cdata("cdata");
		cdata += buff;
		std::string value = it->second;
		fieldNumber++;

		postData.AddText(ckey.c_str(), it->first.c_str() );
		postData.AddText(cdata.c_str(), it->second.c_str());
	}

	gConnectionInterface->PerformAsyncRequest(url.c_str(), fastdelegate::MakeDelegate(this, &CLeaderboard::SaveComple),&postData);
}

void CLeaderboard::ListTableAsync( const std::string& tableName, bool highest, const std::string& mode, int page, int perPage, CustomData customFilter )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrlList +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("mode", mode.c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", page);
	postData.AddText("page", buff);
	sprintf_s(buff, 299,"%d", perPage);
	postData.AddText("perpage", buff);
	sprintf_s(buff, 299,"%d", customFilter.size());
	postData.AddText("numfilters", buff);

	if(customFilter.size() > 0)
	{
		int fieldNumber = 0;
		CustomData::iterator it = customFilter.begin();
		for(;it != customFilter.end(); it++)
		{
			sprintf_s(buff,299,"%d", fieldNumber);
			std::string ckey("ckey");
			ckey += buff;
			std::string cdata("cdata");
			cdata += buff;
			std::string value = it->second;
			fieldNumber++;

			postData.AddText(ckey.c_str(), it->first.c_str() );
			postData.AddText(cdata.c_str(), it->second.c_str());
		}		
	}


	gConnectionInterface->PerformAsyncRequest(url.c_str(), fastdelegate::MakeDelegate(this, &CLeaderboard::ListComple),&postData);
}

void CLeaderboard::SaveAndListTableAsync( const std::string& tableName,
	const CScore& score, bool highest, 
	bool allowDuplicates, const std::string& mode,
	int perPage, CustomData customFilter )
{
	char IdString[50];
	sprintf_s(IdString,49,"%d",gPlaytomic->GameId());
	std::string url = kLeaderboardUrl1 + gPlaytomic->GetGameGuid() + kLeaderboardUrlSaveAndList +
		IdString + kLeaderboardUrl3;

	CPost postData;
	postData.AddText("url", gPlaytomic->GetSourceUrl().c_str());
	postData.AddText("table", tableName.c_str());
	postData.AddText("highest", highest ? "y": "n");
	postData.AddText("name", score.GetName().c_str());
	char buff[300];
	sprintf_s(buff,299,"%d", score.GetPoints());
	postData.AddText("points", buff);

	sprintf_s(buff,299,"%s%d",gPlaytomic->GetSourceUrl().c_str(), score.GetPoints());
	postData.AddText("auth", MD5(buff).hexdigest().c_str());

	CustomData customData = score.GetCustomData();
	sprintf_s(buff,299,"%d", customData.size());
	postData.AddText("numfields", buff);

	int fieldNumber = 0;
	CustomData::iterator it = customData.begin();
	for(;it != customData.end(); it++)
	{
		sprintf_s(buff,299,"%d", fieldNumber);
		std::string ckey("ckey");
		ckey += buff;
		std::string cdata("cdata");
		cdata += buff;
		std::string value = it->second;
		fieldNumber++;

		postData.AddText(ckey.c_str(), it->first.c_str() );
		postData.AddText(cdata.c_str(), it->second.c_str());
	}

	//list fields
	postData.AddText("mode", mode.c_str());
	sprintf_s(buff, 299,"%d", perPage);
	postData.AddText("perpage", buff);
	sprintf_s(buff, 299,"%d", customFilter.size());
	postData.AddText("numfilters", buff);


	if(customFilter.size() > 0)
	{
		int fieldNumber = 0;
		CustomData::iterator it = customFilter.begin();
		for(;it != customFilter.end(); it++)
		{
			sprintf_s(buff,299,"%d", fieldNumber);
			std::string ckey("ckey");
			ckey += buff;
			std::string cdata("cdata");
			cdata += buff;
			std::string value = it->second;
			fieldNumber++;

			postData.AddText(ckey.c_str(), it->first.c_str() );
			postData.AddText(cdata.c_str(), it->second.c_str());
		}		
	}

	gConnectionInterface->PerformAsyncRequest(url.c_str(), fastdelegate::MakeDelegate(this, &CLeaderboard::SaveAndListComple),&postData);

	
}

void CLeaderboard::SaveComple( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	mDelegate->SaveComplete(response);
}

void CLeaderboard::ListComple( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}
	SSCoreTable returnScores;
	returnScores.sErrorCode = response->ResponseError();
	if(!response->ResponseSucceded())
	{
		returnScores.sSucceded = false;

		mDelegate->ListTableComple(returnScores);
	}
	returnScores.sSucceded = true;
	FData	scoreTable(Json::arrayValue);

	const FData& queryData = response->ResponseData();

	FData ScoreList;


	ScoreList = queryData.get("Scores", ScoreList);

	FData value;
	value = queryData.get("NumScores", value);
	returnScores.sScoreCount = value.asInt();
	for (size_t i = 0; i < ScoreList.size(); i++)
	{
		FData currentScore;

		currentScore = ScoreList[i];

		value = currentScore.get("Name", value);
		std::string userName = value.asString();
		value = currentScore.get("Points", value);

		int points = value.asInt();

		value = currentScore.get("RDate",value);
		std::string relativeDate = value.asString();

		value = currentScore.get("Rank", value);
		int rank = value.asInt();


		value = currentScore.get("CustomData", value);

		Json::ValueIterator it = value.begin();
		CustomData customData;
		for(; it != value.end(); it++)
		{
			customData.insert(std::make_pair((*it).asString(), (*it).asString()));
		}

		returnScores.sScoreList.push_back(CScore(userName, points, relativeDate, customData, rank));
	}

	mDelegate->ListTableComple(returnScores);;
}

void CLeaderboard::SaveAndListComple( CPlaytomicResponsePtr& response )
{
	if(mDelegate == NULL)
	{
		return;
	}

	SSCoreTable returnScores;
	returnScores.sErrorCode = response->ResponseError();
	if(!response->ResponseSucceded())
	{
		returnScores.sSucceded = false;

		mDelegate->SaveAndListComple(returnScores);
	}
	returnScores.sSucceded = true;
	FData	scoreTable(Json::arrayValue);

	const FData& queryData = response->ResponseData();

	FData ScoreList;


	ScoreList = queryData.get("Scores", ScoreList);

	FData value;
	value = queryData.get("NumScores", value);
	returnScores.sScoreCount = value.asInt();
	for (size_t i = 0; i < ScoreList.size(); i++)
	{
		FData currentScore;

		currentScore = ScoreList[i];

		value = currentScore.get("Name", value);
		std::string userName = value.asString();
		value = currentScore.get("Points", value);

		int points = value.asInt();

		value = currentScore.get("RDate",value);
		std::string relativeDate = value.asString();

		value = currentScore.get("Rank", value);
		int rank = value.asInt();


		value = currentScore.get("CustomData", value);

		Json::ValueIterator it = value.begin();
		CustomData customData;
		for(; it != value.end(); it++)
		{
			customData.insert(std::make_pair(it.key().asString(), (*it).asString()));
		}

		returnScores.sScoreList.push_back(CScore(userName, points, relativeDate, customData, rank));
	}

	mDelegate->SaveAndListComple(returnScores);
}

}