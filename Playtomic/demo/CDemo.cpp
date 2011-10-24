#include "CDemo.h"
#include "modules/MainMenu.h"

void CDemo::Init()
{
	mInstance = new Playtomic::CPlaytomic(4603, std::string("9f3f3b43cb234025"),true);
	mCurrentModule = new CMainMenu(this);
}

void CDemo::Start()
{
	while (1)
	{
		Update();
	}
}

void CDemo::Update()
{
	mCurrentModule->Update();
}

void CDemo::ChangeModule(CBase* nextModule)
{
	delete mCurrentModule;
	mCurrentModule = nextModule;
}