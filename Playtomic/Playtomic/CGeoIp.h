#ifndef __PLAYTOMIC_GEO_IP_H__
#define __PLAYTOMIC_GEO_IP_H__

#include "../CurlWrap/CConnectionInterface.h"
#include "PlaytomicDefines.h"

namespace Playtomic
{

/*
*	The GeoIP service identifies which country the player is from, returning their country code and name.
*/

class DllExport CGeoIP
{
public:
	CGeoIP();

	/*
	*	@return CPlaytomicResponse with the data formatd: Object with "Code" and "Name"
	*			as keys
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
};

}
#endif