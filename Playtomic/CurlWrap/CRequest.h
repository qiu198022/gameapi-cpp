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
#ifndef __CREQUEST_H__
#define __CREQUEST_H__

#include "curl/curl.h"
#include "Common.h"

class CPost;

struct SRequestResult
{
public:
	char*	data;
	size_t	size;

	void Clear();
	SRequestResult();
	~SRequestResult();
};
class CRequest
{
public:
	
public:
	CRequest();
	~CRequest();


	void			CreateQuery(const char* addres);
	void			SetPostData(CPost* post);
	ERequestResult	Perform(SRequestResult* dest);
private:
	CURL *mHandle;

	ERequestResult mLastResult;

};

#endif