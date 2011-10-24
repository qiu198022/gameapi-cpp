#ifndef __PLAYTOMIC_LEADERBOARD_H__
#define __PLAYTOMIC_LEADERBOARD_H__

#include "../CurlWrap/CPlaytomicResponse.h"
#include "CScore.h"
#include <list>


namespace Playtomic
{



struct SSCoreTable 
{
	std::list<CScore>  sScoreList;
	int							sErrorCode;
	int							sScoreCount;
	bool						sSucceded;
};

class DllExport CLeaderboardDelegate
{
public:
	virtual void SaveComplete(CPlaytomicResponsePtr& result)=0;
	virtual void ListTableComple(SSCoreTable& result)=0;
	virtual void SaveAndListComple(SSCoreTable& result)=0;
};

class DllExport CLeaderboard 
{
public:
	CLeaderboard();

	void SetDelegate(CLeaderboardDelegate* targetDelegate);
	//synchronous calls
	CPlaytomicResponsePtr SaveTable(const std::string& tableName,
								 const CScore& score,
								 bool highest,
								 bool allowDuplicates);

	SSCoreTable	ListTable(const std::string& tableName,
								  bool highest,
								  const std::string& mode,
								  int	page,
								  int	perPage,
								  CustomData	customFilter);

	SSCoreTable	SaveAndListTable(const std::string& tableName,
									const CScore& score,
									bool highest,
									bool allowDuplicates,
									const std::string& mode,
									int	perPage,
									CustomData	customFilter);

	//async calls
	void	SaveTableAsync(const std::string& tableName,
		const CScore& score,
		bool highest,
		bool allowDuplicates);

	void	ListTableAsync(const std::string& tableName,
		bool highest,
		const std::string& mode,
		int	page,
		int	perPage,
		CustomData	customFilter);

	void	SaveAndListTableAsync(const std::string& tableName,
		const CScore& score,
		bool highest,
		bool allowDuplicates,
		const std::string& mode,
		int	perPage,
		CustomData	customFilter);

	void SaveComple(CPlaytomicResponsePtr& response);
	void ListComple(CPlaytomicResponsePtr& response);
	void SaveAndListComple(CPlaytomicResponsePtr& response);
private:
	CLeaderboardDelegate* mDelegate;
};

}
#endif