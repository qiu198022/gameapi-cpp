#include "timer.h"
#include <cstring>

void CTimer::Init(TimerDelegate delegate, int hour, char minutes, float seconds, bool autoreset)
{
	mAutoReset = autoreset;
	mRequiredSeconds = seconds;
	mRequiredMinutes = minutes;
	mRequiredHour = hour;
	mDelegate = delegate;
	mPaused	= false;
	Reset();
}

void CTimer::Reset()
{
	Seconds(0.0f);
	Minutes(0);
	Hour(0);
	mMessageSent = false;
}

void CTimer::Update(float deltaSeconds)
{
	if(mPaused)
	{
		return;
	}
	mSeconds += deltaSeconds;

	if(mSeconds >= 60.0f)
	{
		int minutes = static_cast<int>(mSeconds/60.f);
		mMinutes += minutes;
		mSeconds = mSeconds - (minutes*60.f);
		if (mMinutes >= 60)
		{
			int extraHour = mMinutes/60;
			mHour += extraHour;
			mMinutes -= (extraHour * 60);
		}
	}
	if(!mMessageSent)
	{
		if( mHour >= mRequiredHour &&
			mMinutes >= mRequiredMinutes&&
			mSeconds >= mRequiredSeconds)
		{
			mDelegate(this);
			mMessageSent = true;
			if (mAutoReset)
			{
				Reset();
			}
		}
	}
}

float CTimer::Seconds() const
{ 
	return mSeconds;
}

void CTimer::Seconds(float val)
{
	mSeconds = val;
}

char CTimer::Minutes() const { 
	return mMinutes; 
}

void CTimer::Minutes(char val) 
{
	mMinutes = val;
}

int CTimer::Hour() const {
	return mHour; 
}

void CTimer::Hour(int val) {
	mHour = val; 
}

void CTimer::Pause()
{
	mPaused = true;
}

void CTimer::UnPause()
{
	mPaused = false;
}

CTimerManager::CTimerManager()
{

}

void CTimerManager::AddTimer(CTimer* timer)
{
	mAddList.push_back(timer);
}

void CTimerManager::RemoveTimer(CTimer* timer)
{
	mRemoveList.push_back(timer);
}

void CTimerManager::Update(float deltaTime)
{
	std::list<CTimer*>::iterator it = mAddList.begin();
	for (; it != mAddList.end(); it++)
	{
		mTimerList.push_back(*it);
	}
	mAddList.clear();
	for(size_t i = 0 ; i < mTimerList.size(); i++)
	{
		mTimerList[i]->Update(deltaTime);
	}

	//its is safe to remove timers now
	it = mRemoveList.begin();
	for (; it != mRemoveList.end(); it++)
	{
		for(size_t i = 0 ; i < mTimerList.size(); i++)
		{
			if(mTimerList[i] == *it)
			{
				mTimerList.erase(mTimerList.begin()+i);
				break;
			}
		}
	}
	mRemoveList.clear();
}
