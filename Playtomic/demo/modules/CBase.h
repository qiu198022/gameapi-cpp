#ifndef __CBASE_MODULE_H__
#define __CBASE_MODULE_H__

class CDemo;

class CBase
{
public:
	CBase(CDemo* owner) :mOwner(owner){}

	void Update()
	{
		ShowOptionMenu();
		ProcessOption(GetOption());
	}

	virtual void ShowOptionMenu()=0;
	virtual int	GetOption()=0;
	virtual void ProcessOption(int optionId)=0;
protected:
	CDemo*	mOwner;
};
#endif