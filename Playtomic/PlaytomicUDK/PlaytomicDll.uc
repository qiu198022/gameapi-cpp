class PlaytomicDLL extends PlayerController
	DLLBind(PlaytomicUDK);
	
dllimport final function InitPlaytomic(int gameId, string gameguid);
dllimport final function StopPlaytomic();
dllimport final function LogView();
dllimport final function LogPlay();

dllimport final function LogCustomMetric(string metricName, string group, int  unique);
dllimport final function LevelCounterMetric(string metricName, string level, int unique);
dllimport final function LevelCounterMetricLevelNumber(string metricName, int levelId, int unique);
dllimport final function LevelRangedMetric(string metricName, string level, int trackValue, int unique);
dllimport final function LevelRangedMetricLevelNumber(string metricName, int levelId, int trackValue, int unique);
dllimport final function LevelAverageMetric(string metricName, string level, int trackValue, int unique);
dllimport final function LevelAverageMetricLevelNumber(string metricName, int levelId, int trackValue,int unique);

dllimport final function HeatMap(string metricName, string group, int x, int y);

dllimport final function PlayerLevelStart(string levelId);
dllimport final function PlayerLevelretry(string levelId);
dllimport final function PlayerLevelWin(string levelId);
dllimport final function PlayerLevelQuit(string levelId);
dllimport final function PlayerLevelFlag(string levelId);
