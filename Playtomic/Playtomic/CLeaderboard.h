#ifndef __PLAYTOMIC_LEADERBOARD_H__
#define __PLAYTOMIC_LEADERBOARD_H__

#include "../CurlWrap/CPlaytomicResponse.h"
#include "CScore.h"
#include <list>


namespace Playtomic
{



struct DllExport SSCoreTable 
{
	std::list<CScore>	sScoreList;
	int					sErrorCode;
	int					sScoreCount;
	bool				sSucceded;
};
typedef boost::shared_ptr<SSCoreTable> SSCoreTablePtr;

/**
* LeaderboardDelegate Delegate interface
*	if you use the Asynchronous methods you will need to inherit from this interface
*	to get the information or the commit status
*	you will also need to set as the target delegate to CLeaderboard
*/

class DllExport ILeaderboardDelegate
{
public:
	virtual void SaveComplete(CPlaytomicResponsePtr& result)=0;
	virtual void ListTableComple(SSCoreTable& result)=0;
	virtual void SaveAndListComple(SSCoreTable& result)=0;
};

/**
*	The Leaderboards API gives you very flexible high and low score leaderboards.
*	They can be created in your game dynamically or set up in the edit leaderboards page
*/
class DllExport CLeaderboard 
{
public:
	CLeaderboard();

	//if you use any asynchronous call you need to set the delegate
	void SetDelegate(ILeaderboardDelegate* targetDelegate);
	
	//synchronous calls
	/**
	*	submit the score to the selected table
	*	@param tableName		The score table to submit to, alphanumeric
	*	@param score			An instance of CScore which contains score information
	*	@param highest			Leaderboard tables can be created dynamically from within
								your game so you specify the mode.
	*	@param allowDuplicate	If you don't allow duplicates new, worse scores will not be saved by a player.

	*	@return					Playtomic response with the error code if something went wrong
	*/
	CPlaytomicResponsePtr SaveTable(const std::string& tableName,
								 const CScore& score,
								 bool highest,
								 bool allowDuplicates);

	/**
	*	returns an array of CScore objects to your function where you can display
	*	the data in your leaderboard.
	*	@param tableName	Your leaderboard table name
	*	@param highest		if the table does not exist it will be created with this mode.
	*	@param mode			The list mode can return scores from: "last7days" or "last30days" or
							"alltime" or "today" or "newest" which gives you a stream of unranked scores
	*	@param page			The page you want 
	*	@param perPage		The number of scores to return
	*	@param customFilter Filter by scores with specific CustomData
	*	
	*	@return		SScoreTable struct with the list of scores or the error code if it fails
	*/
	SSCoreTablePtr	ListTable(const std::string& tableName,
								  bool highest,
								  const std::string& mode,
								  int	page,
								  int	perPage,
								  const CustomData& customFilter);

	/**
	*	You can now submit scores and at the same time return the leaderboard page that that score is on.
	*
	*	*You don't specify a page, you specify the PerPage (default 20) and it will
	*	automatically decide which page to return based on the submitted score's rank. 
	*	If you submit the 1187th best score at 30 per page then it will show you page 39, scores #1170 - #1200.
	*	*Ranks are returned, so you are not viewing the top N scores you are viewing the top N scores from rank X onwards.

	*	@param tableName		Your leaderboard table name
	*	@param score			An instance of CScore which contains score information
	*	@param highest			Leaderboard tables can be created dynamically from within
	*							your game so you specify the mode.
	*	@param allowDuplicate	If you don't allow duplicates new, worse scores will not be saved by a player.
	*	@param mode			The list mode can return scores from: "last7days" or "last30days" or
	*						"alltime" or "today" or "newest" which gives you a stream of unranked scores
	*	@param perPage		The number of scores to return
	*	@param customFilter Filter by scores with specific CustomData
	*
	*	@return		SScoreTable struct with the list of scores or the error code if it fails
	*/
	SSCoreTablePtr	SaveAndListTable(const std::string& tableName,
									const CScore& score,
									bool highest,
									bool allowDuplicates,
									const std::string& mode,
									int	perPage,
									const CustomData& customFilter);

	//asynchronous calls
	// take care to set the delegate to null if you need to delete it after doing a request
	/**
	*	submit the score to the selected table
	*	@param tableName		The score table to submit to, alphanumeric
	*	@param score			An instance of CScore which contains score information
	*	@param highest			Leaderboard tables can be created dynamically from within
								your game so you specify the mode.
	*	@param allowDuplicate	If you don't allow duplicates new, worse scores will not be saved by a player.
	*/
	void	SaveTableAsync(const std::string& tableName,
		const CScore& score,
		bool highest,
		bool allowDuplicates);

	/**
	*	returns an array of CScore objects to your function where you can display
	*	the data in your leaderboard.
	*	@param tableName	Your leaderboard table name
	*	@param highest		if the table does not exist it will be created with this mode.
	*	@param mode			The list mode can return scores from: "last7days" or "last30days" or
							"alltime" or "today" or "newest" which gives you a stream of unranked scores
	*	@param page			The page you want 
	*	@param perPage		The number of scores to return
	*	@param customFilter Filter by scores with specific CustomData
	*/
	void	ListTableAsync(const std::string& tableName,
		bool highest,
		const std::string& mode,
		int	page,
		int	perPage,
		const CustomData&	customFilter);

	/**
	*	You can now submit scores and at the same time return the leaderboard page that that score is on.
	*
	*	*You don't specify a page, you specify the PerPage (default 20) and it will
	*	automatically decide which page to return based on the submitted score's rank. 
	*	If you submit the 1187th best score at 30 per page then it will show you page 39, scores #1170 - #1200.
	*	*Ranks are returned, so you are not viewing the top N scores you are viewing the top N scores from rank X onwards.

	*	@param tableName		Your leaderboard table name
	*	@param score			An instance of CScore which contains score information
	*	@param highest			Leaderboard tables can be created dynamically from within
	*							your game so you specify the mode.
	*	@param allowDuplicate	If you don't allow duplicates new, worse scores will not be saved by a player.
	*	@param mode			The list mode can return scores from: "last7days" or "last30days" or
	*						"alltime" or "today" or "newest" which gives you a stream of unranked scores
	*	@param perPage		The number of scores to return
	*	@param customFilter Filter by scores with specific CustomData
	*/
	void	SaveAndListTableAsync(const std::string& tableName,
		const CScore& score,
		bool highest,
		bool allowDuplicates,
		const std::string& mode,
		int	perPage,
		const CustomData&	customFilter);

	//internal delegates for the connection interface 
	// the process the request response and calls the current delegate
	void SaveComple(CPlaytomicResponsePtr& response);
	void ListComple(CPlaytomicResponsePtr& response);
	void SaveAndListComple(CPlaytomicResponsePtr& response);
private:
	ILeaderboardDelegate* mDelegate;
};

}
#endif