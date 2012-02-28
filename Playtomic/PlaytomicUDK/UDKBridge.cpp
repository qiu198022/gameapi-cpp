#include "UDKBridge.h"
#include "Playtomic/CPlaytomic.h"
#include "Playtomic/CLog.h"


extern "C"
{
Playtomic::CPlaytomic* gInstance = NULL;


DllExport void  InitPlaytomic( int gameId, wchar_t* gameguid )
{
	abort();
	if(gInstance)
	{
		delete gInstance;
	}
	char* ascii = new char[wcslen(gameguid) + 1];

	wcstombs( ascii, gameguid, wcslen(gameguid) );

	std::string gameGuid(ascii);
	gInstance = new Playtomic::CPlaytomic(gameId, gameGuid, true);
	delete ascii;
}

DllExport void StopPlaytomic()
{
	if(gInstance)
	{
		delete gInstance;
	}
	gInstance = NULL;
}

DllExport void LogView()
{
	gInstance->Log()->View();
}

DllExport void LogPlay()
{
	gInstance->Log()->Play();
}

DllExport void LogCustomMetric( wchar_t* name, wchar_t* group, bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	char* ascii2 = new char[wcslen(group) + 1];
	wcstombs( ascii, group, wcslen(group) );
	std::string groupName(ascii2);
	delete ascii;
	delete ascii2;
	gInstance->Log()->CustomMetric(metricName, groupName, unique);
	
}

DllExport void LevelCounterMetric( wchar_t* name, wchar_t* level, bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	char* ascii2 = new char[wcslen(level) + 1];
	wcstombs( ascii, level, wcslen(level) );
	std::string levelName(ascii2);
	delete ascii;
	delete ascii2;
	gInstance->Log()->LevelCounterMetric(metricName, levelName, unique);
}

DllExport void LevelCounterMetricLevelNumber( wchar_t* name, int levelNumber,bool  unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	delete ascii;
	gInstance->Log()->LevelCounterMetric(metricName, levelNumber,unique);
}

DllExport void LevelRangedMetric( wchar_t* name, wchar_t* level, int trackValue, bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	char* ascii2 = new char[wcslen(level) + 1];
	wcstombs( ascii, level, wcslen(level) );
	std::string levelName(ascii2);
	delete ascii;
	delete ascii2;
	gInstance->Log()->LevelRangedMetric(metricName, levelName, trackValue, unique);
}

DllExport void LevelRangedMetricLevelNumber( wchar_t* name, int levelNumber, int trackValue, bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	delete ascii;
	gInstance->Log()->LevelRangedMetric(metricName, levelNumber, trackValue, unique);
}

DllExport void LevelAverageMetric( wchar_t* name, wchar_t* level, int trackValue,bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	char* ascii2 = new char[wcslen(level) + 1];
	wcstombs( ascii, level, wcslen(level) );
	std::string levelName(ascii2);
	delete ascii;
	delete ascii2;
	gInstance->Log()->LevelAverageMetric(metricName, levelName, trackValue, unique);
}

DllExport void LevelAverageMetricLevelNumber( wchar_t* name,int levelNumber, int trackValue,bool unique /*= false*/ )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	delete ascii;
	gInstance->Log()->LevelAverageMetric(metricName, levelNumber, trackValue, unique);
}

DllExport void HeatMap( wchar_t* name, wchar_t* group, int x, int y )
{
	char* ascii = new char[wcslen(name) + 1];
	wcstombs( ascii, name, wcslen(name) );
	std::string metricName(ascii);
	char* ascii2 = new char[wcslen(group) + 1];
	wcstombs( ascii, group, wcslen(group) );
	std::string groupName(ascii2);
	delete ascii;
	delete ascii2;
	gInstance->Log()->Heatmap(metricName, groupName, x, y);
}

DllExport void PlayerLevelStart( wchar_t* levelId )
{
	char* ascii = new char[wcslen(levelId) + 1];
	wcstombs( ascii, levelId, wcslen(levelId) );
	std::string id(ascii);
	delete ascii;
	gInstance->Log()->PlayerLevelStart(id);
}

DllExport void PlayerLevelRetry( wchar_t* levelId )
{
	char* ascii = new char[wcslen(levelId) + 1];
	wcstombs( ascii, levelId, wcslen(levelId) );
	std::string id(ascii);
	delete ascii;
	gInstance->Log()->PlayerLevelRetry(id);
}

DllExport void PlayerLevelWin( wchar_t* levelId )
{
	char* ascii = new char[wcslen(levelId) + 1];
	wcstombs( ascii, levelId, wcslen(levelId) );
	std::string id(ascii);
	delete ascii;
	gInstance->Log()->PlayerLevelWin(id);
}

DllExport void PlayerLevelQuit( wchar_t* levelId )
{
	char* ascii = new char[wcslen(levelId) + 1];
	wcstombs( ascii, levelId, wcslen(levelId) );
	std::string id(ascii);
	delete ascii;
	gInstance->Log()->PlayerLevelQuit(id);
}

DllExport void PlayerLevelFlag( wchar_t* levelId )
{
	char* ascii = new char[wcslen(levelId) + 1];
	wcstombs( ascii, levelId, wcslen(levelId) );
	std::string id(ascii);
	delete ascii;
	gInstance->Log()->PlayerLevelFlag(id);
}

}