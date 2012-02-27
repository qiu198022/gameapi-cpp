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
#ifndef __PLAYTOMIC_LOG_H__
#define __PLAYTOMIC_LOH_H__

#include <string>
#include <list>
#include <queue>
#include "PlaytomicDefines.h"

class CTimer;

namespace Playtomic
{

/** 
* Basic Analytics logs
* Events are sent in batches each time the play timer updates (every 30 seconds after the first minute).
*/
class DllExport CLog
{
public:
	friend class CTimer;
	CLog(int gameId, std::string& gameguid);
	~CLog();
    
    //check if there is any log from previus sesion that need to be send
    void Init();
	/**
	* A view occurs whenever somebody views your game. This should go somewhere
	* very early in your code, like before the pre-loader.
	*/
	void View(void);
	/**
	*	A play occurs when someone begins a game by clicking your play button or 
	*	whatever action is relevant to your game. A person can get between 0 and 
	*	many plays during a single view.
	*/
	void Play(void);
	
	/**
	*	Custom metrics allow you to track how many people do something in your game.
	*	For instance, how many play on easy, medium or hard, or how many play 
	*	in English vs. Spanish, or how many view the tutorial or skip it. Anything
	*	you think can help you improve your game can be defined in custom metrics.
	*	@param Name		the custom metric name
	*	@param group	this is optional if you don't want to group your metric just 
	*					send and empty string
	*	@param unique	set it to true if you want the custom metric to be unique-per-view
	*/
	void CustomMetric(const std::string& name, const std::string& group, bool unique = false);
	
	/**
	*	These metrics track how many times something occurs in your levels, for instance deaths and restarts.
	*	@param	name	the metric name (death,restarts, etc.)
	*	@param	level	the level where the event occurs
	*	@param	unique	set it to true if you want the custom metric to be unique-per-view
	*/
	void LevelCounterMetric(const std::string& name, const std::string level, bool unique= false);
	void LevelCounterMetric(const std::string& name, int levelNumber, bool unique= false);

	/**
	*	These metrics track the average of something in your levels, for instance 
	*	the average time to finish a level or the average number of retries. 
	*	It also tracks the minimum and maximums.
	*	@param	name	the metric name (death,restarts, etc.)
	*	@param	level	the level where the event occurs
	*	@param	trackValue	the value that you want to track
	*	@param	unique	set it to true if you want the custom metric to be unique-per-view
	*/
	void LevelRangedMetric(const std::string& name, const std::string& level,
							int trackValue,bool unique= false);
	void LevelRangedMetric(const std::string& name, int levelNumber,
							int trackValue,bool unique = false);

	/**
	*	These metrics track metrics with values, for instance in a golf game you
	*	might track how many shots it takes to complete each level, or you might
	*	track the % of coins collected on each level.
	*	@param	name	the metric name (death,restarts, etc.)
	*	@param	level	the level where the event occurs
	*	@param	trackValue	the value that you want to track
	*	@param	unique	set it to true if you want the custom metric to be unique-per-view
	*/
	void LevelAverageMetric(const std::string& name, const std::string& level,
							int trackValue,bool unique = false);
	void LevelAverageMetric(const std::string& name, int levelNumber,
							int trackValue,bool unique= false);

	void LinkUrl(const std::string& url, const std::string& name, const std::string& group,
				 int unique, int total, int fail);

	/**
	*	Heatmaps allow you to map activity (clicks, deaths, first deaths, or
	*	anything else you want) against an image you upload in the dashboard.
	*	In the dashboard you upload a background image for the heatmap,
	*	and then it is shared by any metrics using it.
	*	@param	name		metric name
	*	@param	group		metric group
	*	@param	x			screenCoordX
	*	@param	y			screenCoordY
	*/
	void Heatmap(const std::string& name, const std::string& group, int x, int y);


	void PlayerLevelStart(const std::string& levelId);
	void PlayerLevelRetry(const std::string& levelId);
	void PlayerLevelWin(const std::string& levelId);
	void PlayerLevelQuit(const std::string& levelId);
	void PlayerLevelFlag(const std::string& levelId);

	void Freeze(void);
	void Unfreeze(void);

	/**
	*	send the complete queue of event to the Playtomic server
	*/
	void ForceSend(bool hasDate = false);

	/**
	*	add a new log event to the event queue
	*	@param	event	the new event to queue
	*	@param	commit	set to true if you want to force to send the whole queue
	*/
	void SendEvent(const std::string& event, bool commit, bool hasDate = false);


	void IncreaseViews(void);
	void IncreasePlays(void);
    
    void SetCurrentBackupFile(const std::string& filePath);
private:
	/** 
	*	this is a call back to the timer 
	*/
	virtual void TimerAlert(CTimer* sender);
	std::string		mTrackUrl;
	std::string		mSourceUrl;
	std::string		mBaseUrl;
    std::string     mLogBackupFile;
	bool			mEnable;
	
	CTimer*						mTimer;
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