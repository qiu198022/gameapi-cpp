#include "LogMenu.h"
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CLog.h"
#include <iostream>
#include <string>
#include "MainMenu.h"


void CLogMenu::ShowOptionMenu()
{
	std::cout << "Log Menu:" << std::endl;
	std::cout << "1:Log Play" << std::endl;
	std::cout << "2:Log Custom Metric" << std::endl;
	std::cout << "3:Log Level Counter" << std::endl;
	std::cout << "4:Log Average Metric" << std::endl;
	std::cout << "5:Log Ranged Metric" << std::endl;
	std::cout << "0:go back to main menu" << std::endl;
}

int CLogMenu::GetOption()
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


void CLogMenu::ProcessOption(int optionId)
{
	CPlaytomicResponsePtr response;
	std::string name;
	std::string group;
	std::string unique;
	int intValue;
	switch (optionId)
	{
	case 1:
		Playtomic::gPlaytomic->Log()->Play();
		break;
	case 2:
		std::cout << "metric name:" << std::endl;
		std::cin >> name;
		std::cout << "group" << std::endl;
		std::cin >> group;
		std::cout << "unique (y/n)" << std::endl;
		std::cin >> unique;
		Playtomic::gPlaytomic->Log()->CustomMetric(name,group, unique.compare("y")==0);
		break;
	case 3:
		std::cout << "level name:" << std::endl;
		std::cin >> name;
		std::cout << "unique (y/n)" << std::endl;
		std::cin >> unique;

		group = "counter";
		Playtomic::gPlaytomic->Log()->LevelCounterMetric(group,name,unique.compare("y")==0);

		break;
	case 4:
		std::cout << "level name:" << std::endl;
		std::cin >> name;
		std::cout << "unique (y/n)" << std::endl;
		std::cin >> unique;
		std::cout << "value" << std::endl;
		std::cin >> intValue;
		group = "average";
		Playtomic::gPlaytomic->Log()->LevelAverageMetric(group,name, intValue,unique.compare("y")==0);
		break;
	case 5:
		std::cout << "level name:" << std::endl;
		std::cin >> name;
		std::cout << "unique (y/n)" << std::endl;
		std::cin >> unique;
		std::cout << "value" << std::endl;
		std::cin >> intValue;
		group = "ranged";
		Playtomic::gPlaytomic->Log()->LevelRangedMetric(group,name, intValue,unique.compare("y")==0);
		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}
}