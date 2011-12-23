//
//  FilePaths.mm
//  Playtomic
//
//  Created by matias calegaris on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "FilePaths.h"
#ifdef _IOS_
#import <UIKit/UIKit.h>

void GetFilePath(char* dest, int maxLength, const char* pFileName)
{
    NSString* path = [NSString stringWithString:[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
    path = [NSString stringWithFormat:@"%@/%@", path, [NSString stringWithCString:pFileName encoding:NSUTF8StringEncoding]];
    [path getCString:dest maxLength:maxLength encoding:NSUTF8StringEncoding];
}

#endif