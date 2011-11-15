#ifndef __PLAYTOMIC_GAME_VARS_H__
#define __PLAYTOMIC_GAME_VARS_H__


#include "../CurlWrap/CConnectionInterface.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{

/**
*		GameVars let you change the value of key variables in your game any time
*		you want. They must be configured on the edit GameVars page in advance.

*		You store a bunch of data in Playtomic, have it in your game as a backup
*		for when there's no client connectivity, and then whenever possible, the
*		player can use the most recent values.
*/
class DllExport CGameVars
{
public:
	CGameVars();

	/*
	*	@return CPlaytomic object with and array of objects with two keys: "Name" and "Value"
	*	a simple example:
	*
	*CPlaytomicResponsePtr response = Playtomic::gPlaytomic->GameVars()->Load();
	*if (response->ResponseSucceded())
	*{
	*	FData array;
	*	array = response->ResponseData();
	*	if(array.size() == 0)
	*	{
	*		std::cout << " empty game vars" << std::endl;
	*		break;
	*	}
	*	else
	*	{
	*		FData value;
	*		for (size_t i = 0; i < array.size(); i++)
	*		{
	*			value = array[i];
	*
	*			FData name;
	*			name = value.get("Name", name);
	*			FData varValue;
	*			varValue = value.get("Value",varValue);
	*
	*			std::cout << name.asString() << "=" << varValue.asString() << std::endl; 
	*		}
	*	}
	*}
	*/
	CPlaytomicResponsePtr	Load();

	/*
	*	asynchronous version of load
	*	you need to set a target delegate to get the data, it could be any class method
	*	that takes CPlaytomicResponsePtr& and return void
	*
	*	e.g. void  CAnyClass::delegate(CPlaytomicResponsePtr& response);
	*
	*	you generate the delegate by calling  fastdelegate::MakeDelegate()
	*	e.g. fastdelegate::MakeDelegate(this,&CAnyClass::delegate);
	*
	*	function call eg: LoadAsync(fastdelegate::MakeDelegate(this,&CAnyClass::delegate));
	*  
	*	you can make all the calls you want to load async and give different delegates every time
	*	but you should not delete these instance since you can't stop the delegate call
	*/
	void					LoadAsync(RequestDelegate targetDelegate);
private:
};

}
#endif