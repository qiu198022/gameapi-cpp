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
#include "CLevel.h"

namespace Playtomic
{


    CLevel::CLevel( const std::string& name, const std::string& playerName, 
                   const std::string& playerId, const std::string& data ) : 
    mLevelId(" "),
    mPlayerId(" "),
    mPlayerName(" "),
    mPlayerSource(" "),
    mName(" "),
    mData(" "),
    mThum(" "),
    mDate(" "),
    mRelativeDate(" ")
{
	mName = name;
	mPlayerName = playerName;
	mPlayerId = playerId;
	mData = data;
}

CLevel::CLevel( const std::string& name, const std::string& playerName, const std::string& playerId,
	const std::string& playerSource, const std::string& data,
	const std::string& thum, int votes, int plays, float rating, int score,
               const std::string date, const std::string& relativeDate,
               const CustomData& customData, const std::string& levelID )  : 
    mLevelId(" "),
    mPlayerId(" "),
    mPlayerName(" "),
    mPlayerSource(" "),
    mName(" "),
    mData(" "),
    mThum(" "),
    mDate(" "),
    mRelativeDate(" ")
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
    mDate = date;
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
    
const std::string& CLevel::GetDate() const
{
    return mDate;
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