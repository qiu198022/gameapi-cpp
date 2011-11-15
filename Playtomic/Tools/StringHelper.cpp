#include "StringHelper.h"

void CleanString(std::string& str)
{
	size_t posInString = -1;
	do 
	{
		posInString = str.find("/", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "\\", 2);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("~", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "-", 1);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("%", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%25", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find(";", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%3B", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("?", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%3F", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("/", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%2F", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find(":", posInString + 1);
        if(posInString != -1)
        {
            str.replace(posInString, 1, "%3A", 3);
        }
    } while ( posInString != -1);

    posInString = -1;
    do 
    {
		posInString = str.find("#", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%23", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("&", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%26", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("=", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%3D", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("+", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%2B", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("$", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%24", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find(",", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%2C", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find(" ", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%20", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("<", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%3C", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find(">", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%3E", 3);
		}
	} while ( posInString != -1);

	posInString = -1;
	do 
	{
		posInString = str.find("~", posInString + 1);
		if(posInString != -1)
		{
			str.replace(posInString, 1, "%7E", 3);
		}
	} while ( posInString != -1);
}