#ifndef __PLAYTOMIC_PLAYER_LEVELS_H__
#define __PLAYTOMIC_PLAYER_LEVELS_H__

#include "PlaytomicDefines.h"
#include "../CurlWrap/CPlaytomicResponse.h"
#include <string>
#include "CLevel.h"
#include "CPlaytomicDelegate.h"
#include <list>

namespace Playtomic {

struct SLevelList 
{
	std::list<CLevel>  sLevelList;
	int							sErrorCode;
	int							sLevelCount;
	bool						sSucceded;
};

typedef boost::shared_ptr<SLevelList> SLevelListPtr;

/**
* PlayerLevel Delegate interface
*	if you use the Asynchronous methods you will need to inherit from this interface
*	to get the information or the commit status
*	you will also need to set as the target delegate to CPlayerLevel
*/
class DllExport IPlayerLevelDelegate
{
public:
	virtual void RateLevelComplete(CPlaytomicResponsePtr& result)=0;
	virtual void LevelListComple(SLevelList& result)=0;
	virtual void SaveLevelComple(SLevelList& result)=0;
	virtual void LoadLevelComplete(SLevelList& result)=0;
};

/**
*	Save and listing levels interface
*/
class  DllExport CPlayerLevels
{
public:
	CPlayerLevels();

	//if you use any asynchronous call you need to set the delegate
	void SetDelegate(IPlayerLevelDelegate* targetDelegate);

	// synchronous calls
	/**
	*	Get one level using the level id, this id is generated by Playtomic servers
	*	it will be retrieved when you save the level or you cant get the id by listing 
	*	the player levels @see List()
	*	@param	levelId		the level id generated by Playtomic servers
	*	@return	a SLevelList with one level in the list if sSucced is true or
	*	the error code if fail, check the documentation about error codes
	*/
	SLevelListPtr			LoadLevel(const std::string& levelId);

	/**
	*	Levels can be rated 1 - 10 by players. Rating can be done anonymously with
	*	some protection against repeat voting, or bound to PlayerIds if you specify them.
	*	@param levelId		the level id generated by Playtomic servers
	*	@param rating		the new level rating from 1 to 10
	*	@return	a CPlaytomicResponse check the documentation about error codes
	*/
	CPlaytomicResponsePtr	RateLevelId(const std::string& levelId, int rating);

	/**
	*	Listing levels can be done by popular or newest, with optional filtering
	*	by date ranges and/or custom data.
	*	@param mode			'popular' or 'newest'
	*	@param page			The page you want
	*	@param perPage		The number of levels to return
	*	@param includeData	specify true if you want level data returned with the list
	*	@param includeThumb	specify true if you want level data thumbnail url included
	*	@param customFilter	filter by custom data you've saved with levels
	
	*	@return a SLevelList with the list of level or the error code if the request fail
	*/
	SLevelListPtr			List(const std::string& mode, int page, int perPage,
							bool includeData, bool includeThumbs,
							const CustomData& customFilter);

	/**
	*	@return the level with all the information from the Playtomic server (levelId and relative date)
	*/
	SLevelListPtr			SaveLevel(CLevel& level);

	// asynchronous calls
	// for more details see the synchronous calls the only difference is that they send the
	// response to the callback instead of the return value
	// take care to set the delegate to null if you need to delete it after doing a request
	void	LoadLevelAsync(const std::string& levelId);
	void	RateLevelIdAsync(const std::string& levelId, int rating);
	void	ListAsync(const std::string& mode, int page, int perPage,
					bool includeDAta, bool includeThumbs,
					const CustomData& customFilter);
	void	SaveLevelAsync(CLevel& level);

	//internal delegates for the connection interface 
	// the process the request response and calls the current delegate
	void	LoadLevelComplete(CPlaytomicResponsePtr& response);
	void	RateLevelIdComplete(CPlaytomicResponsePtr& response);
	void	ListAsyncComplete(CPlaytomicResponsePtr& response);
	void	SaveLevelComplete(CPlaytomicResponsePtr& response);
private:
	void					AddLevel(const FData& level, const std::string& levelId,
									std::list<CLevel>& levelList);
	IPlayerLevelDelegate*	mDelegate;
	std::string				mLevelId;
};

}
#endif