#ifndef __LEVEL_MENU_H__
#define __LEVEL_MENU_H__

#include "CBase.h"
#ifndef __PLAYTOMIC_PLAYER_LEVELS_H__
#include "Playtomic/CPlayerLevels.h"
#endif


class CLevelMenu : public CBase, public Playtomic::IPlayerLevelDelegate
{
public:
	CLevelMenu(CDemo* owner) : CBase(owner)
	{
		mWaitingForAsync = false; 
		mWriting = false;
		mWaitToWrite = false;
	}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);

	virtual void RateLevelComplete(CPlaytomicResponsePtr& result);
	virtual void LevelListComple(Playtomic::SLevelList& result);
	virtual void SaveLevelComple(Playtomic::SLevelList& result);
	virtual void LoadLevelComplete(Playtomic::SLevelList& result);
private:
	volatile bool mWaitingForAsync;
	volatile bool mWriting;
	volatile bool mWaitToWrite;
};
#endif