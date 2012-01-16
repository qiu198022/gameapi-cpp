#ifndef __PLAYTOMIC_H__
#define __PLAYTOMIC_H__

#include <string>
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
#include "PlaytomicDefines.h"
#include "CConnectionInfo.h"

namespace boost {
    class thread;
}


class CTimerManager;

namespace Playtomic
{

class CLog;
class CGameVars;
class CGeoIP;
class CLeaderboard;
class CPlayerLevels;
class CLink;
class CData;

/**
 *  Main class to access Playtomic API
 *	Configure the game data and initialize all the system that Playtomic need to 
 *	communicate with the server
 */

class DllExport CPlaytomic
{
public:
	static CPlaytomic* Get();
    static void        Destroy();
public:
	/**
	*  Playtomic constructor
	*	@param gameId get it from they Playtomic dashboard
	*	@param gameGuid	get it from they Playtomic dashboard
	*	@param autoUpdate if set to false you will need to call update by your program
	*	if you set to true it will start a new thread to auto update the timers
	*/
	CPlaytomic(int gameId, std::string& gameguid, bool autoUpdate = false);
	~CPlaytomic();
    
    void Init();

	int GameId() const;
	void GameId(int val);
	const std::string& GetGameGuid() const;
	void SetGameGuid(const std::string& source);
	const std::string& GetSourceUrl() const;
	void SetSourceUrl(const std::string& source);
	const std::string& GetBaseUrl() const;
	void SetBaseUrl(const std::string& source);

	/** 
       * Update the internal timers
       * Call this if you set autoUpdate to false
	   * @param deltaTime time since last update call
     */
	void Update(float deltaTime);

	CLog* Log() const;
	CGeoIP* GeoIP() const;
	CTimerManager* TimerManager() const;
	CGameVars* GameVars() const;
	CLeaderboard* Leaderboards() const;
	CPlayerLevels* PlayerLevels() const;
	CData* Data() const;
    bool    IsWiFiActive();
    
    
    //internal calls to update state
    void WiFiBecomeActive();
private:
	static          CPlaytomic*	mHandle;
	int             mGameId;
    CConnectionInfoBase* mConnectionType;
    CConnectionInfoBase::EConnectionType mLastConnectionState;
	std::string     mGameGuid;
	std::string     mSourceUrl;
	std::string     mBaseUrl;
	
	CTimerManager*				mTimerManager;
	CLog*				mPlaytomicLog;	
	CGameVars*			mPlaytomicGameVars;
	
	CGeoIP*			mPlaytomicGeoIP;
	CLeaderboard*		mPlaytomicLeaderboards;
	CPlayerLevels*		mPlaytomicPlayerLevels;
	CLink*				mPlaytomicLink;
	CData*				mPlaytomicData;

	//hold the auto update thread
	boost::thread*		mThread;
	
};

#define gPlaytomic	CPlaytomic::Get()

}
#endif