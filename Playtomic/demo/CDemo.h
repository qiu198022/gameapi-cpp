#ifndef __DEMO_MAIN__H__
#define __DEMO_MAIN__H__

#include "Playtomic/CPlaytomic.h"
#include "modules/CBase.h"

class CDemo
{
public:
	void Init();

	void Start();

	void Update();

	void ChangeModule(CBase* nextModule);
private:
	Playtomic::CPlaytomic* mInstance;
	CBase*				   mCurrentModule;
	
};
#endif