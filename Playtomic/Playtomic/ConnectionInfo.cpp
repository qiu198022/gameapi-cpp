//
//  CheckWifi.cpp
//  Playtomic
//
//  Created by matias calegaris on 12/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "ConnectionInfo.h"
#ifdef __ANDROID__

#include <jni.h>
#include "CPlaytomicAndroid.h"
#include <android/log.h>

#define  LOG_TAG    "playtomicCheckWifi"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif
namespace Playtomic {


#ifdef __ANDROID__
EConnectionType CheckConnectionType()
{
    
    LOGI("ask wifi type");
//jni wtf
// Acquire a pointer to the current JavaVM
    JavaVM * jVM = CPlaytomicAndroid::GetJavaVM();
    if(jVM == NULL)
    {
            LOGI("invalid vm");
        return e_disconnected;
    }
    jobject activity = CPlaytomicAndroid::GetActivity();
    
    JNIEnv* env = 0;
    
  	int status = jVM->GetEnv((void **)&env, JNI_VERSION_1_6);
    bool dettachProcess = false;
    if(status < 0)
    {
        dettachProcess = true;
	    status = jVM->AttachCurrentThread(&env, NULL);
	    if(status < 0)
	    {
                LOGI("invalid env");
	        return e_disconnected;
	    }
    }
    LOGI("get context info");
    jclass cls_context = env->FindClass("android/content/Context");
	jmethodID sys_service = env->GetMethodID(cls_context, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    
	jfieldID fid = env->GetStaticFieldID(cls_context, "CONNECTIVITY_SERVICE",
                                         "Ljava/lang/String;");
    
	jstring systemstr = (jstring)env->GetStaticObjectField(cls_context, fid);
    
    
    LOGI("call activity for manager");
	jobject obj_connectManager = env->CallObjectMethod(activity, sys_service,systemstr);
    LOGI("get manager table");
    jclass cls_env = env->GetObjectClass(obj_connectManager);
	jmethodID mid_getExtStorage = env->GetMethodID(cls_env, "getActiveNetworkInfo", "()Landroid/net/NetworkInfo;");
    LOGI("get net info manager : %d", obj_connectManager);
	jobject obj_netInfo = env->CallObjectMethod(obj_connectManager, mid_getExtStorage);
    LOGI("check for valid net infor :%d", obj_netInfo);
    int type = -1;
    if( obj_netInfo)
    {
        jclass cls_netInfo = env->GetObjectClass(obj_netInfo);//env->FindClass("android/net/NetworkInfo");
        LOGI("get method id %d", cls_netInfo);
        jmethodID mid_getType = env->GetMethodID(cls_netInfo, "getType",  "()I");
        LOGI("call method %d", mid_getType);
        type = env->CallIntMethod(obj_netInfo, mid_getType);
        LOGI("type wtf");
    }
    LOGI("type : %d", type);
    switch (type)
    {
        case e_wifi:
            return e_wifi;
            break;
        case e_mobile:
            return e_mobile;
            break;
    }
    return e_disconnected;
}
#else
#ifndef __IOSSDK__
EConnectionType CheckConnectionType()
{
    return e_wifi;
}
    

#endif
#endif
}
