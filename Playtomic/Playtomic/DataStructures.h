//
//  DataStructures.h
//  Playtomic
//
//  Created by matias on 11/19/11.
//  Copyright 2011 Playtomic. All rights reserved.
//

#ifndef Playtomic_DataStructures_h
#define Playtomic_DataStructures_h

#include "PlaytomicDefines.h"
#include "boost/shared_ptr.hpp"
#include <list>

namespace Playtomic {
    
class CGenericMetric
{
public:
    CGenericMetric();
    CGenericMetric(const FData& source);
    
    void Init(const FData& source);
    int mValue;
};

    
class CLevelAverage
{
public:
    CLevelAverage();
    CLevelAverage(const FData& source);
    void Init(const FData& source);
    int mAverage;
    int mMin;
    int mMax;
    int mTotal;
};
 
struct RangedEntry
{
    std::string sName;
    int         sInt;
};
typedef boost::shared_ptr<RangedEntry> RangedEntryPtr;
    
class CRangedMetric
{
public:
    CRangedMetric();
    CRangedMetric(const FData& source);
    void Init(const FData& source);
    std::list<RangedEntryPtr> mEntries;
};
}

#endif
