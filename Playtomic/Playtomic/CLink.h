#ifndef __PLAYTOMIC_LINK_H__
#define __PLAYTOMIC_LINK_H__

#include "PlaytomicDefines.h"
#include <map>

namespace Playtomic
{

class DllExport CLink
{
public:
	void Track(const std::string& url, const std::string& name, const std::string& group);
private:
	std::map<std::string, int>  mClick;
};

}
#endif