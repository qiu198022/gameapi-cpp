#ifndef __PLAYTOMIC_LOG_H__
#define __PLAYTOMIC_LOH_H__

#include <string>
#include <list>
#include <queue>
#include "../Tools/timer.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{


class DllExport CLog : public CTimerDelegate
{
public:
	CLog(int gameId, std::string& gameguid);
	~CLog();

	void View(void);
	void Play(void);
	
	virtual void TimerAlert(CTimer* sender);

	void CustomMetric(const std::string& name, const std::string& group, bool unique);
	
	void LevelCounterMetric(const std::string& name, const std::string level, bool unique);
	void LevelCounterMetric(const std::string& name, int levelNumber, bool unique);
	void LevelRangedMetric(const std::string& name, const std::string& level,
							int trackValue,bool unique);
	void LevelRangedMetric(const std::string& name, int levelNumber,
							int trackValue,bool unique);
	void LevelAverageMetric(const std::string& name, const std::string& level,
							int trackValue,bool unique);
	void LevelAverageMetric(const std::string& name, int levelNumber,
							int trackValue,bool unique);

	void LinkUrl(const std::string& url, const std::string& name, const std::string& group,
				 int unique, int total, int fail);

	void Heatmap(const std::string& name, const std::string& group, int x, int y);

	void Funnel(void);

	void PlayerLevelStart(const std::string& levelId);
	void PlayerLevelRetry(const std::string& levelId);
	void PlayerLevelWin(const std::string& levelId);
	void PlayerLevelQuit(const std::string& levelId);
	void PlayerLevelFlag(const std::string& levelId);

	void Freeze(void);
	void Unfreeze(void);
	void ForceSend(void);

	void SendEvent(const std::string& event, bool commit);

	int GetCookie(const std::string& name);
	void SaveCookie(void);

	void IncreaseViews(void);
	void IncreasePlays(void);
private:
	std::string		mTrackUrl;
	std::string		mSourceUrl;
	std::string		mBaseUrl;
	bool			mEnable;
	
	CTimer						mTimer;
	int							mPings;
	int							mViews;
	int							mPlays;
	bool						mFrozen;
	std::list<std::string>		mQueue;
	std::list<std::string>		mCustomMetrics;
	std::list<std::string>		mLevelCounters;
	std::list<std::string>		mLevelAverages;
	std::list<std::string>		mlevelRangeds;
	//TODO last event ocurrrance when timers gets implemented;
};

}
#endif