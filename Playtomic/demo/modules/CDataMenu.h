#ifndef __DATA_MENU_H__
#define __DATA_MENU_H__

#include "CBase.h"
#include "../CDemo.h"

class CDataMenu : public CBase
{
public:
	CDataMenu(CDemo* owner) : CBase(owner){}
	virtual void ShowOptionMenu();
	virtual int	GetOption();
	virtual void ProcessOption(int optionId);
};
#endif