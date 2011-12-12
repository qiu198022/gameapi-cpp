#include "CScore.h"

namespace Playtomic
{

CScore::CScore(const std::string& name,
	int points,
	std::string& relativeDate,
	const CustomData& customData,
	long rank )
{
	mRank = rank;
	mCustomData = customData;
	mRelativeDate = relativeDate;
	mPoints = points;
	mName = name;
}

CScore::CScore(const std::string& name, int points, const CustomData& customData) : mRelativeDate(" ")
{	
	mCustomData = customData;
	mPoints = points;
	mName = name;
}

    CScore::CScore(const std::string& name, int points) : mRelativeDate(" ")
{
	mName = name;
	mPoints = points;
}

void CScore::SetDefaultValues(const std::string& name, int points)
{
	mName = name;
	mPoints = points;
}

const std::string& CScore::GetName() const
{
	return mName;
}

int CScore::GetPoints() const
{
	return mPoints;
}

long CScore::GetRank() const
{
	return mRank;
}

const std::string& CScore::GetRelativeDate() const
{
	return mRelativeDate;
}

const CustomData& CScore::GetCustomData() const
{
	return mCustomData;
}

const std::string& CScore::GetCustomValue( const std::string& key ) const
{
	return mCustomData.find(key)->second;
}

}