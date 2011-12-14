//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 10/20/11.
//  Copyright 2011 Playtomic LLC. All rights reserved.
//
//  Documentation is available at:
//  http://playtomic.com/api/cpp
//
// PLEASE NOTE:
// You may modify this SDK if you wish but be kind to our servers.  Be
// careful about modifying the analytics stuff as it may give you
// borked reports.
//
// If you make any awesome improvements feel free to let us know!
//
// -------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY PLAYTOMIC, LLC "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __TIMER_HELP_H__
#define __TIMER_HELP_H__

class CTimer;
#include <vector>
#include <list>
#include <cstring>
#include "FastDelegate.h"

typedef fastdelegate::FastDelegate1<CTimer*> TimerDelegate;

class CTimerDelegate
{
public:
	virtual void TimerAlert(CTimer* sender) =0;
};

class CTimer
{
public:
	void Init(TimerDelegate targetDelegate, int hour, char minutes, float seconds, bool autoreset = true);
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
    TimerDelegate mDelegate;
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