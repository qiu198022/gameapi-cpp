#ifndef __PLAYTOMIC_DEMO_H__
#define __PLAYTOMIC_DEMO_H__

#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CPlayerLevels.h"
#include "Playtomic/CLeaderboard.h"

class CPlaytomicDemo : public Playtomic::IPlayerLevelDelegate, public Playtomic::ILeaderboardDelegate
{
public:
	CPlaytomicDemo(int gameId, std::string& gameguid, bool autoUpdate = false);

	void LogView();
	void LogPlay();
	void LogCustomMetric();
	void LogCounterMetric();
	void LogAverageMetric();


	void SaveLevel();
	void ListLevels();
	void LoadLevel();
	void RateLevel();

	void SaveScore();
	void ListScores();
	void SaveAndListScore();

	void GetGameVars();
	void GetLocation();

	//data lookup
	void GetViews();
	void GetPlays();
	void GetPlayTime();

	virtual void RateLevelComplete(CPlaytomicResponsePtr& result);
	virtual void LevelListComple(Playtomic::SLevelList& result);
	virtual void SaveLevelComple(Playtomic::SLevelList& result);
	virtual void LoadLevelComplete(Playtomic::SLevelList& result);

	virtual void SaveComplete(CPlaytomicResponsePtr& result);
	virtual void ListTableComple(Playtomic::SSCoreTable& result);
	virtual void SaveAndListComple(Playtomic::SSCoreTable& result);

	void GameVarsFinish(CPlaytomicResponsePtr& response);
	void LocationFinish(CPlaytomicResponsePtr& response);
	void ViewFinish(CPlaytomicResponsePtr& response);
	void PlayTimeFinish(CPlaytomicResponsePtr& response);
	void PlaysFinish(CPlaytomicResponsePtr& response);

private:
	Playtomic::CPlaytomic* mPlaytomicInstance;
	Playtomic::SLevelList  mLevels;
};
#endif
