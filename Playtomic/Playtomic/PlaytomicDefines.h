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
#ifndef __PLAYTOMIC_DEFINES_H__
#define __PLAYTOMIC_DEFINES_H__

#include <map>
#include "CPlaytomicResponse.h"

#if defined (_LINUX_) || defined (_OPENBSD_) || (__ANDROID__)
#include <cstdio>
#define	sprintf_s(buffer, buffer_size, stringbuffer, ...) (sprintf(buffer, stringbuffer, __VA_ARGS__))
#endif

#ifdef CREATE_DLL
#define DllExport __declspec(dllexport)
#pragma warning (disable: 4251)
#else
#ifdef LINK_DLL
#define DllExport __declspec(dllimport)
#else
#define DllExport
#endif
#endif

namespace Playtomic
{

typedef std::map<std::string,std::string> CustomData;

//log
const char kBasetrackUrlPart1[] = "http://g";
const char kBaseTrackUrlPart2[] = ".api.playtomic.com/tracker/q.aspx?swfid=";
const char kBaseTrackUrlPart3[] = "&url=";
const char kBaseTrackUrlPart4[] = "&q="; 

//geo ip
const char kGeoIpUrl1[] = "http://g";
const char kGeoIpUrl2[] = ".api.playtomic.com/geoip/lookup.aspx?swfid=";
const char kGeoIpUrl3[] = "&js=y";

//game vars
const char kGameVarsUrl1[] = "http://g";
const char kGameVarsUrl2[] = ".api.playtomic.com/gamevars/load.aspx?swfid=";
const char kGameVarsUrl3[] ="&js=y";

//leaderboards
const char kLeaderboardUrl1[] = "http://g";
const char kLeaderboardUrl2[] = ".api.playtomic.com/v2/leaderboards/save.aspx?swfid=";
const char kLeaderboardUrl3[] ="&js=y";
const char kLeaderboardUrlList[] = ".api.playtomic.com/v2/leaderboards/list.aspx?swfid=";
const char kLeaderboardUrlSaveAndList[] = ".api.playtomic.com/v2/leaderboards/saveandlist.aspx?swfid=";


//player levels
const char kPlayerLevelUrl1[] = "http://g";
const char kPlayerLevelUrl2[] = ".api.playtomic.com/playerlevels/load.aspx?swfid=";
const char kPlayerLevelUrl3[] =	"&js=m&levelid=";

const char kPlayerLevelRateUrl2[] = ".api.playtomic.com/playerlevels/rate.aspx?swfid=";
const char kPlayerLevelRateUrl1[] = "http://g";
const char kPlayerLevelRateUrl3[] =	"&js=m&levelid=";
const char kPlayerLevelRateUrl4[] = "&rating=";

const char kPlayerLevelListUrl1[] = "http://g";
const char kPlayerLevelListUrl2[] = ".api.playtomic.com/playerlevels/list.aspx?swfid=";
const char kPlayerLevelListUrl3[] =	"&js=m&mode=";
const char kPlayerLevelListUrl4[] = "&page=";
const char kPlayerLevelListUrl5[] = "&perpage=";
const char kPlayerLevelListUrl6[] =	"&data=";
const char kPlayerLevelListUrl7[] = "&thumbs=";
const char kPlayerLevelListUrl8[] = "&datemin=";
const char kPlayerLevelListUrl9[] =	"&datemax=";
const char kPlayerLevelListUrl10[] = "&filters=";

const char kPlayerLevelSaveUrl1[] = "http://g";
const char kPlayerLevelSaveUrl2[] = ".api.playtomic.com/playerlevels/save.aspx?swfid=";
const char kPlayerLevelSaveUrl3[] =	"&&js=y&url=";

//playtomic data
//general

const char kDataGeneralUrl1[] = "http://g";
const char kDataGeneralUrl2[] = ".api.playtomic.com/data/";
const char kDataGeneralUrl3[] =	".aspx?swfid=";
const char kDataGeneralUrl4[] = "&js=m&&day=";
const char kDataGeneralUrl5[] =	"&month=";
const char kDataGeneralUrl6[] = "&year=";

const char kDataCustomUrl1[] = "http://g";
const char kDataCustomUrl2[] = ".api.playtomic.com/data/custommetric.aspx?swfid=";
const char kDataCustomUrl3[] =	"&js=m&&metric=";
const char kDataCustomUrl4[] = "&day=";
const char kDataCustomUrl5[] =	"&month=";
const char kDataCustomUrl6[] = "&year=";

const char kDataLevelUrl1[] = "http://g";
const char kDataLevelUrl2[] = ".api.playtomic.com/data/levelmetric";
const char kDataLevelUrl3[] = ".aspx?swfid=";
const char kDataLevelUrl4[] = "&js=m&metric=";
const char kDataLevelUrl5[] =	"&level=";
const char kDataLevelUrl6[] =	"&day=";
const char kDataLevelUrl7[] =	"&month=";
const char kDataLevelUrl8[] = "&year="; 

}
#endif
