#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "CBase.h"
#include "../CDemo.h"

class CMainMenu : public CBase
{
public:
	CMainMenu(CDemo* owner) : CBase(owner){}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);
};
#endif