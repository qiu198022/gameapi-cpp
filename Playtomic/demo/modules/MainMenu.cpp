#include "MainMenu.h"
#include "CScoreMenu.h"
#include "LogMenu.h"
#include <iostream>
#include <string>
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CGameVars.h"
#include "CLevelMenu.h"
#include "CDataMenu.h"



void CMainMenu::ShowOptionMenu()
{
	std::cout << "Main Menu:" << std::endl;
	std::cout << "1:Test Leaderboards" << std::endl;
	std::cout << "2:Test Logs" << std::endl;
	std::cout << "3:Test GameVars" << std::endl;
	std::cout << "4:Get Data" << std::endl;
	std::cout << "5:Test Player Levels" << std::endl;
	std::cout << "0:Quit" << std::endl;
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
	else if( input.compare("5") == 0)
	{
		return 5;
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
			
			FData array;
			array = response->ResponseData();
			if(array.size() == 0)
			{
				std::cout << " empty game vars" << std::endl;
				break;
			}
			else
			{
				FData value;
				for (size_t i = 0; i < array.size(); i++)
				{
					value = array[i];

					FData name;
					name = value.get("Name", name);
					FData varValue;
					varValue = value.get("Value",varValue);

					std::cout << name.asString() << "=" << varValue.asString() << std::endl; 
				}
			}
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 4:
		mOwner->ChangeModule(new CDataMenu(mOwner));
		break;
	case 5:
		mOwner->ChangeModule(new CLevelMenu(mOwner));
		break;
	case 0:
		mOwner->ChangeModule(NULL);
		return;
	default:
		break;
	}
}