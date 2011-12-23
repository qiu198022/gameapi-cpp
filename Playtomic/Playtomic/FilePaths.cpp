//
//  FilePaths.cpp
//  Playtomic
//
//  Created by matias calegaris on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifdef __ANDROID__
#include "FilePaths.h"
#include <string>

void GetFilePath(char* dest, int maxLength, const char* pFileName)
{
    if(dest == NULL || pFileName == NULL)
    {
        return;
    }
    std::string path("/scard/");
    path += pFileName;
    
    if(path.length() > maxLength)
    {
        return;
    }
    
    strcpy( dest, path.c_str());
}
#endif