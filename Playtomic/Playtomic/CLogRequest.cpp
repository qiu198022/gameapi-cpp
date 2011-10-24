#include "CLogRequest.h"
#include "../CurlWrap/CConnectionInterface.h"

namespace Playtomic
{

CLogRequest::CLogRequest(const std::string& url)
{
	mTrackUrl = url;
	mMustReleaseOnFinished = false;
}

void CLogRequest::Send( void )
{
	std::string fullUrl(mTrackUrl);
	fullUrl += mData;

	//TODO make it async when implented
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
	if(mMustReleaseOnFinished)
	{
		//TODO please change this to a object delete list
		delete this;
	}
}

}
