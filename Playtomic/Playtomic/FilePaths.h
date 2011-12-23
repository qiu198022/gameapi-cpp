//
//  FilePaths.h
//  Playtomic
//
//  Created by matias calegaris on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Playtomic_FilePaths_h
#define Playtomic_FilePaths_h

#if defined(_IOS_) || defined(__ANDROID__)
void GetFilePath(char* dest, int maxLength, const char* pFileName);
#endif

#endif
