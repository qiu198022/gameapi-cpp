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
#include "CPlaytomicResponse.h"

CPlaytomicResponse::CPlaytomicResponse()
	: mResponseError(0),
	mResponseSucceded(false),
	mNumResult(0),
	mResponseData( Json::nullValue)
{

}

CPlaytomicResponse::CPlaytomicResponse(int errorCode)
	: mResponseError(errorCode),
	mResponseSucceded(false),
	mNumResult(0),
	mResponseData( Json::nullValue)
{
}


CPlaytomicResponse::CPlaytomicResponse(bool success, int errorCode)
	: mResponseError(errorCode),
	mResponseSucceded(success),
	mNumResult(0),
	mResponseData( Json::nullValue)
{
}

CPlaytomicResponse::CPlaytomicResponse(
	bool success, 
	int errorCode, 
	const FData& source,
	int resultCount)
	: mResponseError(errorCode),
	mResponseSucceded(success),
	mNumResult(resultCount),
	mResponseData(source)
{
}

CPlaytomicResponse::CPlaytomicResponse(const CPlaytomicResponse& source)
{
	*this = source;
}

bool CPlaytomicResponse::ResponseSucceded() const
{ 
	return mResponseSucceded;
}
void CPlaytomicResponse::ResponseSucceded(bool val)
{ 
	mResponseSucceded = val; 
}

int CPlaytomicResponse::ResponseError() const 
{ 
	return mResponseError;
}

void CPlaytomicResponse::ResponseError(int val) 
{ 
	mResponseError = val; 
}

const FData& CPlaytomicResponse::ResponseData() const
{
	return mResponseData;
}

void CPlaytomicResponse::ResponseData(const FData& val)
{ 
	mResponseData = val;
}

int CPlaytomicResponse::NumResult() const 
{ 
	return mNumResult; 
}

void CPlaytomicResponse::NumResult(int val)
{ 
	mNumResult = val; 
}


CPlaytomicResponse& CPlaytomicResponse::operator= (const CPlaytomicResponse& source)
{
	mNumResult = source.mNumResult;
	mResponseData = source.mResponseData;
	mResponseError = source.mResponseError;
	mResponseSucceded = source.mResponseSucceded;
	return *this;
}