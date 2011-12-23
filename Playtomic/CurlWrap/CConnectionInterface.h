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
#ifndef __CONNECTION_INTERFACE_H__
#define __CONNECTION_INTERFACE_H__

#include "CPlaytomicResponse.h"
#include "FastDelegate.h"
#include <list>

#ifndef _CPOST_H_
#include "CPost.h"
#endif

namespace boost {
    class thread;
}


typedef fastdelegate::FastDelegate1<CPlaytomicResponsePtr&> RequestDelegate;

typedef boost::shared_ptr<boost::thread> ThreadPtr;
typedef boost::shared_ptr<CPost> CPostPtr;

class CAsyncRequest;

class CConnectionInterface
{
	//singleton interface
public:
	static CConnectionInterface*	Get();
	static void						Destroy();

public:

	void Init();

	CPlaytomicResponsePtr PerformSyncRequest(const char* url, CPost* postData = NULL);

	void	PerformAsyncRequest(const char* url, RequestDelegate targetDelegate);
	void	PerformAsyncRequest(const char* url, RequestDelegate targetDelegate, CPostPtr postData);

    void    ThreadFinish(CAsyncRequest* thread);
private:
	CConnectionInterface();
	~CConnectionInterface();

	static CConnectionInterface* sHandle;
    
    std::list<CAsyncRequest*> mThreadList;
};

#define gConnectionInterface CConnectionInterface::Get()

#endif