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
#include "CLink.h"
#include "CPlaytomic.h"
#include "CLog.h"

namespace Playtomic
{

void CLink::Track(const std::string& url, const std::string& name, const std::string& group)
{

	int unique = 0;
	int bunique = 0;
	int total	= 0;
	int btotal	= 0;
	std::string key(url);
	url + name;

	std::string baseUrl = url;
	size_t posInString = -1;
	do 
	{
		posInString = baseUrl.find("http://", posInString + 1);
		if(posInString != -1)
		{
			baseUrl.erase(posInString, 7);
		}
	} while ( posInString != -1);
	posInString = -1;
	do 
	{
		posInString = baseUrl.find("https://", posInString + 1);
		if(posInString != -1)
		{
			baseUrl.erase(posInString, 8 );
		}
	} while ( posInString != -1);

	posInString = baseUrl.find("/", 0);

	if(posInString != -1)
	{
		baseUrl =  baseUrl.substr(0,posInString);
	}
	std::string baseUrlName = baseUrl;

	posInString = -1;
	do 
	{
		posInString = baseUrlName.find("www.", posInString + 1);
		if(posInString != -1)
		{
			baseUrlName.erase(posInString, 4 );
		}
	} while ( posInString != -1);

	std::map<std::string, int>::iterator it = mClick.find(key);
	if(it != mClick.end())
	{
		total = 1;
		unique = 1;
		mClick.insert(std::make_pair(key,0));
	}
	else
	{
		total = 1;
	}

	it = mClick.find(baseUrlName);
	if(it != mClick.end())
	{
		btotal = 1;
		bunique = 1;
		mClick.insert(std::make_pair(baseUrlName,0));
	}
	else
	{
		btotal = 1;
	}
	gPlaytomic->Log()->LinkUrl(baseUrl, baseUrlName, "DomainTotals", bunique, btotal, 0);
	gPlaytomic->Log()->LinkUrl(baseUrl, baseUrlName, group, bunique, btotal, 0);
	gPlaytomic->Log()->ForceSend();
}

}