#ifndef __UDK_BRIDGE_H__
#define __UDK_BRIDGE_H__

#include "Playtomic/PlaytomicDefines.h"
extern "C"
{

DllExport void InitPlaytomic(int gameId, wchar_t* gameguid);
DllExport void StopPlaytomic();


DllExport void LogView();
DllExport void LogPlay();
DllExport void LogCustomMetric(wchar_t* name, wchar_t* group, bool unique = false);
DllExport void LevelCounterMetric(wchar_t* name, wchar_t* level, bool unique = false);
DllExport void LevelCounterMetricLevelNumber(wchar_t* name, int levelNumber, bool unique = false);
DllExport void LevelRangedMetric(wchar_t* name, wchar_t* level, int trackValue, bool unique = false);
DllExport void LevelRangedMetricLevelNumber(wchar_t* name, int levelNumber, int trackValue, bool unique = false);
DllExport void LevelAverageMetric(wchar_t* name, wchar_t* level, int trackValue,bool unique = false);
DllExport void LevelAverageMetricLevelNumber(wchar_t* name, int levelNumber, int trackValue,bool unique = false);

DllExport void HeatMap(wchar_t* name, wchar_t* group, int x, int y);

DllExport void PlayerLevelStart(wchar_t* levelId);
DllExport void PlayerLevelRetry(wchar_t* levelId);
DllExport void PlayerLevelWin(wchar_t* levelId);
DllExport void PlayerLevelQuit(wchar_t* levelId);
DllExport void PlayerLevelFlag(wchar_t* levelId);
}
#endif