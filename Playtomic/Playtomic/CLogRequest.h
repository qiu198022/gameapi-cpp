#ifndef __PLAYTOMIC_LOG_REQUEST_H__
#define __PLAYTOMIC_LOG_REQUEST_H__

#include <string>
#include <list>
#include "../CurlWrap/CPlaytomicResponse.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{

class DllExport CLogRequest
{
public:
	CLogRequest(const std::string& url);

	void Send	(void);
	void QueueEvent( const std::string& event);
	void MassQueue(std::list<std::string>& queue);

	void RequestComplete(CPlaytomicResponsePtr& response);
private:
	std::string mData;
	std::string mTrackUrl;
	bool		mMustReleaseOnFinished;
};

}
#endif