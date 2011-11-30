//
//  DataStructure.cpp
//  Playtomic
//
//  Created by matias on 11/19/11.
//  Copyright 2011 Playtomic. All rights reserved.
//

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