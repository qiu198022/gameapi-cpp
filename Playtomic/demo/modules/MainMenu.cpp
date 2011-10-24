#include "MainMenu.h"
#include "CScoreMenu.h"
#include "LogMenu.h"
#include <iostream>
#include <string>
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CGameVars.h"
#include "CDataMenu.h"



void CMainMenu::ShowOptionMenu()
{
	std::cout << "Main Menu:" << std::endl;
	std::cout << "1:Test Leaderboards" << std::endl;
	std::cout << "2:Test Logs" << std::endl;
	std::cout << "3:Test GameVars" << std::endl;
	std::cout << "4:Get Data" << std::endl;
}

int CMainMenu::GetOption()
{
	std::string input;
	std::cin >> input;

	if( input.compare("1") == 0)
	{
		return 1;
	}
	else if( input.compare("2") == 0)
	{
		return 2;
	}
	else if( input.compare("3") == 0)
	{
		return 3;
	}
	else if( input.compare("4") == 0)
	{
		return 4;
	}
	else if( input.compare("0") == 0)
	{
		return 0;
	}
	else 
	{
		std::cout << "invalid option try again" << std::endl;
		ShowOptionMenu();
		return GetOption();		
	}
}


void CMainMenu::ProcessOption(int optionId)
{
	CPlaytomicResponsePtr response;
	switch (optionId)
	{
	case 1:
		mOwner->ChangeModule(new CSCoreMenu(mOwner));
		return;
	case 2:
		mOwner->ChangeModule(new CLogMenu(mOwner));
		return;
	case 3:
		response = Playtomic::gPlaytomic->GameVars()->Load();
		
		if (response->ResponseSucceded())
		{
			
			FData value;
			if(value.size() == 0)
			{
				std::cout << " empty game vars" << std::endl;
				break;
			}
			value = response->ResponseData().get("GameVar1",value);
			std::cout << "GameVar1 == " << value.asString() << std::endl; 
			value = response->ResponseData().get("GameVar2",value);
			std::cout << "GameVar2 == " << value.asString() << std::endl; 
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 4:
		mOwner->ChangeModule(new CDataMenu(mOwner));
		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}
}