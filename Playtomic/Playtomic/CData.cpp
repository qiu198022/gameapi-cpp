#include "CData.h"
#include "CPlaytomic.h"

#include "../Tools/StringHelper.h"

namespace Playtomic
{

CPlaytomicResponsePtr CData::Views( int day, int month, int year )
{
	return General("views",day,month,year);
}

CPlaytomicResponsePtr CData::Views( int month /*= 0*/, int year/*= 0*/ )
{
	return General("views",0,month,year);
}

CPlaytomicResponsePtr CData::Plays( int month /*= 0*/, int year /*= 0*/ )
{
	return General("plays",0,month,year);
}

CPlaytomicResponsePtr CData::Plays( int day,int month, int year )
{
	return General("plays",day,month,year);
}

CPlaytomicResponsePtr CData::Playtime( int month/*=0*/, int year/*=0*/ )
{
	return General("playtime",0,month,year);
}

CPlaytomicResponsePtr CData::Playtime( int day,int month, int year )
{
	return General("playtime",day,month,year);
}

CPlaytomicResponsePtr CData::General( const std::string& mode,int day,int month, int year )
{
	char date[60];
	sprintf_s(date,59,"%d", gPlaytomic->GameId());
	std::string url(kDataGeneralUrl1);
	url += gPlaytomic->GetGameGuid() + kDataGeneralUrl2 + mode + kDataGeneralUrl3 + date + kDataGeneralUrl4;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataGeneralUrl5, month, kDataGeneralUrl6, year);
	url += date; url += kDataGeneralUrl6;

	return GetData(url);
}

CPlaytomicResponsePtr CData::CustomMetric( const std::string& name, int day/*=0*/,
	int month/*=0*/, int year/*=0*/ )
{
	std::string cleanName = name;
	CleanString(cleanName);
	char date[60];
	sprintf_s(date,59,"%d",  gPlaytomic->GameId());
	std::string url(kDataCustomUrl1);
	url += gPlaytomic->GetGameGuid() + kDataCustomUrl2 +date + kDataCustomUrl3 + cleanName + kDataCustomUrl4;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataCustomUrl5, month, kDataCustomUrl6, year);
	url += date; url += kDataCustomUrl6;

	return GetData(url);
}

CPlaytomicResponsePtr CData::LevelCounterMetric( const std::string& name,
	const std::string& level, int month/*=0*/, int year/*=0*/ )
{
	return LevelMetricType("counter",name, level, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelCounterMetric( const std::string& name,
	const std::string& level, int day,int month, int year )
{
	return LevelMetricType("counter",name, level, day, month, year);
}

CPlaytomicResponsePtr CData::LevelCounterMetric( const std::string& name,
	int levelNumber, int month/*=0*/, int year/*=0*/ )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("counter",name, buff, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelCounterMetric( const std::string& name,
	int levelNumber, int day,int month, int year )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("counter",name, buff, day, month, year);
}

CPlaytomicResponsePtr CData::LevelAverageMetric( const std::string& name, 
	const std::string& level, int month/*=0*/, int year/*=0*/ )
{
	return LevelMetricType("average",name, level, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelAverageMetric( const std::string& name, 
	const std::string& level, int day, int month, int year )
{
	return LevelMetricType("average",name, level, day, month, year);
}

CPlaytomicResponsePtr CData::LevelAverageMetric( const std::string& name,
	int levelNumber, int month/*=0*/, int year/*=0*/ )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("average",name, buff, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelAverageMetric( const std::string& name,
	int levelNumber, int day,int month, int year )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("counter",name, buff, day, month, year);
}

CPlaytomicResponsePtr CData::LevelRangedMetric( const std::string& name,
	const std::string& level, int month/*=0*/, int year/*=0*/ )
{
	return LevelMetricType("ranged",name, level, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelRangedMetric( const std::string& name,
	const std::string& level, int day, int month, int year )
{
	return LevelMetricType("ranged",name, level, day, month, year);
}

CPlaytomicResponsePtr CData::LevelRangedMetric( const std::string& name, 
	int levelNumber, int month/*=0*/, int year/*=0*/ )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("ranged",name, buff, 0, month, year);
}

CPlaytomicResponsePtr CData::LevelRangedMetric( const std::string& name,
	int levelNumber, int day,int month, int year )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	return LevelMetricType("ranged",name, buff, day, month, year);
}

CPlaytomicResponsePtr CData::LevelMetricType( const std::string& type, 
	const std::string name, const std::string& level, int day, int month, int year )
{
	std::string cleanName(name);
	std::string cleanLevel(level);
	CleanString(cleanName);
	CleanString(cleanLevel);
	char date[60];
	sprintf_s(date,59,"%d",  gPlaytomic->GameId());
	std::string url(kDataLevelUrl1);
	url += gPlaytomic->GetGameGuid() + kDataLevelUrl2 + cleanName + kDataLevelUrl3;
	url += date;
	url += kDataLevelUrl4 + cleanLevel ;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataLevelUrl7, month, kDataLevelUrl8, year);
	url += kDataLevelUrl6;url += date;

	return GetData(url);
}

CPlaytomicResponsePtr CData::GetData( const std::string& url )
{
	return gConnectionInterface->PerformSyncRequest(url.c_str());
}


//async version
void CData::ViewsAsync( int day, int month, int year, RequestDelegate targetDelegate )
{
	GeneralAsync("views",day,month,year, targetDelegate);
}

void CData::ViewsAsync( int month , int year, RequestDelegate targetDelegate )
{
	GeneralAsync("views",0,month,year, targetDelegate);
}

void CData::ViewsAsync(RequestDelegate targetDelegate)
{
	GeneralAsync("views",0,0,0,targetDelegate);
}

void CData::PlaysAsync( int month, int year , RequestDelegate targetDelegate )
{
	GeneralAsync("plays",0,month,year, targetDelegate);
}

void CData::PlaysAsync( int day,int month, int year , RequestDelegate targetDelegate)
{
	GeneralAsync("plays",day,month,year, targetDelegate);
}

void CData::PlaysAsync( RequestDelegate targetDelegate )
{
	GeneralAsync("plays",0,0,0, targetDelegate);
}

void CData::PlaytimeAsync(  RequestDelegate targetDelegate )
{
	GeneralAsync("playtime",0,0,0, targetDelegate);
}

void CData::PlaytimeAsync( int month, int year, RequestDelegate targetDelegate )
{
	GeneralAsync("playtime",0,month,year, targetDelegate);
}

void CData::PlaytimeAsync( int day,int month, int year, RequestDelegate targetDelegate )
{
	GeneralAsync("playtime",day,month,year, targetDelegate);
}

void CData::GeneralAsync( const std::string& mode,int day,int month, int year,
	RequestDelegate targetDelegate )
{
	char date[60];
	sprintf_s(date,59,"%d",  gPlaytomic->GameId());
	std::string url(kDataGeneralUrl1);
	url += gPlaytomic->GetGameGuid() + kDataGeneralUrl2 + mode + kDataGeneralUrl3 + date + kDataGeneralUrl4;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataGeneralUrl5, month, kDataGeneralUrl6, year);
	url += date; url += kDataGeneralUrl6;

	GetDataAsync(url, targetDelegate);
}

void CData::CustomMetricAsync( const std::string& name, int day, int month, int year,
	RequestDelegate targetDelegate )
{
	std::string cleanName = name;
	CleanString(cleanName);
	char date[60];
	sprintf_s(date,59,"%d",  gPlaytomic->GameId());
	std::string url(kDataCustomUrl1);
	url += gPlaytomic->GetGameGuid() + kDataCustomUrl2 +date + kDataCustomUrl3 + cleanName + kDataCustomUrl4;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataCustomUrl5, month, kDataCustomUrl6, year);
	url += date; url += kDataCustomUrl6;

	GetDataAsync(url, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, const std::string& level,
	RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("counter",name, level, 0, 0, 0, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, const std::string& level,
	int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("counter",name, level, 0, month, year, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, const std::string& level,
	int day,int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("counter",name, level, day, month, year, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, int levelNumber,
										RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("counter",name, buff, 0, 0, 0, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, int levelNumber,
	int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("counter",name, buff, 0, month, year, targetDelegate);
}

void CData::LevelCounterMetricAsync( const std::string& name, int levelNumber,
	int day,int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("counter",name, buff, day, month, year, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, const std::string& level,
									RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("average",name, level, 0, 0, 0, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, const std::string& level,
	int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("average",name, level, 0, month, year, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, const std::string& level,
	int day, int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("average",name, level, day, month, year, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, int levelNumber, 
									RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("average",name, buff, 0, 0, 0, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, int levelNumber,
	int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("average",name, buff, 0, month, year, targetDelegate);
}

void CData::LevelAverageMetricAsync( const std::string& name, int levelNumber,
	int day,int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("counter",name, buff, day, month, year, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, const std::string& level,
	RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("ranged",name, level, 0, 0, 0, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, const std::string& level,
	int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("ranged",name, level, 0, month, year, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, const std::string& level,
	int day, int month, int year, RequestDelegate targetDelegate )
{
	LevelMetricTypeAsync("ranged",name, level, day, month, year, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, int levelNumber,
	RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("ranged",name, buff, 0, 0, 0, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, int levelNumber,
	int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("ranged",name, buff, 0, month, year, targetDelegate);
}

void CData::LevelRangedMetricAsync( const std::string& name, int levelNumber, 
	int day,int month, int year, RequestDelegate targetDelegate )
{
	char buff[4];
	sprintf_s(buff,3,"%d", levelNumber);
	LevelMetricTypeAsync("ranged",name, buff, day, month, year, targetDelegate);
}

void CData::LevelMetricTypeAsync( const std::string& type, const std::string name,
	const std::string& level, int day, int month, int year, RequestDelegate targetDelegate )
{
	std::string cleanName(name);
	std::string cleanLevel(level);
	CleanString(cleanName);
	CleanString(cleanLevel);
	char date[60];
	sprintf_s(date,59,"%d",  gPlaytomic->GameId());
	std::string url(kDataLevelUrl1);
	url += gPlaytomic->GetGameGuid() + kDataLevelUrl2 + cleanName + kDataLevelUrl3;
	url += date;
	url += kDataLevelUrl4 + cleanLevel ;
	sprintf_s(date,59,"%d%s%d%s%d", day, kDataLevelUrl7, month, kDataLevelUrl8, year);
	url += kDataLevelUrl6;url += date;

	GetDataAsync(url, targetDelegate);
}

void CData::GetDataAsync( const std::string& url, RequestDelegate targetDelegate )
{
	gConnectionInterface->PerformAsyncRequest(url.c_str(), targetDelegate);
}


}