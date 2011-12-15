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

namespace Playtomic
{

CLogRequest::CLogRequest(const std::string& url)
{
	mTrackUrl = url;
	mMustReleaseOnFinished = true;
    mSendTries = 0;
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
            CFile backupData(sLogBackupFileName);
            backupData.Write(mData);
        }
            
        
    }
	if(mMustReleaseOnFinished)
	{
		//TODO please change this to an object delete list
		delete this;
	}
}

}
