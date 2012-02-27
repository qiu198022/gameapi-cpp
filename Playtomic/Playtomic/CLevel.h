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
#ifndef __PLAYTOMIC_LEVEL_H__
#define __PLAYTOMIC_LEVEL_H__

#include <string>
#include <map>

#include "PlaytomicDefines.h"

namespace Playtomic
{
/**
*	this classs provide storage for user-generated content for your game 
*	It can operate anonymously or authenticated via any 3rd party service you're
*	already using.
*	Saving and listing levels uses this class to represent a level.
*/
class DllExport CLevel
{
public:
	/**
	*	Constructor
	*	Use this constructor to create levels in your aplication and upload them to playtomic
	*	using the CPlayerLevels interace
	*	@param name:		the name of the level
	*	@param playerName:	the name of the player or the name provided by any 3rd party API.
	*	@param playerId		If you're working under a 3rd party API you can include the player's user id
	*	@param data			the data of the level saved	
	*/
	CLevel(const std::string& name, const std::string& playerName,
					const std::string& playerId, const std::string& data);
	
	/**
	*	Constructor
	*	this constructor is called by platomic when you load or list levels using
	*	CPlayerLevels interface
	*	@param name:		the name of the level
	*	@param playerName:	the name of the player or the name provided by any 3rd party API.
	*	@param playerId		If you're working under a 3rd party API you can include the player's user id
	*	@param playerSource If you're working under a 3rd party API you can specify which, eg "gamersafe" or "mochicoins"
	*	@param data			the data of the level saved
	*	@param thumb		The URL of the thumbnail, unless you generate them from data (recommended)
	*	@param votes		The number of votes the level has
	*	@param plays		The number of plays the level has
	*	@param rating		The rating the level has (score / votes)
	*	@param score		The sum of all votes the level has
	*	@param relativeDate	The relative date of the level eg "7 minutes ago", determined automatically by Playtomic
	*	@param customData	Any additional data you want to (or have) attached to a score, like the level the player reached or what character they used
	*	@param levelID		this is the level id, it is generated by Playtomic 
	*/
	CLevel(const std::string& name, const std::string& playerName,
					const std::string& playerId,const std::string& playerSource,
					const std::string& data, const std::string& thum,
                    int votes, int plays, float rating, int score,const std::string date,
					const std::string& relativeDate, const CustomData& customData,
					const std::string& levelID);


	void				AddCustomValue(const std::string& key, const std::string& value);

	float				GetRating()const;
	int					GetPlays()const;
	int					GetVotes()const;
	const std::string&	GetLevelId()const;
	const std::string&	GetPlayerId()const;
	const std::string&	GetPlayerName()const;
	const std::string&	GetPlayerSource()const;
	const std::string&	GetName()const;
	const std::string&	GetData()const;
	const std::string&	GetThumbnailUrl()const;
	const std::string&	GetRelativeDate()const;
    const std::string&  GetDate() const;
	std::string			GetCustomValue(const std::string& key);
	const CustomData&	GetCustomData();
private:
	std::string mLevelId;
	std::string mPlayerId;
	std::string mPlayerName;
	std::string mPlayerSource;
	std::string mName;
	std::string mData;
	std::string mThum;
	int			mVotes;
	int			mPlays;
	float		mRating;
	int			mScore;
    std::string mDate;
	std::string	mRelativeDate;
	CustomData	mCustomData;
};

}
#endif