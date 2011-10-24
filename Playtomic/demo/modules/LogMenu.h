#ifndef __LOGS_MENU_H__
#define __LOGS_MENU_H__

#include "CBase.h"
#include "../CDemo.h"

class CLogMenu : public CBase
{
public:
	CLogMenu(CDemo* owner) : CBase(owner){}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);
};
#endif