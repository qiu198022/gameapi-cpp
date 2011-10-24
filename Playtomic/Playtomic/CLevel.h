#ifndef __PLAYTOMIC_LEVEL_H__
#define __PLAYTOMIC_LEVEL_H__

#include <string>
#include <map>

#include "PlaytomicDefines.h"

namespace Playtomic
{

class DllExport CLevel
{
public:
	CLevel(const std::string& name, const std::string& playerName,
					const std::string& playerId, const std::string& data);
	
	CLevel(const std::string& name, const std::string& playerName,
					const std::string& playerId,const std::string& playerSource,
					const std::string& data, const std::string& thum,
					int votes, int plays, float rating, int score,
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
	//TODO add date
	std::string	mRelativeDate;
	CustomData	mCustomData;
};

}
#endif