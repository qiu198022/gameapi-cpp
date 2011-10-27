#ifndef __PLAYTOMIC_H__
#define __PLAYTOMIC_H__

#include <string>
#include "PlaytomicDefines.h"
#include "boost/thread.hpp"


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

	int GetGameId();
	
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

private:
	static		CPlaytomic*	mHamdle;
	int			mGameId;
	std::string	mGameGuid;
	std::string mSourceUrl;
	std::string mBaseUrl;
	
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