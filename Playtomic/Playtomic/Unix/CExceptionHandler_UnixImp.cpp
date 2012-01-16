//
//  CExceptionHandler_UnixImp.cpp
//  Playtomic
//
//  Created by matias calegaris on 1/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "../CExceptionHandler.h"
#include <execinfo.h>

namespace Playtomic
{
    void CExceptionHandler::GetStackTrace(std::string &dest)
    {
#ifdef _IOSSDK_
        dest += "ios stack \n";
#else
        dest += "unix stack mac\n";	
#endif
        void *array[128];
        // get void*'s for all entries on the stack
        size_t size = backtrace(array, 128);

        char** symbols = backtrace_symbols(array, size);
        
        for(int i = 2; i < size; i++)
        {
            dest += static_cast<char*>(symbols[i]);
            dest += "\n";
        }
        free(symbols);
    }
}