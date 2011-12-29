//
//  PlaytomicAndroid.h
//  Playtomic
//
//  Created by matias calegaris on 12/27/11.
//  Copyright (c) 2011 Playtomic. All rights reserved.
//

#ifndef Playtomic_PlaytomicAndroid_h
#define Playtomic_PlaytomicAndroid_h


#ifdef __ANDROID__
#include "CPlaytomic.h"
#include <jni.h>
namespace Playtomic
{
    
class CPlaytomicAndroid : public CPlaytomic
{
public:
    CPlaytomicAndroid(int gameId, std::string& gameguid, JavaVM* javaVMPtr, jobject activity, bool autoUpdate = false);
    
    
    static JavaVM* GetJavaVM();
    static jobject GetActivity();
private:
    
    static JavaVM* mJavaVM;
    static jobject mActivity;
};
    
}
#endif
#endif
