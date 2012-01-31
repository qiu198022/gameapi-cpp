//
//  CExceptionHandler_UnixImp.cpp
//  Playtomic
//
//  Created by matias calegaris on 1/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "../CExceptionHandler.h"

namespace Playtomic
{
    void CExceptionHandler::GetStackTrace(std::string &dest)
    {
        dest += "could not get android stack information";
    }
}