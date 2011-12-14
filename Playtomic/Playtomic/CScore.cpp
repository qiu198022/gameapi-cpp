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