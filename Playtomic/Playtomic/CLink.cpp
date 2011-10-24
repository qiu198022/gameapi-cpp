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