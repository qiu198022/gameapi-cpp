//
//  CheckWifi.cpp
//  Playtomic
//
//  Created by matias calegaris on 12/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include "CConnectionInfo.h"
#ifdef __ANDROID__

#include <jni.h>
#include "CPlaytomicAndroid.h"
#include <android/log.h>

#define  LOG_TAG    "playtomicCheckWifi"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif
namespace Playtomic {

class CConnectionInfoAndroid : public CConnectionInfoBase
{
public:
    virtual void Init();
    virtual EConnectionType GetConnectionType();
    
private:

};

#ifndef __ANDROID__
class CConnectionInfoGeneric : public CConnectionInfoBase
{
public:
    virtual void Init();
    virtual EConnectionType GetConnectionType();
    
private:
};
#endif
 
#ifndef _IOSSDK_
CConnectionInfoBase* CConnectionInfoBase::CreateInstance()
{
#if defined( __ANDROID__)
    return new CConnectionInfoAndroid;
#else
    return new CConnectionInfoGeneric;
#endif
}
#endif
    

#ifdef __ANDROID__

void CConnectionInfoAndroid::Init()
{
}
    
    
CConnectionInfoBase::EConnectionType CConnectionInfoAndroid::GetConnectionType()
{
    
// Acquire a pointer to the current JavaVM
    JavaVM * jVM = CPlaytomicAndroid::GetJavaVM();
    if(jVM == NULL)
    {

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

    jclass cls_context = env->FindClass("android/content/Context");
	jmethodID sys_service = env->GetMethodID(cls_context, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    
	jfieldID fid = env->GetStaticFieldID(cls_context, "CONNECTIVITY_SERVICE",
                                         "Ljava/lang/String;");
    
	jstring systemstr = (jstring)env->GetStaticObjectField(cls_context, fid);

	jobject obj_connectManager = env->CallObjectMethod(activity, sys_service,systemstr);
    jclass cls_env = env->GetObjectClass(obj_connectManager);
	jmethodID mid_getExtStorage = env->GetMethodID(cls_env, "getActiveNetworkInfo", "()Landroid/net/NetworkInfo;");
	jobject obj_netInfo = env->CallObjectMethod(obj_connectManager, mid_getExtStorage);
    int type = -1;
    if( obj_netInfo)
    {
        jclass cls_netInfo = env->GetObjectClass(obj_netInfo);
        jmethodID mid_getType = env->GetMethodID(cls_netInfo, "getType",  "()I");
        type = env->CallIntMethod(obj_netInfo, mid_getType);

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
    
void CConnectionInfoGeneric::Init()
{
    
}
    
CConnectionInfoBase::EConnectionType CConnectionInfoGeneric::GetConnectionType()
{
    return e_wifi;
}
    

#endif
#endif
}
