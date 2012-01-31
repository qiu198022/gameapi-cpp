

#include "../CPlaytomic.h"
#ifdef __ANDROID__

#include <jni.h>
#include "../CPlaytomicAndroid.h"
#include <android/log.h>

#define  LOG_TAG    "playtomicAndroid"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#endif

namespace Playtomic {
    void CPlaytomic::GetDeviceFromSystem()
    {
        // Acquire a pointer to the current JavaVM
        JavaVM * jVM = CPlaytomicAndroid::GetJavaVM();
        if(jVM == NULL)
        {
            LOGI("please set the vm");
            return ;
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
                return;
            }
        }
        
        jclass cls_env = env->FindClass("android/os/Build");
        jfieldID fid = env->GetStaticFieldID(cls_env, "DEVICE",  "Ljava/lang/String;");
        jstring systemstr = (jstring)env->GetStaticObjectField(cls_env, fid);
        mDevice += "Device :";
        const char* device = env->GetStringUTFChars(systemstr, NULL);
        mDevice += device;
        env->ReleaseStringUTFChars(systemstr, device);
        mDevice += "\n";
        
        cls_env = env->FindClass("android/os/Build$VERSION");
        if(cls_env == NULL)
        {
            LOGI("failed to find version class ");
            return;
        }

        jfieldID sdk_version = env->GetStaticFieldID(cls_env, "SDK_INT", "I");
        if(sdk_version == NULL)
        {
            LOGI("invalid signature for sdk version field ");
            return;
        }
        jint systemsdk = env->GetStaticIntField(cls_env, sdk_version);
        
        char sdkversionstr[32];
        sprintf( sdkversionstr, "%d", systemsdk);
        mDevice += "SDK ID : ";
        mDevice += sdkversionstr;
        mDevice += "\n";
    }
}