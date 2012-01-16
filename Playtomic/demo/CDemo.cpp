#include "CDemo.h"
#include "modules/MainMenu.h"
#include "Playtomic/CLog.h"
#include "Playtomic/CExceptionHandler.h"
#include <iostream>

void processCrash(int signal)
{
	//you can try to save any data you want to save here
}
void CDemo::Init()
{
	std::string key("9f3f3b43cb234025");
	
	mInstance = new Playtomic::CPlaytomic(4603, key, true);
	Playtomic::CExceptionHandler::SetHandlers();
	Playtomic::CExceptionHandler::SetSignalCallbackk(&processCrash);
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
