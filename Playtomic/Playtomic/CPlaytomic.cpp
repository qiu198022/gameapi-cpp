#include "CPlaytomic.h"
#include "../CurlWrap/CConnectionInterface.h"
#include "CLog.h"
#include "../Tools/timer.h"
#include "CGeoIp.h"
#include "CGameVars.h"
#include "CLeaderboard.h"
#include "CPlayerLevels.h"
#include "CData.h"
#include "boost/timer.hpp"


namespace Playtomic
{

	struct SAutoUpdate
	{
		CPlaytomic* instance;
		void operator()();
	};

	void SAutoUpdate::operator()()
	{
		boost::timer timer;
		timer.restart();
		double currentTime = timer.elapsed();
		while (1)
		{
			double elapsed = timer.elapsed() - currentTime;
			currentTime = timer.elapsed();
			instance->Update(elapsed);
		}
	}
CPlaytomic* CPlaytomic::mHamdle = NULL;


CPlaytomic::CPlaytomic(int gameId, std::string& gameguid, bool autoUpdate)
{
	//this should never happen
	if(mHamdle)
	{
		delete mHamdle;
	}
	mThread	= NULL;
	mHamdle = this;
	mGameId = gameId;
	mGameGuid = gameguid;

	gConnectionInterface->Init();

	mSourceUrl = "http://cpptest.com";
	mBaseUrl = "cpp.com";

	mTimerManager = new CTimerManager();

	mPlaytomicLog = new CLog(gameId, gameguid);
	mPlaytomicGeoIP = new CGeoIP;
	mPlaytomicGameVars = new CGameVars;
	mPlaytomicLeaderboards = new CLeaderboard;
	mPlaytomicPlayerLevels = new CPlayerLevels;
	mPlaytomicData		= new CData;

	if(autoUpdate)
	{
		//start update here
		SAutoUpdate autoUpdateThread;
		autoUpdateThread.instance = this;
		mThread = new boost::thread(autoUpdateThread);
	}

}

CPlaytomic::~CPlaytomic()
{
	delete mPlaytomicLog;
	if (mThread)
	{
		mThread->interrupt();
		mThread = NULL;
	}
}

CPlaytomic* CPlaytomic::Get()
{
	return mHamdle;
}

int CPlaytomic::GameId() const
{
	return mGameId;
}

void CPlaytomic::GameId(int val)
{ 
	mGameId = val; 
}

const std::string& CPlaytomic::GetGameGuid() const
{
	return mGameGuid;
}

void CPlaytomic::SetGameGuid(const std::string& source)
{
	mGameGuid = source;
}

const std::string& CPlaytomic::GetSourceUrl() const
{
	return mSourceUrl;
}

void CPlaytomic::SetSourceUrl(const std::string& source)
{
	mSourceUrl = source;
}

const std::string& CPlaytomic::GetBaseUrl() const
{
	return mBaseUrl;
}

void CPlaytomic::SetBaseUrl(const std::string& source)
{
	mBaseUrl = source;
}

void CPlaytomic::Update(float deltaTime)
{
	mTimerManager->Update(deltaTime);
}

CTimerManager* CPlaytomic::TimerManager() const
{ 
	return mTimerManager;
}

CLog* CPlaytomic::Log() const
{ 
	return mPlaytomicLog;
}

CGeoIP* CPlaytomic::GeoIP() const
{ 
	return mPlaytomicGeoIP;
}

CGameVars* CPlaytomic::GameVars() const
{ 
	return mPlaytomicGameVars;
}


CLeaderboard* CPlaytomic::Leaderboards() const
{
	return mPlaytomicLeaderboards;
}


CPlayerLevels* CPlaytomic::PlayerLevels() const
{ 
	return mPlaytomicPlayerLevels;
}

CData* CPlaytomic::Data() const
{ 
	return mPlaytomicData;
}

}
