#ifndef __PLAYTOMIC_DATA_H__
#define __PLAYTOMIC_DATA_H__

#include "../CurlWrap/CConnectionInterface.h"
#include <string>
#include "CPlaytomicDelegate.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{

/*
*	The Data class in the API allows you to retrieve any of your game data to display in your game.

*	Each function for retrieving data takes an optional parameters object for day, month and year, with default values of 0.

*	When day, month and year are specified you will receive data for that specific day.
*	When month and year are specified you will receive data for that specific month.
*	When day, month and year are unspecified or 0 then you will receive data for all time.
*/
class DllExport CData
{
public:
	

	CPlaytomicResponsePtr	Views(int day, int month, int year);
	CPlaytomicResponsePtr	Views(int month = 0, int year= 0);

	CPlaytomicResponsePtr	Plays(int month = 0, int year = 0);
	CPlaytomicResponsePtr	Plays(int day,int month, int year);

	CPlaytomicResponsePtr	Playtime(int month=0, int year=0);
	CPlaytomicResponsePtr	Playtime(int day,int month, int year);

	CPlaytomicResponsePtr	General(const std::string& mode,int day,int month, int year);

	CPlaytomicResponsePtr	CustomMetric(const std::string& name, int day=0, int month=0, int year=0);

	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, const std::string& level,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, const std::string& level,
											int day,int month, int year);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, int levelNumber,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, int levelNumber,
											int day,int month, int year);

	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, const std::string& level,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, const std::string& level,
											int day, int month, int year);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, int levelNumber,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, int levelNumber,
											int day,int month, int year);

	CPlaytomicResponsePtr	LevelRangedMetric(const std::string& name, const std::string& level,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelRangedMetric(const std::string& name, const std::string& level,
											int day, int month, int year);
	CPlaytomicResponsePtr	LevelRangedMetric(const std::string& name, int levelNumber,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelRangedMetric(const std::string& name, int levelNumber,
											int day,int month, int year);


	CPlaytomicResponsePtr	LevelMetricType(const std::string& type, const std::string name,
										const std::string& level, int day, int month, int year);

	CPlaytomicResponsePtr	GetData(const std::string& url);

	//async calls
	void	ViewsAsync(RequestDelegate targetDelegate);
	void	ViewsAsync(int day, int month, int year, RequestDelegate targetDelegate);
	void	ViewsAsync(int month, int year, RequestDelegate targetDelegate);

	void	PlaysAsync(RequestDelegate targetDelegate);
	void	PlaysAsync(int month , int year, RequestDelegate targetDelegate);
	void	PlaysAsync(int day,int month, int year, RequestDelegate targetDelegate);

	void	PlaytimeAsync(RequestDelegate targetDelegate);
	void	PlaytimeAsync(int month, int yea, RequestDelegate targetDelegate);
	void	PlaytimeAsync(int day,int month, int year, RequestDelegate targetDelegate);

	void	GeneralAsync(const std::string& mode,int day,int month, int year, RequestDelegate targetDelegate);

	void	CustomMetricAsync(const std::string& name, RequestDelegate targetDelegate);
	void	CustomMetricAsync(const std::string& name, int day, int month, int year, RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, const std::string& level,
								   RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, const std::string& level,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, const std::string& level,
		int day,int month, int year, RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
									 RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
		int day,int month, int year, RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
									RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
		int day, int month, int year, RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
		RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
		int day,int month, int year, RequestDelegate targetDelegate);


	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
		RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
		int day, int month, int year, RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
		RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
		int month, int year, RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
		int day,int month, int year, RequestDelegate targetDelegate);


	void	LevelMetricTypeAsync(const std::string& type, const std::string name,
		const std::string& level, int day, int month, int year, RequestDelegate targetDelegate);

	void	GetDataAsync(const std::string& url, RequestDelegate targetDelegate);
	

private:
};

}

#endif