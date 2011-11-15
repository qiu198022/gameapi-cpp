#include "CLevel.h"

namespace Playtomic
{


CLevel::CLevel( const std::string& name, const std::string& playerName, const std::string& playerId, const std::string& data )
{
	mName = name;
	mPlayerName = playerName;
	mPlayerId = playerId;
	mData = data;
}

CLevel::CLevel( const std::string& name, const std::string& playerName, const std::string& playerId,
	const std::string& playerSource, const std::string& data,
	const std::string& thum, int votes, int plays, float rating,
	int score, const std::string& relativeDate, const CustomData& customData, const std::string& levelID )
{
	mName = name;
	mPlayerName = playerName;
	mPlayerId = playerId;
	mPlayerSource = playerSource;
	mData = data;
	mThum = thum;
	mPlays = plays;
	mRating = rating;
	mScore = score;
	mRelativeDate = relativeDate;
	mCustomData = customData;
	mLevelId = levelID;
}

void CLevel::AddCustomValue( const std::string& key, const std::string& value )
{
	mCustomData.insert(std::make_pair(key,value));
}

float CLevel::GetRating() const
{
	return mRating;
}

int CLevel::GetPlays() const
{
	return mPlays;
}

const std::string& CLevel::GetLevelId() const
{
	return mLevelId;
}

const std::string& CLevel::GetPlayerId() const
{
	return mPlayerId;
}

const std::string& CLevel::GetPlayerName() const
{
	return mPlayerName;
}

const std::string&CLevel:: GetPlayerSource() const
{
	return mPlayerSource;
}

const std::string& CLevel::GetName() const
{
	return mName;
}

const std::string& CLevel::GetData() const
{
	return mData;
}

const std::string& CLevel::GetThumbnailUrl() const
{
	return mThum;
}

const std::string& CLevel::GetRelativeDate() const
{
	return mRelativeDate;
}

std::string CLevel::GetCustomValue( const std::string& key )
{
	CustomData::iterator it = mCustomData.find(key);

	if( it != mCustomData.end())
	{
		return it->second;
	}
	return (std::string("invalid"));
}

const CustomData& CLevel::GetCustomData()
{
	return mCustomData;
}

}