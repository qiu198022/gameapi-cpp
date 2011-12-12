#ifndef __PLAYTOMIC_SCORE_H__
#define __PLAYTOMIC_SCORE_H__

#include <string>
#include <map>
#include "PlaytomicDefines.h"

namespace Playtomic
{

	/**
	*	used by the leaderboards to represent the player score
	*/
class DllExport CScore
{
public:
	
	

	/**
	*	Use this constructor to create new scores and upload them to the Playtomic servers
	*/
	// empty constructor should call SetDefaultValues before commit the score
	CScore() {}
    ~CScore() {}
	/**
	*	@param name		player name
	*	@param points	player score
	*	@param customData	Any additional data you want to (or have) attached to
	*		a score, like the level the player reached or what character they used
	*/
	CScore(const std::string& name, int points, const CustomData& customData);
	CScore(const std::string& name, int points);

	/**
	*	Constructor used by CLeaderboard to initialize the score with the Playtomic generated
	*	information (relative date, rank)
	*/
	CScore(const std::string& name, int points,
		std::string& relativeDate, const CustomData& customData, long rank );

	void				SetDefaultValues(const std::string& name, int points);

	const std::string&	GetName()const;
	int					GetPoints() const ;
	long				GetRank() const ;
	const std::string&	GetRelativeDate() const ;
	const CustomData&	GetCustomData() const;
	const std::string&	GetCustomValue(const std::string& key) const;
private:
	std::string		mName;
	int				mPoints;
	//TODO add date
	std::string		mRelativeDate;
	CustomData		mCustomData;
	long			mRank;
};

}
#endif