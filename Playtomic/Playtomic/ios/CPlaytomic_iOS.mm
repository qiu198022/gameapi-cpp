//
//  CPlaytomic_iOS.mm
//  Playtomic
//
//  Created by matias calegaris on 1/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "../CPlaytomic.h"
#import "UIKit/UIDevice.h"

namespace Playtomic {

    void CPlaytomic::GetDeviceFromSystem()
    {
        NSString *model = [[UIDevice currentDevice] model];
        NSString *system = [[UIDevice currentDevice] systemName];
        NSString *version = [[UIDevice currentDevice] systemVersion];
        
        mDevice = "Model = ";
        mDevice += [model cStringUsingEncoding:NSASCIIStringEncoding];
        mDevice += "\n";
        mDevice += "system = ";
        mDevice += [system cStringUsingEncoding:NSASCIIStringEncoding];
        mDevice += "\n";
        mDevice += "version = ";
        mDevice += [version cStringUsingEncoding:NSASCIIStringEncoding];
        mDevice += "\n";        
    }
}