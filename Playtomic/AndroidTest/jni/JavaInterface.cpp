


#include <jni.h>
#include "PlaytomicDemo.h"
#include <android/log.h>
#include "JavaInterface.h"
#define  LOG_TAG    "playtomicTest"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

CPlaytomicDemo* instance = NULL;

jobject gThiz  = NULL;
jclass gPlaytomicActivity = NULL;
JavaVM* g_jvm = 0;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void * reserved)
{
    g_jvm = vm;

    return JNI_VERSION_1_6;
}

extern "C" {
void Java_playtomic_cpp_PlaytomicActivity_initCpp( JNIEnv* env, jobject thiz )
{
	gThiz = env->NewGlobalRef(thiz);
	gPlaytomicActivity = (jclass) env->NewGlobalRef(env->FindClass("playtomic/cpp/PlaytomicActivity"));

	if(instance == NULL)
	{
		std::string guid("9f3f3b43cb234025");
    	instance = new CPlaytomicDemo(4603, guid,true);
    }
	instance->LogView();
}


void Java_playtomic_cpp_PlaytomicActivity_logPlay( JNIEnv* env, jobject thiz )
{
	LOGI("try to Log play");
	if(instance !=NULL)
	{
		instance->LogPlay();
	}
	else
	{
		LOGI("Instance is null!");
	}
}

void Java_playtomic_cpp_PlaytomicActivity_logCustomMetric( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->LogCustomMetric();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_logLevelAverageMetric( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->LogAverageMetric();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_logLevelCounterMetric( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->LogCounterMetric();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_logLevelRangedMetric( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
	}
}

void Java_playtomic_cpp_PlaytomicActivity_loadGameVars( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->GetGameVars();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_geoip( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->GetLocation();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_leaderboardSave(JNIEnv* env, jobject thiz)
{
	if(instance != NULL)
	{
		instance->SaveScore();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_leaderboardList(JNIEnv* env, jobject thiz)
{
	if(instance != NULL)
	{
		instance->ListScores();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_leaderboardSaveAndList( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->SaveAndListScore();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_privateLeaderboardSave( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
	}
}

void Java_playtomic_cpp_PlaytomicActivity_LeaderboardLoad( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
	}
}

void Java_playtomic_cpp_PlaytomicActivity_levelSave( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->SaveLevel();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_levelList( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->ListLevels();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_levelLoad( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->LoadLevel();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_levelRate( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->RateLevel();
	}
}
void Java_playtomic_cpp_PlaytomicActivity_loadPlays( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->GetPlays();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_loadPlaytime( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->GetPlayTime();
	}
}

void Java_playtomic_cpp_PlaytomicActivity_loadViews( JNIEnv* env, jobject thiz )
{
	if(instance !=NULL)
	{
		instance->GetViews();
	}
}
}

void PostString(const char *string)
{
	JNIEnv* env = 0;
	int status = g_jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	bool dettachProcess = false;
	if(status < 0)
	{
		dettachProcess = true;
		LOGI("Failed to get JNI environment, assuming native thread");
	    status = g_jvm->AttachCurrentThread(&env, NULL);
	    if(status < 0)
	    {
	    	LOGI("callback_handler: failed to attach current thread");
	        return;
	    }
	}
	jstring jstr = env->NewStringUTF(string);

	jmethodID printLog = env->GetMethodID(gPlaytomicActivity, "printLog", "(Ljava/lang/String;)V");

	LOGI("post string %s", string);
	env->CallVoidMethod(gThiz, printLog, jstr);
	if(dettachProcess)
	{
		g_jvm->DetachCurrentThread();
	}
}
