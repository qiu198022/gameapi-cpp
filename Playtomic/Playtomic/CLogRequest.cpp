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
#include "CLogRequest.h"
#include "../CurlWrap/CConnectionInterface.h"
#include "../Tools/File.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../Tools/StringHelper.h"
#include "boost/thread/locks.hpp"
#include "boost/thread.hpp"

#if defined(_IOS_) || defined(__ANDROID__)
#include "FilePaths.h"
#endif

#ifdef __ANDROID__
#include <android/log.h>
#define  LOG_TAG    "CLOGREQUEST"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

const char* sLogBackupFileName = "pFailedLogs.txt";
const size_t kMaxFileSize = 1024*50;
static boost::mutex m;

namespace Playtomic
{

void CLogRequest::SetLogFileName(const char *newName)
{
    sLogBackupFileName = newName;
}

const char* CLogRequest::GetLogFileName()
{
    return sLogBackupFileName;
}
    
CLogRequest::CLogRequest(const std::string& url)
{
	mTrackUrl = url;
	mMustReleaseOnFinished = true;
    mSendTries = 0;
    mHasDate = false;
}

void CLogRequest::Send( void )
{
	std::string fullUrl(mTrackUrl);
	fullUrl += mData;

    mSendTries++;
	gConnectionInterface->PerformAsyncRequest(fullUrl.c_str(), fastdelegate::MakeDelegate(this, &CLogRequest::RequestComplete));

}

void CLogRequest::QueueEvent( const std::string& event )
{
	if(mData.size() == 0)
	{
		mData = event;
	}
	else
	{
		mData += "~" + event;
	}
}

void CLogRequest::MassQueue(std::list<std::string>& queue )
{
	while (!queue.empty())
	{
		std::string event = queue.front();
		queue.pop_front();
		if(mData.size() == 0)
		{
			mData = event;
		}
		else
		{
			mData += "~" + event;
			if ( mData.length() > 300)
			{
				Send();
				CLogRequest newRequest(mTrackUrl);
				newRequest.MassQueue(queue);
				return;
			}
		}
	}
	Send();
}

void CLogRequest::SetHasDate(bool state)
{
    mHasDate = state;
}

void CLogRequest::RequestComplete( CPlaytomicResponsePtr& response )
{
    
    if(!response->ResponseSucceded())
    {
        if(mSendTries < e_triesLimit)
        {
            Send();
            return;
        }
        else
        {  
            const char *currentFileName = GetLogFileName();
#if defined(_IOS_)
            char fileName[300];

            GetFilePath(fileName, 300, currentFileName);
            currentFileName = fileName;
#endif
            boost::mutex::scoped_lock lock(m);
            CFile backupData(currentFileName);
            if(backupData.GetSize() < kMaxFileSize)
            {
                if(!mHasDate)
                {
                    boost::posix_time::ptime now = boost::posix_time::second_clock::universal_time();
                    std::string strDate("&date=");
                    std::string date = boost::posix_time::to_simple_string(now);
                    CleanString(date);
                    strDate += date;
                    mData += strDate;
                }            
                backupData.WriteLine(mData);
                
            }
            backupData.Close();
            lock.unlock();           

        }
            
        
    }
	if(mMustReleaseOnFinished)
	{
		//TODO please change this to an object delete list
		delete this;
	}
}

}
