//
//  FilePaths.cpp
//  Playtomic
//
//  Created by matias calegaris on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "FilePaths.h"
#include <string>
#include <string.h>
#ifdef __ANDROID__
#include <jni.h>
#include "CPlaytomicAndroid.h"
#include <android/log.h>

#define  LOG_TAG    "playtomicFilePaths"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
 
void GetFilePath(char* dest, int maxLength, const char* pFileName)
{

    
    //jni wtf
    // Acquire a pointer to the current JavaVM
    JavaVM * jVM = Playtomic::CPlaytomicAndroid::GetJavaVM();
    if(jVM == NULL)
    {
        return;
    }
    
    JNIEnv* env = 0;
    
  	int status = jVM->GetEnv((void **)&env, JNI_VERSION_1_6);
    bool dettachProcess = false;
    if(status < 0)
    {
        dettachProcess = true;
	    status = jVM->AttachCurrentThread(&env, NULL);
	    if(status < 0)
	    {
	        return;
	    }
    }
    jclass cls_env = env->FindClass("android/os/Environment");
	jmethodID mid_getExtStorage = env->GetStaticMethodID(cls_env, "getExternalStorageDirectory",  "()Ljava/io/File;");
	jobject obj_File = env->CallStaticObjectMethod(cls_env, mid_getExtStorage);
    
	jclass file = env->FindClass("java/io/File");
	jmethodID mid_getPath = env->GetMethodID(file, "getPath", "()Ljava/lang/String;");
    
	jstring obj_Path = (jstring)(env->CallObjectMethod(obj_File, mid_getPath));
    
	const char* path = env->GetStringUTFChars(obj_Path, NULL);
    
	std::string fullPath(path);
    env->ReleaseStringUTFChars(obj_Path, path);
    fullPath +=  "/";
    fullPath += pFileName;
    
    if(fullPath.length() > maxLength)
    {
        return;
    }
    
    strcpy( dest, fullPath.c_str());
    
    
    if(dettachProcess)
	{
		jVM->DetachCurrentThread();
	}
}

#else
#ifndef __IOSSDK__
void GetFilePath(char* dest, int maxLength, const char* pFileName)
{
    
	std::string fullPath(pFileName);
        
    if(fullPath.length() > maxLength)
    {
        return;
    }
    
    strcpy( dest, fullPath.c_str());
}
#endif
#endif
