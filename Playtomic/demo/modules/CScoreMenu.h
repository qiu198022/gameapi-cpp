#ifndef __SCORE_MENU_H__
#define __SCORE_MENU_H__

#include "CBase.h"
#ifndef __PLAYTOMIC_LEADERBOARD_H__
#include "Playtomic/CLeaderboard.h"
#endif


class CSCoreMenu : public CBase, public Playtomic::ILeaderboardDelegate
{
public:
	CSCoreMenu(CDemo* owner) : CBase(owner){ mWaitingForAsync = false; mWriting = false;}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);

	virtual void SaveComplete(CPlaytomicResponsePtr& result);
	virtual void ListTableComple(Playtomic::SSCoreTable& result);
	virtual void SaveAndListComple(Playtomic::SSCoreTable& result);
private:
	bool mWaitingForAsync;
	bool mWriting;
};
#endif