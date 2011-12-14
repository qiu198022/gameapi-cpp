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