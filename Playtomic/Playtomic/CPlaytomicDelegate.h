#ifndef __PLAYTOMIC_DELEGATE_H__
#define __PLAYTOMIC_DELEGATE_H__

namespace Playtomic
{

class CDelegate
{
public:

	virtual void RequestLoadGeoIpFinished(CPlaytomicResponsePtr& response){}
	virtual void RequestLoadGameVarsFinished(CPlaytomicResponsePtr& response){}
};

}
#endif