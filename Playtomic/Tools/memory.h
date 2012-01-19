//
//  memory.h
//  Playtomic
//
//  Created by matias calegaris on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Playtomic_memory_h
#define Playtomic_memory_h


template<typename T>
DefaultAllocator 
{
public:
    pointer allocate(size_type nNumObjects, const void *hint = 0)
    {
        new (nNumObjects*sizeof(T));
    }
    
    void deallocate(pointer p, size_type nNumObjects)
    {
        delete(p, nNumObjects*sizeof(T));
    }
};

#endif
