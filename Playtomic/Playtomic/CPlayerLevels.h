#ifndef __PLAYTOMIC_PLAYER_LEVELS_H__
#define __PLAYTOMIC_PLAYER_LEVELS_H__

#include "PlaytomicDefines.h"
#include "../CurlWrap/CPlaytomicResponse.h"
#include <string>
#include "CLevel.h"
#include "CPlaytomicDelegate.h"
#include <list>

namespace Playtomic {

struct SLevelList 
{
	std::list<CLevel>  sLevelList;
	int							sErrorCode;
	int							sLevelCount;
	bool						sSucceded;
};

class DllExport CPlayerLevelDelegate
{
public:
	virtual void RateLevelComplete(CPlaytomicResponsePtr& result)=0;
	virtual void LevelListComple(SLevelList& result)=0;
	virtual void SaveLevelComple(SLevelList& result)=0;
	virtual void LoadLevelComplete(SLevelList& result)=0;
};


class  DllExport CPlaytomicPlayerLevels
{
public:
	CPlaytomicPlayerLevels();
	void SetDelegate(CPlayerLevelDelegate* targetDelegate);
	// synchronous calls
	SLevelList				LoadLevel(const std::string& levelId);
	CPlaytomicResponsePtr	RateLevelId(const std::string& levelId, int rating);
	SLevelList				List(const std::string& mode, int page, int perPage,
								bool includeDAta, bool includeThumbs,
								const CustomData& customFilter);
	SLevelList				SaveLevel(CLevel& level);

	// asynchronous calls
	//
	void	LoadLevelAsync(const std::string& levelId);
	void	RateLevelIdAsync(const std::string& levelId, int rating);
	void	ListAsync(const std::string& mode, int page, int perPage,
					bool includeDAta, bool includeThumbs,
					const CustomData& customFilter);
	void	SaveLevelAsync(CLevel& level);

	void	LoadLevelComplete(CPlaytomicResponsePtr& response);
	void	RateLevelIdComplete(CPlaytomicResponsePtr& response);
	void	ListAsyncComplete(CPlaytomicResponsePtr& response);
	void	SaveLevelComplete(CPlaytomicResponsePtr& response);
private:
	void					AddLevel(const FData& level, const std::string& levelId,
									std::list<CLevel>& levelList);
	CPlayerLevelDelegate*	mDelegate;
	std::string				mLevelId;
};

}
#endif