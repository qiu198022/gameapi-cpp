#ifndef __PLAYTOMIC_GEO_IP_H__
#define __PLAYTOMIC_GEO_IP_H__

#include "../CurlWrap/CConnectionInterface.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{



class DllExport CGeoIP
{
public:
	CGeoIP();

	CPlaytomicResponsePtr	Load();
	void					LoadAsync(RequestDelegate targetDelegate);
};

}
#endif