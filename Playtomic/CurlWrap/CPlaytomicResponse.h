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
#ifndef __CPLAYTOMIC_RESPONSE_H__
#define __CPLAYTOMIC_RESPONSE_H__

#include "Common.h"
#ifdef __ANDROID__
#include "boostFix.h"
#endif
#include "boost/shared_ptr.hpp"


class DllExport CPlaytomicResponse
{
public:
	CPlaytomicResponse();
	CPlaytomicResponse(int errorCode);
	CPlaytomicResponse(bool success, int errorCode);
	CPlaytomicResponse(bool success, int errorCode, const FData& source, int resultCount);
	CPlaytomicResponse(const CPlaytomicResponse& source);

	bool ResponseSucceded() const;
	void ResponseSucceded(bool val) ;
	int ResponseError() const;
	void ResponseError(int val);
	const FData& ResponseData() const ;
	void ResponseData(const FData& val) ;
	int NumResult() const ;
	void NumResult(int val);

	CPlaytomicResponse& operator=(const CPlaytomicResponse& source);
private:
	bool		mResponseSucceded;	
	int			mResponseError;	
	FData		mResponseData;	
	int			mNumResult;
	
};

typedef boost::shared_ptr<CPlaytomicResponse> CPlaytomicResponsePtr;
#endif
