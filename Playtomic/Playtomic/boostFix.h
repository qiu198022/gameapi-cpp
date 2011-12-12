//
//  boostFix.h
//  
//
//  Created by matias calegaris on 11/25/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _boostFix_h
#define _boostFix_h

#ifdef __ANDROID__

#include <exception>

#ifdef __BOOST_HACK__
namespace std
{
    struct bad_alloc : public exception { bad_alloc operator()(){}};
}
namespace std
{
    struct bad_cast : public exception {bad_cast operator()(){}};
    struct bad_typeid : public exception {bad_typeid operator()(){}};
}
#endif
#endif


#endif
