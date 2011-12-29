#include "CDemo.h"
#include "modules/MainMenu.h"
#include "Playtomic/CLog.h"
#include <iostream>

void CDemo::Init()
{
	std::string key("9f3f3b43cb234025");
	
	mInstance = new Playtomic::CPlaytomic(4603, key, true);
    mInstance->Init();
    mInstance->Log()->View();
	mCurrentModule = new CMainMenu(this);
}

void CDemo::Start()
{
	while (mCurrentModule)
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

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}
