//
//  PlaytomicAndroid.cpp
//  Playtomic
//
//  Created by matias calegaris on 12/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifdef __ANDROID__
#include "CPlaytomicAndroid.h"


namespace Playtomic
{
    
JavaVM* CPlaytomicAndroid::mJavaVM = NULL;
jobject CPlaytomicAndroid::mActivity = NULL;

CPlaytomicAndroid::CPlaytomicAndroid(int gameId, std::string& gameguid,
                                     JavaVM* javaVMPtr, jobject activity,
                                     bool autoUpdate)
: CPlaytomic( gameId, gameguid, autoUpdate)
{
    mJavaVM = javaVMPtr;
    mActivity = activity;
}


JavaVM* CPlaytomicAndroid::GetJavaVM()
{
    return mJavaVM;
}
    
jobject CPlaytomicAndroid::GetActivity()
{
    return mActivity;
}
    
}

#endif