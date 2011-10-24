#ifndef __PLAYTOMIC_SCORE_H__
#define __PLAYTOMIC_SCORE_H__

#include <string>
#include <map>
#include "PlaytomicDefines.h"

namespace Playtomic
{

class DllExport CScore
{
public:
	CScore() {}
	CScore(const std::string& name, int points,
					std::string& relativeDate, const CustomData& customData, long rank );

	CScore(const std::string& name, int points, const CustomData& customData);
	CScore(const std::string& name, int points);

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
	CustomData			mCustomData;
	long			mRank;
};

}
#endif