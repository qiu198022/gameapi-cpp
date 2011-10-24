#ifndef __PLAYTOMIC_GAME_VARS_H__
#define __PLAYTOMIC_GAME_VARS_H__


#include "../CurlWrap/CConnectionInterface.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{

class DllExport CGameVars
{
public:
	CGameVars();

	CPlaytomicResponsePtr	Load();
	void					LoadAsync(RequestDelegate targetDelegate);
private:
};

}
#endif