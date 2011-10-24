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
class CPlaytomicPlayerLevels;
class CLink;
class CData;


class DllExport CPlaytomic
{
public:
	static CPlaytomic* Get();
public:
	CPlaytomic(int gameId, std::string& gameguid, bool autoUpdate = false);
	~CPlaytomic();

	friend int GetGameId();
	
	int GameId() const;
	void GameId(int val);
	const std::string& GetGameGuid() const;
	void SetGameGuid(const std::string& source);
	const std::string& GetSourceUrl() const;
	void SetSourceUrl(const std::string& source);
	const std::string& GetBaseUrl() const;
	void SetBaseUrl(const std::string& source);

	void Update(float deltaTime);

	CLog* Log() const;
	CGeoIP* GeoIP() const;
	CTimerManager* TimerManager() const;
	CGameVars* GameVars() const;
	CLeaderboard* Leaderboards() const;
	CPlaytomicPlayerLevels* PlayerLevels() const;
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
	CPlaytomicPlayerLevels*		mPlaytomicPlayerLevels;
	CLink*				mPlaytomicLink;
	CData*				mPlaytomicData;

	boost::thread*		mThread;
	
};

#define gPlaytomic	CPlaytomic::Get()

}
#endif