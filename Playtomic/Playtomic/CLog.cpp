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
#include "CLog.h"
#include "CPlaytomic.h"
#include "CLogRequest.h"
#include "../Tools/StringHelper.h"
#include "../Tools/timer.h"
#include "../Tools/File.h"

#ifdef _IOS_
#include "FilePaths.h"
#endif


namespace Playtomic
{

CLog::CLog(int gameId, std::string& gameguid)
{
	mSourceUrl = CPlaytomic::Get()->GetSourceUrl();
	mBaseUrl   = gPlaytomic->GetBaseUrl();

	char IdString[50];
	sprintf_s(IdString,49,"%d",gameId);
	mTrackUrl = kBasetrackUrlPart1;
	mTrackUrl += gameguid + kBaseTrackUrlPart2;
	mTrackUrl += IdString;
	mTrackUrl += kBaseTrackUrlPart3;
	mTrackUrl += mSourceUrl + kBaseTrackUrlPart4;

	mViews = 0;
	mPings = 0;
	mPlays = 0;
	mEnable = true;
	mFrozen = false;
    mTimer = new CTimer;
	mTimer->Init(fastdelegate::MakeDelegate(this,&CLog::TimerAlert),0,1,0, false);
	gPlaytomic->TimerManager()->AddTimer(mTimer);
    
    const char *currentFileName = CLogRequest::GetLogFileName();
#ifdef _IOS_
    char fileName[300];
    GetFilePath(fileName, 300, currentFileName);
    currentFileName = fileName;
#endif
    if( CFile::Exist(currentFileName ))
    {
        CFile backup(currentFileName );
        
        std::string fileData;
        backup.Rewind();
        while(backup.ReadLine(fileData))
        {
            SendEvent(fileData,true,true);
        }
        backup.Close();
        CFile::Remove(CLogRequest::GetLogFileName());
    }
}

CLog::~CLog()
{
	gPlaytomic->TimerManager()->RemoveTimer(mTimer);
}

void CLog::View( void )
{
	char IdString[50];
	sprintf_s(IdString,49,"v/%d", mViews + 1);    
	SendEvent(IdString,true);
}

void CLog::Play( void )
{
	char IdString[50];
	sprintf_s(IdString,49,"p/%d", mViews + 1);
	SendEvent(IdString,true);
}

void CLog::TimerAlert(CTimer* sender)
{
	if( sender != mTimer)
	{
		return;
	}
	mPings++;
	char IdString[50];
	sprintf_s(IdString,49,"t/%s%d", mPings == 1 ? "y" : "n", mPings);
	SendEvent(IdString,true);

	if ( mPings == 1)
	{
		sender->Init(fastdelegate::MakeDelegate(this,&CLog::TimerAlert), 0,0,30.0f);
	}
}

void CLog::CustomMetric( const std::string& name, const std::string& group, bool unique )
{
	if(unique)
	{
		std::list<std::string>::iterator it= mCustomMetrics.begin();
		for(; it != mCustomMetrics.end(); it++)
		{
			if( *it == name)
			{
				return;
			}
		}
		mCustomMetrics.push_back(name);
	}

	std::string event("c/");
	event += name + "/" + group;
}

void CLog::LevelCounterMetric( const std::string& name, const std::string level, bool unique )
{
	std::string cleanName = name;
	std::string cleanLevel = level;
	CleanString(cleanLevel);
	CleanString(cleanName);
	if(unique)
	{
		std::string key = cleanName + "." + cleanLevel;
		std::list<std::string>::iterator it= mLevelCounters.begin();
		for(; it != mLevelCounters.end(); it++)
		{
			if( *it == key)
			{
				return;
			}
		}
		mLevelCounters.push_back(key);
	}
	std::string event("lc/");
	event += cleanName + "/" + cleanLevel;
	SendEvent(event, false);
}

void CLog::LevelCounterMetric( const std::string& name, int levelNumber, bool unique )
{
	char buff[50];
	sprintf_s(buff, 49, "%d", levelNumber);
	LevelCounterMetric(name, buff, unique);	
}

void CLog::LevelRangedMetric( const std::string& name, const std::string& level, int trackValue,bool unique )
{
	std::string cleanName = name;
	std::string cleanLevel = level;
	CleanString(cleanLevel);
	CleanString(cleanName);
	char buff[30];
	sprintf_s(buff, 29, "%d", trackValue);
	if(unique)
	{
		
		std::string key = cleanName + "." + cleanLevel + "." + buff;
		std::list<std::string>::iterator it= mlevelRangeds.begin();
		for(; it != mlevelRangeds.end(); it++)
		{
			if( *it == key)
			{
				return;
			}
		}
		mlevelRangeds.push_back(key);
	}
	std::string event("lr/");
	event += cleanName + "/" + cleanLevel + "/" + buff;
	SendEvent(event, false);
}

void CLog::LevelRangedMetric( const std::string& name, int levelNumber, int trackValue,bool unique )
{
	char buff[50];
	sprintf_s(buff, 49, "%d", levelNumber);
	LevelRangedMetric(name, buff, trackValue, unique);	
}

void CLog::LevelAverageMetric( const std::string& name, const std::string& level, int trackValue,bool unique )
{
	std::string cleanName = name;
	std::string cleanLevel = level;
	CleanString(cleanLevel);
	CleanString(cleanName);
	char buff[30];
	sprintf_s(buff, 29, "%d", trackValue);
	if(unique)
	{
		
		std::string key = cleanName + "." + cleanLevel + "." + buff;
		std::list<std::string>::iterator it= mLevelAverages.begin();
		for(; it != mLevelAverages.end(); it++)
		{
			if( *it == key)
			{
				return;
			}
		}
		mLevelAverages.push_back(key);
	}
	std::string event("la/");
	event += cleanName + "/" + cleanLevel + "/" + buff;
	SendEvent(event, false);
}

void CLog::LevelAverageMetric( const std::string& name, int levelNumber, int trackValue,bool unique )
{
	char buff[50];
	sprintf_s(buff, 49, "%d", levelNumber);
	LevelRangedMetric(name, buff, trackValue, unique);	
}

void CLog::LinkUrl( const std::string& url, const std::string& name, const std::string& group, int unique, int total, int fail )
{
	char buff[50];
	//create the int part of the url since we cant add directly to the string
	sprintf_s(buff, 49, "/%d/%d/%d", unique, total, fail);
	std::string event;
	event = "l/" + url + "/" + name + "/" + group + buff;
	SendEvent(event, false);
}

void CLog::Heatmap( const std::string& name, const std::string& group, int x, int y )
{
	char buff[50];
	sprintf_s(buff, 49, "/%d/%d", x, y);
	std::string event;
	event = "h/" + name + "/" + group + "/" + group + buff;
	SendEvent(event, false);
}

void CLog::Funnel( void )
{
	//TODO unimplemented in ios so i don't know what this function was for
}

void CLog::PlayerLevelStart( const std::string& levelId )
{
	std::string event = "pls/" + levelId;
	SendEvent(event, false);
}

void CLog::PlayerLevelRetry( const std::string& levelId )
{
	std::string event = "plr/" + levelId;
	SendEvent(event, false);
}

void CLog::PlayerLevelWin( const std::string& levelId )
{
	std::string event = "plw/" + levelId;
	SendEvent(event, false);
}

void CLog::PlayerLevelQuit( const std::string& levelId )
{
	std::string event = "plq/" + levelId;
	SendEvent(event, false);
}

void CLog::PlayerLevelFlag( const std::string& levelId )
{
	std::string event = "plf/" + levelId;
	SendEvent(event, false);
}

void CLog::Freeze( void )
{
	if(!mFrozen)
	{
		mFrozen = true;
		mTimer->Pause();
	}
}

void CLog::Unfreeze( void )
{
	if(mFrozen)
	{
		mFrozen = false;
		mTimer->UnPause();
	}
}

void CLog::ForceSend( bool hasDate)
{
	if (mQueue.size() > 0)
	{
		//TODO please fix this! who will take care of this?
		CLogRequest* request = new CLogRequest(mTrackUrl);
        request->SetHasDate(hasDate);
		request->MassQueue(mQueue);
		mQueue.clear();
	}
	
}

void CLog::SendEvent( const std::string& event, bool commit, bool hasDate )
{
	//TODO timer required to implement this

	mQueue.push_back(event);
	if(mFrozen || commit == false)
	{
		return;
	}
	ForceSend(hasDate);
}


int CLog::GetCookie( const std::string& name )
{
	return 0;//TODO
}

void CLog::SaveCookie( void )
{

}

void CLog::IncreaseViews( void )
{
	mViews++;
}

void CLog::IncreasePlays( void )
{
	mPlays++;
}

}