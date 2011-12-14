//
//  DataStructure.cpp
//  Playtomic
//
//  Copyright 2011 Playtomic. All rights reserved.
//  This file is part of the official Playtomic API for C++ games.
//  Playtomic is a real time analytics platform for casual games
//  and services that go in casual games.  If you haven't used it
//  before check it out:
//  http://playtomic.com/
//
//  Created by Matias at the above domain on 11/19/11.
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

#include "DataStructures.h"


namespace Playtomic {

    CGenericMetric::CGenericMetric()
    {
        mValue = 0;
    }
    
    CGenericMetric::CGenericMetric(const FData& source)
    {
        Init(source);
    }
    
    void CGenericMetric::Init(const FData& source)
    {
        FData value;
        
        value = source.get("Value", value);
        
        if(value.isInt())
        {
            mValue = value.asInt();
        }
        else if(value.isString())
        {
            mValue = atoi(value.asCString());
        }
    }
    
    CLevelAverage::CLevelAverage()
    {
        mMin = 0;
        mMax = 0;
        mAverage = 0;
        mTotal = 0;
    }
    
    CLevelAverage::CLevelAverage(const FData& source)
    {
        mMin = 0;
        mMax = 0;
        mAverage = 0;
        mTotal = 0;
        Init(source);
    }
    
    void CLevelAverage::Init(const FData& source)
    {
        FData value;
        
        value = source.get("Min", value);
        
        if(value.isInt())
        {
            mMin = value.asInt();
        }
        else if(value.isString())
        {
            mMin = atoi(value.asCString());
        }
        
        value = source.get("Max", value);
        
        if(value.isInt())
        {
            mMax = value.asInt();
        }
        else if(value.isString())
        {
            mMax = atoi(value.asCString());
        }
        
        value = source.get("Average", value);
        
        if(value.isInt())
        {
            mAverage = value.asInt();
        }
        else if(value.isString())
        {
            mAverage = atoi(value.asCString());
        }
        
        value = source.get("Total", value);
        
        if(value.isInt())
        {
            mTotal = value.asInt();
        }
        else if(value.isString())
        {
            mTotal = atoi(value.asCString());
        }
    }
    
    CRangedMetric::CRangedMetric()
    {
        
    }
    
    CRangedMetric::CRangedMetric(const FData& source)
    {
        Init(source);
    }
    
    void CRangedMetric::Init(const FData& source)
    {
        FData array;
        
        array = source.get("Values", array);
        mEntries.clear();
        if(array.isArray())
        {
            for (size_t i = 0; i < array.size(); i++)
            {
                FData object;
                object = array[(int)i];
                RangedEntryPtr ptr(new RangedEntry);
                
                FData value;
                value = source.get("Tracking", value);
                
                if(value.isString())
                {
                    ptr->sName = value.asString();
                }
                
                value = source.get("Occurances", value);
                
                if(value.isInt())
                {
                    ptr->sInt = value.asInt();
                }
                else if(value.isString())
                {
                    ptr->sInt = atoi(value.asCString());
                }
                
                mEntries.push_back(ptr);
            }

        }
    }
}