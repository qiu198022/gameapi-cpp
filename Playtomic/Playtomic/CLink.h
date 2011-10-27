#ifndef __PLAYTOMIC_LINK_H__
#define __PLAYTOMIC_LINK_H__

#include "PlaytomicDefines.h"
#include <map>

/**
*	Link tracking allows you to keep track of how many people open URLs in your game,
*	providing you information on unique and total clicks that can be fully audited
*	to allow you to identify good sources of traffic.
*/
namespace Playtomic
{

class DllExport CLink
{
public:

	/**
	*	log the link
	*	example : gPlaytomic->Link("http://armorgames.com/", "armorgames", "sponsor");
	*	@param url : 
	*	@param name
	*	@param group
	*/
	void Track(const std::string& url, const std::string& name, const std::string& group);
private:
	std::map<std::string, int>  mClick;
};

}
#endif