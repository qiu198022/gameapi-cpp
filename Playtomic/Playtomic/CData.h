//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 10/20/11.
//  Copyright 2011 Playtomic LLC. All rights reserved.
//
//  Documentation is available at:
//  http://playtomic.com/api/cpp
//
// PLEASE NOTE:
// You may modify this SDK if you wish but be kind to our servers.  Be
// careful about modifying the analytics stuff as it may give you
// borked reports.
//
// If you make any awesome improvements feel free to let us know!
//
// -------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY PLAYTOMIC, LLC "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef __PLAYTOMIC_DATA_H__
#define __PLAYTOMIC_DATA_H__

#include "PlaytomicDefines.h"
#include "CConnectionInterface.h"
#include <string>
#include "CPlaytomicDelegate.h"


namespace Playtomic
{

/*
*	The Data class in the API allows you to retrieve any of your game data to display in your game.

*	Each function for retrieving data takes an optional parameters object for day, month and year, with default values of 0.

*	When day, month and year are specified you will receive data for that specific day.
*	When month and year are specified you will receive data for that specific month.
*	When day, month and year are unspecified or 0 then you will receive data for all time.

*	When the request succeeds the returned data is available via:
*	CPlaytomicResponsePtr response;
*	FData value;
*	value = response->ResponseData().get("key",value);
*/

/*	Asynchronous and synchronous methods
*	For some methods there are two versions: one synchronous and one asynchronous.
*	We recomend you to use the asynchronous one because it is not going to freeze
*	your game while the call is executed. Calling the synchronous version is more 
*	easy to code and is there for games which are not resource-intensive.

*	The Asynchronous methods take a delegate as parameter, you should generate 
*	one using fastdelegate::MakeDelegate(classPtr,&classType::method);
*	the delegate method should take a CPlaytomicResponsePtr& as parameter.
*
*	e.g.
*	
*	CAnyClass::delegate(CPlaytomicResponsePtr& response);
*	ViewsAsync(fastdelegate::MakeDelegate(this,&CAnyClass::delegate));
*
*	be careful to don't destroy the given instance before the delegate get called
*/
class DllExport CData
{
public:
	
	//synchronous calls
	CPlaytomicResponsePtr	Views(int day, int month, int year);
	CPlaytomicResponsePtr	Views(int month = 0, int year= 0);

	CPlaytomicResponsePtr	Plays(int month = 0, int year = 0);
	CPlaytomicResponsePtr	Plays(int day,int month, int year);

	CPlaytomicResponsePtr	Playtime(int month=0, int year=0);
	CPlaytomicResponsePtr	Playtime(int day,int month, int year);

	CPlaytomicResponsePtr	General(const std::string& mode,int day,int month, int year);

	/*
	*	The CustomMetric function returns data about a custom metric to your 
	*	function, which receives the same parameters as views/plays/play time above.
	*	@param	name	the custom metric name
	*	@return	CPlaytomicResponse	the only key for the data is "Value"
	*	e.x 
	*	response = Playtomic::gPlaytomic->Data()->CustomMetric("hi");
	*	FData value;
	*	value = response->ResponseData().get("Value",value);
	*/
	CPlaytomicResponsePtr	CustomMetric(const std::string& name, int day=0, int month=0, int year=0);

	/*
	*	Retrieving level metrics is the same as retrieving custom metrics with
	*	an additional property for the level name or number.
	*	@param	name	metric name
	*	@param	level	level name
	*	return	valid key for responseData: "Value"
	*/
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, const std::string& level,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, const std::string& level,
											int day,int month, int year);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, int levelNumber,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelCounterMetric(const std::string& name, int levelNumber,
											int day,int month, int year);

	/*
	*	@param	name	metric name
	*	@param	level	level name
	*	return	valid key for responseData: "Min", "Max", "Average" and "Total"
	*/
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, const std::string& level,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, const std::string& level,
											int day, int month, int year);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, int levelNumber,
											int month=0, int year=0);
	CPlaytomicResponsePtr	LevelAverageMetric(const std::string& name, int levelNumber,
											int day,int month, int year);

	/*
	*	@param	name	metric name
	*	@param	level	level name
	*	return	valid key for responseData: "Values" is an array of objects 
	*	with the keys: "Tracking" and "Occurances"
	*/
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

	//asynchronous calls
	/*
	*	The Asynchronous methods take a delegate as parameter, you should generate 
	*	one using fastdelegate::MakeDelegate(classPtr,&classType::method);
	*	the delegate method should take a CPlaytomicResponsePtr& as parameter.
	*
	*	e.g.
	*	
	*	CAnyClass::delegate(CPlaytomicResponsePtr& response);
	*	ViewsAsync(fastdelegate::MakeDelegate(this,&CAnyClass::delegate));
	*
	*	be careful to don't destroy the given instance before the delegate get called
	*
	*	the data returned by the synchronous version is the same that the data 
	*	send to the delegates so you can process it in the same way
	*/
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
										int month, int year,
										RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, const std::string& level,
									int day,int month, int year,
									RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
									 RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
									int month, int year,
									RequestDelegate targetDelegate);

	void	LevelCounterMetricAsync(const std::string& name, int levelNumber,
										int day,int month, int year,
										RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
									RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
										int month, int year,
										RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, const std::string& level,
										int day, int month, int year,
										RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
									RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
										int month, int year,
										RequestDelegate targetDelegate);

	void	LevelAverageMetricAsync(const std::string& name, int levelNumber,
									int day,int month, int year,
									RequestDelegate targetDelegate);


	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
									RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
									int month, int year, RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, const std::string& level,
									int day, int month, int year,
									RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
										RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
									int month, int year,
									RequestDelegate targetDelegate);

	void	LevelRangedMetricAsync(const std::string& name, int levelNumber,
									int day,int month, int year,
									RequestDelegate targetDelegate);


	void	LevelMetricTypeAsync(const std::string& type, const std::string name,
									const std::string& level, int day, int month,
									int year, RequestDelegate targetDelegate);

	void	GetDataAsync(const std::string& url, RequestDelegate targetDelegate);
	

private:
};

}

#endif