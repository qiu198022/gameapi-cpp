//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 12/2/11.
//  Copyright 2011 Playtomic LLC. All rights reserved.
//
//  Documentation is available at:
//  http://playtomic.com/api/cpp
//
// PLEASE NOTE:
// You may modify this SDK if you wish but be kind to our servers.  Be
// careful about modifying the analytics stuff as it may give you
// borked reports.
//
// If you make any awesome improvements feel free to let us know!
//
// -------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY PLAYTOMIC, LLC "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "PlaytomicDemo.h"

#include "Playtomic/CLog.h"
#include "Playtomic/CData.h"
#include "Playtomic/DataStructures.h"
#include "Playtomic/CGameVars.h"
#include "Playtomic/CGeoIp.h"
#include "Playtomic/CLogRequest.h"
#include <android/log.h>
#include "JavaInterface.h"
#define  LOG_TAG    "playtomicTest"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
using namespace Playtomic;

CPlaytomicDemo::CPlaytomicDemo(int gameId, std::string& gameguid, bool autoUpdate, const std::string& filePath)
{
	CLogRequest::SetLogFileName(filePath.c_str());
	mPlaytomicInstance = new CPlaytomic(gameId, gameguid, autoUpdate);
	mLevels.sLevelCount = 0;
}

CPlaytomicDemo::~CPlaytomicDemo()
{
	CPlaytomic::Destroy();
}

void CPlaytomicDemo::LogView()
{
	mPlaytomicInstance->Log()->View();
	PostString("log View");
}

void CPlaytomicDemo::LogPlay()
{
	mPlaytomicInstance->Log()->Play();
	PostString("log Play");
}

void CPlaytomicDemo::LogCustomMetric()
{
	mPlaytomicInstance->Log()->CustomMetric("customTest","Android", false);
}

void CPlaytomicDemo::LogCounterMetric()
{
	mPlaytomicInstance->Log()->LevelCounterMetric("counterTest","Android", false);
}

void CPlaytomicDemo::LogAverageMetric()
{
	mPlaytomicInstance->Log()->LevelAverageMetric("customTest","Android", 500, false);
}

void CPlaytomicDemo::SaveLevel()
{
	std::string levelName("AndroidLevel");
	CLevel level(levelName, "AndroidPlayer", "android tester", "some android data");
	mPlaytomicInstance->PlayerLevels()->SetDelegate(this);
	mPlaytomicInstance->PlayerLevels()->SaveLevelAsync(level);
}

void CPlaytomicDemo::ListLevels()
{
	Playtomic::CustomData customData;
	gPlaytomic->PlayerLevels()->SetDelegate(this);
	gPlaytomic->PlayerLevels()->ListAsync("",1,10,false,false,customData);
}
void CPlaytomicDemo::LoadLevel()
{
	mPlaytomicInstance->PlayerLevels()->SetDelegate(this);
	if(mLevels.sLevelCount == 0)
	{
		PostString("there is no listed levels");
		return;
	}
	gPlaytomic->PlayerLevels()->LoadLevelAsync(mLevels.sLevelList.begin()->GetLevelId());
}

void CPlaytomicDemo::RateLevel()
{
	if(mLevels.sLevelCount == 0)
	{
		PostString("there is no listed levels");
		return;
	}
	mPlaytomicInstance->PlayerLevels()->SetDelegate(this);
	gPlaytomic->PlayerLevels()->RateLevelAsync(mLevels.sLevelList.begin()->GetLevelId(), 8);
}


void CPlaytomicDemo::SaveScore()
{
	CustomData filter;
	std::string playerName("AndroidDemo");
	CScore scoreData(playerName, 123456);
	gPlaytomic->Leaderboards()->SetDelegate(this);
	std::string tableName("Android Table");
	gPlaytomic->Leaderboards()->SaveAsync( tableName, scoreData,true,true);
}

void CPlaytomicDemo::ListScores()
{
	CustomData filter;
	gPlaytomic->Leaderboards()->SetDelegate(this);
	gPlaytomic->Leaderboards()->ListAsync("Android Table",true,"last7days", 1,10 , filter);
}

void CPlaytomicDemo::SaveAndListScore()
{
	CustomData filter;
	CScore scoreData("AndroidDemo", 123456);
	gPlaytomic->Leaderboards()->SetDelegate(this);
	Playtomic::gPlaytomic->Leaderboards()->SaveAndListAsync
				("Android Table", scoreData,true,true,"last7days",10 , filter);
}

void CPlaytomicDemo::GetGameVars()
{
	gPlaytomic->GameVars()->LoadAsync(fastdelegate::MakeDelegate(this,&CPlaytomicDemo::GameVarsFinish));
}

void CPlaytomicDemo::GetLocation()
{
	gPlaytomic->GeoIP()->LoadAsync(fastdelegate::MakeDelegate(this,&CPlaytomicDemo::LocationFinish));
}

//data lookup
void CPlaytomicDemo::GetViews()
{
	gPlaytomic->Data()->ViewsAsync(fastdelegate::MakeDelegate(this,&CPlaytomicDemo::ViewFinish));
}

void CPlaytomicDemo::GetPlays()
{
	gPlaytomic->Data()->PlaysAsync(fastdelegate::MakeDelegate(this,&CPlaytomicDemo::PlaysFinish));
}

void CPlaytomicDemo::GetPlayTime()
{
	gPlaytomic->Data()->PlaytimeAsync(fastdelegate::MakeDelegate(this,&CPlaytomicDemo::PlayTimeFinish));
}

void CPlaytomicDemo::RateLevelComplete(CPlaytomicResponsePtr& result)
{
	PostString("Rate level:");
	if(result->ResponseSucceded())
	{
		PostString("Succeded!");
	}
	else
	{
		char buff[256];
		sprintf(buff, "Failed, Error Code: %d", result->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::LevelListComple(SLevelList& result)
{
	PostString("List Level level:");
	char buff[256];
	if(result.sSucceded)
	{
		PostString("Succeded!");
		PostString("Levels:");
		std::list<Playtomic::CLevel>::iterator it = result.sLevelList.begin();
		mLevels = result;
		for (; it != result.sLevelList.end(); it++)
		{
			PostString("Level Data {");
			sprintf(buff, "name: %s", it->GetName().c_str());
			PostString(buff);
			sprintf(buff, "LevelId: %s", it->GetLevelId().c_str());
			PostString(buff);
			sprintf(buff, "PlayerName: %s", it->GetPlayerName().c_str());
			PostString(buff);
			PostString("}");
		}

	}
	else
	{
		sprintf(buff, "Failed, Error Code: %d", result.sErrorCode);
		PostString(buff);
	}
}

void CPlaytomicDemo::SaveLevelComple(SLevelList& result)
{
	PostString("Save level:");
	if(result.sSucceded)
	{
		PostString("Succeded!");
	}
	else
	{
		char buff[256];
		sprintf(buff, "Failed, Error Code: %d", result.sErrorCode);
		PostString(buff);
	}
}

void CPlaytomicDemo::LoadLevelComplete(SLevelList& result)
{
	PostString("Load level:");
	char buff[256];
	if(result.sSucceded)
	{
		PostString("Succeded!");
		PostString("Levels:");
		std::list<Playtomic::CLevel>::iterator it = result.sLevelList.begin();
		for (; it != result.sLevelList.end(); it++)
		{
			PostString("Level Data {");
			sprintf(buff, "name: %s", it->GetName().c_str());
			PostString(buff);
			sprintf(buff, "LevelId: %s", it->GetLevelId().c_str());
			PostString(buff);
			sprintf(buff, "PlayerName: %s", it->GetPlayerName().c_str());
			PostString(buff);
			PostString("}");
		}

	}
	else
	{
		sprintf(buff, "Failed, Error Code: %d", result.sErrorCode);
		PostString(buff);
	}
}

void CPlaytomicDemo::SaveComplete(CPlaytomicResponsePtr& result)
{
	PostString("Save Score:");
	if(result->ResponseSucceded())
	{
		PostString("Succeded!");
	}
	else
	{
		char buff[256];
		sprintf(buff, "Failed, Error Code: %d", result->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::ListTableComple(SSCoreTable& result)
{
	PostString("List Score Table:");
	char buff[256];
	if(result.sSucceded)
	{
		PostString("Succeded!");
		PostString("Scores:");
		PostString("Score Data {");
		std::list<CScore>::iterator it = result.sScoreList.begin();
		for (; it != result.sScoreList.end(); it++)
		{
			PostString("Score Entry {");
			sprintf(buff, "name: %s", it->GetName().c_str());
			PostString(buff);
			sprintf(buff, "Score: %d", it->GetPoints());
			PostString(buff);
			sprintf(buff, "Rank: %d", it->GetRank());
			PostString(buff);
			sprintf(buff, "Date: %s", it->GetRelativeDate().c_str());
			PostString(buff);
			PostString("}");
		}
		PostString("}");
	}
	else
	{
		sprintf(buff, "Failed, Error Code: %d", result.sErrorCode);
		PostString(buff);
	}
}

void CPlaytomicDemo::SaveAndListComple(SSCoreTable& result)
{
	PostString("Save and List Score:");
	char buff[256];
	if(result.sSucceded)
	{
		PostString("Succeded!");
		PostString("Scores:");
		std::list<CScore>::iterator it = result.sScoreList.begin();
		for (; it != result.sScoreList.end(); it++)
		{
			PostString("Score Data {");
			sprintf(buff, "name: %s", it->GetName().c_str());
			PostString(buff);
			sprintf(buff, "Score: %d", it->GetPoints());
			PostString(buff);
			sprintf(buff, "Rank: %d", it->GetRank());
			PostString(buff);
			sprintf(buff, "Date: %s", it->GetRelativeDate().c_str());
			PostString(buff);
			PostString("}");
		}

	}
	else
	{
		sprintf(buff, "Failed, Error Code: %d", result.sErrorCode);
		PostString(buff);
	}

}

void CPlaytomicDemo::ViewFinish(CPlaytomicResponsePtr& response)
{
	PostString("Get Views:");
	char buff[256];
	if(response->ResponseSucceded())
	{
		PostString("Succeded!");
		PostString("{");
		CGenericMetric value( response->ResponseData());
		sprintf(buff, "Value: %d", value.mValue);
		PostString(buff);
		PostString("}");
	}
	else
	{

		sprintf(buff, "Failed, Error Code: %d", response->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::PlayTimeFinish(CPlaytomicResponsePtr& response)
{
	PostString("Get Playtime:");
	char buff[256];
	if(response->ResponseSucceded())
	{
		PostString("Succeded!");
		PostString("{");
		CGenericMetric value( response->ResponseData());
		sprintf(buff, "Value: %d", value.mValue);
		PostString(buff);
		PostString("}");
	}
	else
	{

		sprintf(buff, "Failed, Error Code: %d", response->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::PlaysFinish(CPlaytomicResponsePtr& response)
{
	PostString("Get Plays:");
	char buff[256];
	if(response->ResponseSucceded())
	{
		PostString("Succeded!");
		PostString("{");
		CGenericMetric value( response->ResponseData());
		sprintf(buff, "Value: %d", value.mValue);
		PostString(buff);
		PostString("}");
	}
	else
	{

		sprintf(buff, "Failed, Error Code: %d", response->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::GameVarsFinish(CPlaytomicResponsePtr& response)
{
	PostString("Get Game Vars:");
	char buff[256];
	if(response->ResponseSucceded())
	{
		PostString("Succeded!");
		PostString("{");
		FData array;
		array = response->ResponseData();
		if(array.size() == 0)
		{
			PostString(" empty game vars");
		}
		else
		{
			FData value;
			for (size_t i = 0; i < array.size(); i++)
			{
				value = array[(int)i];
				FData name;
				name = value.get("Name", name);
				FData varValue;
				varValue = value.get("Value",varValue);
				sprintf(buff, "%s = %s", name.asCString(), varValue.asCString());
				PostString(buff);
			}
		}
		PostString("}");
	}
	else
	{

		sprintf(buff, "Failed, Error Code: %d", response->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::LocationFinish(CPlaytomicResponsePtr& response)
{
	PostString("Get Location:");
	char buff[256];
	if(response->ResponseSucceded())
	{
		PostString("Succeded!");
		PostString("{");
		FData geoIpInfo;
		geoIpInfo = response->ResponseData();

		FData code,name;
		LOGI("get code");
		code = geoIpInfo.get("Code",code);
		LOGI("get name");
		name = geoIpInfo.get("Name", name);

		LOGI("generate code string");
		sprintf(buff, "Code: %s", code.asCString());
		PostString(buff);
		LOGI("generate name string");
		sprintf(buff, "Name: %s", name.asCString());
		PostString(buff);
		PostString("}");
	}
	else
	{

		sprintf(buff, "Failed, Error Code: %d", response->ResponseError());
		PostString(buff);
	}
}

void CPlaytomicDemo::Freeze()
{
	gPlaytomic->Log()->Freeze();
}

void CPlaytomicDemo::Unfreeze()
{
	gPlaytomic->Log()->Unfreeze();
}
