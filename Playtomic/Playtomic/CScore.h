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