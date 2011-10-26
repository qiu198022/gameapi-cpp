#include "CDataMenu.h"

#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CData.h"
#include <iostream>
#include <string>
#include "MainMenu.h"


void CDataMenu::ShowOptionMenu()
{
	std::cout << "Data Menu:" << std::endl;
	std::cout << "1:Load Views" << std::endl;
	std::cout << "2:Get Custom Data" << std::endl;
	std::cout << "3:Load Plays" << std::endl;
	std::cout << "4:Load Playtime" << std::endl;
	std::cout << "5:Load Counters" << std::endl;
	std::cout << "0:go back to main menu" << std::endl;
}

int CDataMenu::GetOption()
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


void CDataMenu::ProcessOption(int optionId)
{
	CPlaytomicResponsePtr response;
	std::string name;
	std::string group;
	std::string unique;
	switch (optionId)
	{
	case 1:
		response = Playtomic::gPlaytomic->Data()->Views();
		if (response->ResponseSucceded())
		{
			FData value;
			value = response->ResponseData().get("Views",value);
			std::cout << "views = " << value.asInt() << std::endl; 
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 2:
		response = Playtomic::gPlaytomic->Data()->CustomMetric("hi");
		if (response->ResponseSucceded())
		{
			FData value;
			if(response->ResponseData().size() > 0)
			{
				value = response->ResponseData().get("Views",value);
				if(value.isString())
				{
					std::cout << "hi metric = " << value.asString() << std::endl; 
				}
				
			}			
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 3:
		response = Playtomic::gPlaytomic->Data()->Plays();
		if (response->ResponseSucceded())
		{
			FData value;
			value = response->ResponseData().get("Plays",value);
			std::cout << "plays = " << value.asInt() << std::endl; 
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}

		break;
	case 4:
		response = Playtomic::gPlaytomic->Data()->Playtime();
		if (response->ResponseSucceded())
		{
			FData value;
			value = response->ResponseData().get("Value",value);
			if(value.isString())
			{
				std::string strValue = value.asString();
				std::cout << "Playtime = " << strValue << std::endl; 
			}
			
		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 5:

		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}
}