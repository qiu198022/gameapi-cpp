#include "CLevelMenu.h"
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CPlayerLevels.h"

#include <iostream>
#include <string>
#include "MainMenu.h"


void CLevelMenu::ShowOptionMenu()
{
	std::cout << "player levels menu:" << std::endl;
	std::cout << "1:level save" << std::endl;
	std::cout << "2:level list" << std::endl;
	std::cout << "3:level load" << std::endl;
	std::cout << "4:level rate" << std::endl;

	std::cout << "5:level save ASYNC" << std::endl;
	std::cout << "6:level list ASYNC" << std::endl;
	std::cout << "7:level load ASYNC" << std::endl;
	std::cout << "8:level rate ASYNC" << std::endl;
	std::cout << "0:go back to main menu" << std::endl;
}

int CLevelMenu::GetOption()
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
	if( input.compare("4") == 0)
	{
		return 4;
	}
	else if( input.compare("5") == 0)
	{
		return 5;
	}
	else if( input.compare("6") == 0)
	{
		return 6;
	}
	else if( input.compare("7") == 0)
	{
		return 7;
	}
	else if( input.compare("8") == 0)
	{
		return 8;
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


void CLevelMenu::ProcessOption(int optionId)
{
	Playtomic::CLevel* level;
	std::string name;
	std::string playerName;
	std::string playerId;
	std::string data;
	Playtomic::SLevelListPtr list;
	CPlaytomicResponsePtr response;
	int rating;
	std::list<Playtomic::CLevel>::iterator it;
	Playtomic::CustomData customData;
	switch (optionId)
	{
	case 1:
		std::cout << "level name:" << std::endl;
		std::cin >> name;
		std::cout << "playerName" << std::endl;
		std::cin >> playerId;
		std::cout << "PlayerId" << std::endl;
		std::cin >> playerId;
		std::cout << "level data" << std::endl;
		std::cin >> data;
		level = new Playtomic::CLevel(name,playerName, playerId, data);
		list = Playtomic::gPlaytomic->PlayerLevels()->SaveLevel(*level);

		if(!list->sSucceded)
		{
			std::cout << "failed to save level, error code :" << list->sErrorCode;
		}
		break;
	case 2:
		list = Playtomic::gPlaytomic->PlayerLevels()->List("",1,10,false,false,customData);
		
		std::cout <<std::endl << std::endl << "levels" 
			<< " page: 0" << std::endl << std::endl;
		it = list->sLevelList.begin();
		for (; it != list->sLevelList.end(); it++)
		{
			std::cout << "name: " << it->GetName() << " LevelId: " 
				<< (it->GetLevelId()) << "PlayerName: " << it->GetPlayerName() <<
				"date: "<< it->GetRelativeDate() <<std::endl;
		}
		break;
	case 3:
		

		std::cout << "level id:" << std::endl;
		std::cin >> name;
		list = Playtomic::gPlaytomic->PlayerLevels()->LoadLevel(name);
		if(list->sSucceded)
		{
			if(list->sLevelList.size() == 0)
			{
				std::cout << "could not find the entry:" << std::endl;
			}
			else
			{
				it = list->sLevelList.begin();
				for (; it != list->sLevelList.end(); it++)
				{
					std::cout << "name: " << it->GetName() << " LevelId: " 
						<< (it->GetLevelId()) << "PlayerName: " << it->GetPlayerName() <<
						"date: "<< it->GetRelativeDate() <<std::endl;
				}
			}
		}
		else
		{
			std::cout << "failed to get the level!" << std::endl;
			std::cout << "error number: " << list->sErrorCode << std::endl;
		}
		break;
	case 4:
		std::cout << "level id:" << std::endl;
		std::cin >> name;
		std::cout << "rating:" << std::endl;
		std::cin >> rating;

		response = Playtomic::gPlaytomic->PlayerLevels()->RateLevel(name,rating);

		if(response->ResponseSucceded())
		{
			std::cout << "rating succeded!" << std::endl;
		}
		else
		{
			std::cout << "rating failed! Err Code:" <<
				response->ResponseError() << std::endl;
		}
		break;
	case 5:
		Playtomic::gPlaytomic->PlayerLevels()->SetDelegate(this);
		std::cout << "level name:" << std::endl;
		std::cin >> name;
		std::cout << "playerName" << std::endl;
		std::cin >> playerId;
		std::cout << "PlayerId" << std::endl;
		std::cin >> playerId;
		std::cout << "level data" << std::endl;
		std::cin >> data;
		level = new Playtomic::CLevel(name,playerName, playerId, data);
		Playtomic::gPlaytomic->PlayerLevels()->SaveLevelAsync(*level);
		mWaitingForAsync = true;
		break;
	case 6:
		Playtomic::gPlaytomic->PlayerLevels()->SetDelegate(this);
		Playtomic::gPlaytomic->PlayerLevels()->ListAsync("",1,10,false,false,customData);
		mWaitingForAsync = true;
		break;
	case 7:
		Playtomic::gPlaytomic->PlayerLevels()->SetDelegate(this);
		std::cout << "level id:" << std::endl;
		std::cin >> name;
		Playtomic::gPlaytomic->PlayerLevels()->LoadLevelAsync(name);
		mWaitingForAsync = true;
		break;
	case 8:
		Playtomic::gPlaytomic->PlayerLevels()->SetDelegate(this);
		std::cout << "level id:" << std::endl;
		std::cin >> name;
		std::cout << "rating:" << std::endl;
		std::cin >> rating;

		Playtomic::gPlaytomic->PlayerLevels()->RateLevelAsync(name,rating);
		mWaitingForAsync = true;
		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}

	std::cout << std::endl;
	if(mWaitingForAsync)
	{
		mWaitToWrite = true;
		while(mWaitingForAsync)
		{
			for (int i = 0; i <1000000; i++)
			{
				i =i;
			}
			std::cout << ". ";
		}
		mWaitToWrite = false;
		std::cout <<std::endl << std::endl;
		while(mWriting)
		{
		}
		std::cout << std::endl;
	}
}

void CLevelMenu::RateLevelComplete( CPlaytomicResponsePtr& result )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if(result->ResponseSucceded())
	{
		std::cout << "rating succeded!" << std::endl;
	}
	else
	{
		std::cout << "rating failed! Err Code:" <<
			result->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CLevelMenu::LevelListComple( Playtomic::SLevelList& result )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	std::cout <<std::endl << std::endl << "levels" 
		<< " page: 0" << std::endl << std::endl;
	std::list<Playtomic::CLevel>::iterator it = result.sLevelList.begin();
	for (; it != result.sLevelList.end(); it++)
	{
		std::cout << "name: " << it->GetName() << " LevelId: " 
			<< (it->GetLevelId()) << "PlayerName: " << it->GetPlayerName() <<
			"date: "<< it->GetRelativeDate() <<std::endl;
	}
	mWriting = false;
}

void CLevelMenu::SaveLevelComple( Playtomic::SLevelList& result )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if(!result.sSucceded)
	{
		std::cout << "failed to save level, error code :" << result.sErrorCode;
	}
	mWriting = false;
}

void CLevelMenu::LoadLevelComplete( Playtomic::SLevelList& result )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if(result.sSucceded)
	{
		if(result.sLevelList.size() == 0)
		{
			std::cout << "could not find the entry:" << std::endl;
		}
		else
		{
			std::list<Playtomic::CLevel>::iterator it = result.sLevelList.begin();
			for (; it != result.sLevelList.end(); it++)
			{
				std::cout << "name: " << it->GetName() << " LevelId: " 
					<< (it->GetLevelId()) << "PlayerName: " << it->GetPlayerName() <<
					"date: "<< it->GetRelativeDate() <<std::endl;
			}
		}
	}
	else
	{
		std::cout << "failed to get the level!" << std::endl;
		std::cout << "error number: " << result.sErrorCode << std::endl;
	}
	mWriting = false;
}

