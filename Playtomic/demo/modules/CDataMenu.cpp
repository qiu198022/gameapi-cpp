#include "CDataMenu.h"

#include "Playtomic/CPlaytomic.h"

#include "Playtomic/DataStructures.h"
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
	std::cout << "6:Load Views ASYNC" << std::endl;
	std::cout << "7:Custom Metric ASYNC" << std::endl;
	std::cout << "8:Playtime ASYNC" << std::endl;
	std::cout << "9:Level Counter ASYNC" << std::endl;
	std::cout << "10:Level average ASYNC" << std::endl;
	std::cout << "11:Level Ranged ASYNC" << std::endl;
	std::cout << "12:Load Plays ASYNC" << std::endl;
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
	if( input.compare("6") == 0)
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
	else if( input.compare("9") == 0)
	{
		return 9;
	}
	else if( input.compare("10") == 0)
	{
		return 10;
	}
	if( input.compare("11") == 0)
	{
		return 11;
	}
	else if( input.compare("12") == 0)
	{
		return 12;
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
			value = response->ResponseData().get("Value",value);
			std::cout << "views = " << value.asString() << std::endl; 
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
				value = response->ResponseData().get("Value",value);
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
		response = Playtomic::gPlaytomic->Data()->LevelCounterMetric("hi","level 1");
		if (response->ResponseSucceded())
		{
			FData value;
			value = response->ResponseData().get("Value",value);
			if(value.isString())
			{
				std::string strValue = value.asString();
				std::cout << "Counter metric = " << strValue << std::endl; 
			}

		}
		else
		{
			std::cout << "response failed error code = " << response->ResponseError() << std::endl;
		}
		break;
	case 6:
		Playtomic::gPlaytomic->Data()->ViewsAsync(fastdelegate::MakeDelegate(this,&CDataMenu::ViewFinish));
		mWaitingForAsync = true;
		break;
	case 7:
		Playtomic::gPlaytomic->Data()->CustomMetricAsync("hi",fastdelegate::MakeDelegate(this,&CDataMenu::CustomMetricFinish));
		mWaitingForAsync = true;
		break;
	case 8:
		Playtomic::gPlaytomic->Data()->PlaytimeAsync(fastdelegate::MakeDelegate(this,&CDataMenu::PlayTimeFinish));
		mWaitingForAsync = true;
		break;
	case 9:
		Playtomic::gPlaytomic->Data()->LevelCounterMetricAsync("hi","level 1",fastdelegate::MakeDelegate(this,&CDataMenu::LevelCounterFinish));
		mWaitingForAsync = true;
		break;
	case 10:
		Playtomic::gPlaytomic->Data()->LevelAverageMetricAsync("hi","level 1",fastdelegate::MakeDelegate(this,&CDataMenu::LevelAverageFinish));
		mWaitingForAsync = true;
		break;
	case 11:
		Playtomic::gPlaytomic->Data()->LevelRangedMetricAsync("hi","level 1",fastdelegate::MakeDelegate(this,&CDataMenu::LevelRangedFinish));
		mWaitingForAsync = true;
		break;
	case 12:
		Playtomic::gPlaytomic->Data()->PlaysAsync(fastdelegate::MakeDelegate(this,&CDataMenu::PlaysFinish));
		mWaitingForAsync = true;
		break;
	case 0:
		mOwner->ChangeModule(new CMainMenu(mOwner));
		return;
	default:
		break;
	}
	std::cout << std::endl;
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

void CDataMenu::ViewFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);
		std::cout << "views = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::CustomMetricFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);
		std::cout << "custom metric = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::PlaysFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);
		std::cout << "plays = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::PlayTimeFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);
		std::cout << "Playtime = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::LevelCounterFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);
		std::cout << "level counter = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::LevelAverageFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Average",value);
		if(value.isInt())
		std::cout << "level Average = " << value.asInt() << std::endl; 
		value = response->ResponseData().get("Min",value);
		if(value.isInt())
		std::cout << "level Min = " << value.asInt() << std::endl; 
		value = response->ResponseData().get("Max",value);
		if(value.isInt())
		std::cout << "level Max = " << value.asInt() << std::endl; 
		value = response->ResponseData().get("Total",value);
		if(value.isInt())
		std::cout << "level Total = " << value.asInt() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}

void CDataMenu::LevelRangedFinish( CPlaytomicResponsePtr& response )
{
	mWriting = true;
	mWaitingForAsync = false;
	while(mWaitToWrite)
	{
	}
	if (response->ResponseSucceded())
	{
		FData value;
		value = response->ResponseData().get("Value",value);

		Playtomic::CRangedMetric metricData(value);
		int regCount = metricData.mEntries.size();
		//std::cout << "level ranged = " << value.asString() << std::endl; 
	}
	else
	{
		std::cout << "response failed error code = " << response->ResponseError() << std::endl;
	}
	mWriting = false;
}
