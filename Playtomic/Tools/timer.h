#ifndef __TIMER_HELP_H__
#define __TIMER_HELP_H__

class CTimer;
#include <vector>
#include <list>

class CTimerDelegate
{
public:
	virtual void TimerAlert(CTimer* sender) =0;
};

class CTimer
{
public:
	void Init(CTimerDelegate* targetDelegate, int hour, char minutes, float seconds, bool autoreset = true);
	void Reset();
	void Update(float deltaSeconds);

	float Seconds() const;
	void Seconds(float val);
	char Minutes() const;
	void Minutes(char val);
	int Hour() const;
	void Hour(int val);

	void Pause();
	void UnPause();
private:
	CTimerDelegate *mDelegate;
	//required time to call the delegate
	float mRequiredSeconds;
	char mRequiredMinutes;
	int	 mRequiredHour;
	//counters
	float mSeconds;
	char  mMinutes;	
	int	  mHour;
	bool  mAutoReset;
	bool  mMessageSent;
	bool  mPaused;
};


class CTimerManager
{
public:
	CTimerManager();
	~CTimerManager();

	void AddTimer(CTimer* timer);

	//add timer to remove list, all timers in the list will be removed in 
	//the next update so its secure to call this inside a timer delegate call
	void RemoveTimer(CTimer* timer);

	void Update(float deltaTime);
private:
	std::list<CTimer*> mRemoveList;
	std::list<CTimer*> mAddList;
	std::vector<CTimer*> mTimerList;
};
#endif