//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 10/20/11.
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
#include "CPlaytomic.h"
#include "../CurlWrap/CConnectionInterface.h"
#include "CLog.h"
#include "../Tools/timer.h"
#include "CGeoIp.h"
#include "CGameVars.h"
#include "CLeaderboard.h"
#include "CPlayerLevels.h"
#include "CData.h"
#ifdef __ANDROID__
#include "boostFix.h"
#endif
#include "boost/timer.hpp"
#include "boost/thread.hpp"


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
            boost::this_thread::interruption_point();
			double elapsed = timer.elapsed() - currentTime;
			currentTime = timer.elapsed();
			instance->Update(elapsed);
		}
	}
CPlaytomic* CPlaytomic::mHandle = NULL;


CPlaytomic::CPlaytomic(int gameId, std::string& gameguid, bool autoUpdate)
{
	//this should never happen
	if(mHandle)
	{
		delete mHandle;
	}
	mThread	= NULL;
	mHandle = this;
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
    mConnectionType = e_disconnected;

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
	if (mThread)
	{
		mThread->interrupt();
		mThread = NULL;
	}
    CConnectionInterface::Destroy();
    delete mPlaytomicData;
    delete mPlaytomicPlayerLevels;
    delete mPlaytomicLeaderboards;
    delete mPlaytomicGameVars;
    delete mPlaytomicGeoIP;
    delete mPlaytomicLog;
    delete mTimerManager;
}

CPlaytomic* CPlaytomic::Get()
{
	return mHandle;
}

void CPlaytomic::Destroy()
{
    if(mHandle)
    {
        delete mHandle;
        mHandle = NULL;
    }
}

void CPlaytomic::Init()
{
    mConnectionType = CheckConnectionType();
    mPlaytomicLog->Init();
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

bool CPlaytomic::IsWiFiActive() const
{
    return mConnectionType == e_wifi;
}
    
}
