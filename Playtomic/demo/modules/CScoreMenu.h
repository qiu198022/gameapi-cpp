#ifndef __SCORE_MENU_H__
#define __SCORE_MENU_H__

#include "CBase.h"

class CSCoreMenu : public CBase
{
public:
	CSCoreMenu(CDemo* owner) : CBase(owner){}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);
};
#endif