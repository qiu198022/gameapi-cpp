#include "CScoreMenu.h"
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CLeaderboard.h"
#include <iostream>
#include <string>
#include "MainMenu.h"


void CSCoreMenu::ShowOptionMenu()
{
	std::cout << "score menu:" << std::endl;
	std::cout << "1:save new score" << std::endl;
	std::cout << "2:save new  score and display current tables" << std::endl;
	std::cout << "3:display current scores" << std::endl;
	std::cout << "0:go back to main menu" << std::endl;
}

int CSCoreMenu::GetOption()
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


void CSCoreMenu::ProcessOption(int optionId)
{
	std::string name;
	int score;
	Playtomic::CustomData filter;
	Playtomic::CScore scoreData;
	Playtomic::SSCoreTable table;
	CPlaytomicResponsePtr response;
	switch (optionId)
	{
	case 1:
		std::cout << "player name:" << std::endl;
		std::cin >> name;
		std::cout << "player score" << std::endl;
		std::cin >> score;

		scoreData.SetDefaultValues(name, score);

		response = Playtomic::gPlaytomic->Leaderboards()->SaveTable("Demo Table", scoreData,true,true);
		if(response->ResponseSucceded())
		{
			std::cout << "new score entry success!" << std::endl;
		}
		else
		{
			std::cout << "failed to save the score!" << std::endl;
			std::cout << "error number: " << response->ResponseError() << std::endl;
		}
		break;
	case 2:
		std::cout << "player name:" << std::endl;
		std::cin >> name;
		std::cout << "player score" << std::endl;
		std::cin >> score;

		scoreData.SetDefaultValues(name, score);

		table = Playtomic::gPlaytomic->Leaderboards()->SaveAndListTable
			("Demo Table", scoreData,true,true,"last7days",10 , filter);
		if (table.sSucceded)
		{
			std::cout <<std::endl << std::endl << "scoretable" 
				<< " page: 0" << std::endl << std::endl;
			std::list<Playtomic::CScore>::iterator it = table.sScoreList.begin();
			for (; it != table.sScoreList.end(); it++)
			{
				std::cout << "name: " << it->GetName() << " Score: " 
					<< (int)(it->GetPoints()) << "Rank: " << it->GetRank() <<
					"date: "<< it->GetRelativeDate() <<std::endl;
			}

			if(table.sScoreCount > 10)
			{

				for (int i = 1; i <= table.sScoreCount / 10; i++)
				{
					std::cout << std::endl << std::endl << "scoretable" 
						<< " page: "<< i << std::endl << std::endl;
					table = Playtomic::gPlaytomic->Leaderboards()->ListTable("Test Table2", false, "last7days",i + 1  , 10, filter);
					it = table.sScoreList.begin();
					for (; it != table.sScoreList.end(); it++)
					{
						std::cout << "name: " << it->GetName() << " Score: " 
							<< (int)(it->GetPoints()) << "Rank: " << it->GetRank() <<
							"date: "<< it->GetRelativeDate() <<std::endl;
					}
				}
			}
		}
		else
		{
			std::cout << "failed to save the score!" << std::endl;
			std::cout << "error number: " << table.sErrorCode << std::endl;
		}
		break;
	case 3:
		table = Playtomic::gPlaytomic->Leaderboards()->ListTable
			("Demo Table",true,"last7days", 1,10 , filter);
		if (table.sSucceded)
		{
			std::cout <<std::endl << std::endl << "scoretable" 
				<< " page: 0" << std::endl << std::endl;
			std::list<Playtomic::CScore>::iterator it = table.sScoreList.begin();
			for (; it != table.sScoreList.end(); it++)
			{
				std::cout << "name: " << it->GetName() << " Score: " 
					<< (int)(it->GetPoints()) << "Rank: " << it->GetRank() <<
					"date: "<< it->GetRelativeDate() <<std::endl;
			}

			if(table.sScoreCount > 10)
			{

				for (int i = 1; i <= table.sScoreCount / 10; i++)
				{
					std::cout << std::endl << std::endl << "scoretable" 
						<< " page: "<< i << std::endl << std::endl;
					table = Playtomic::gPlaytomic->Leaderboards()->ListTable("Test Table2", true, "last7days",i + 1  , 10, filter);
					it = table.sScoreList.begin();
					for (; it != table.sScoreList.end(); it++)
					{
						std::cout << "name: " << it->GetName() << " Score: " 
							<< (int)(it->GetPoints()) << "Rank: " << it->GetRank() <<
							"date: "<< it->GetRelativeDate() <<std::endl;
					}
				}
			}
		}
		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}
}
