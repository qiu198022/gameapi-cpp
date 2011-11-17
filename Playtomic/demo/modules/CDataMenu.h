#ifndef __DATA_MENU_H__
#define __DATA_MENU_H__

#include "CBase.h"
#include "../CDemo.h"
#include "Playtomic/CData.h"

class CDataMenu : public CBase
{
public:
	CDataMenu(CDemo* owner) : CBase(owner)
	{ 	
		mWriting = false;
		mWaitingForAsync = false;
	}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);


public: //async callbacks

	void ViewFinish(CPlaytomicResponsePtr& response);
	void CustomMetricFinish(CPlaytomicResponsePtr& response);
	void PlayTimeFinish(CPlaytomicResponsePtr& response);
	void LevelCounterFinish(CPlaytomicResponsePtr& response);
	void LevelAverageFinish(CPlaytomicResponsePtr& response);
	void LevelRangedFinish(CPlaytomicResponsePtr& response);
	void PlaysFinish(CPlaytomicResponsePtr& response);

private:
	bool mWaitingForAsync;
	bool mWriting;
	bool mWaitToWrite;
};
#endif