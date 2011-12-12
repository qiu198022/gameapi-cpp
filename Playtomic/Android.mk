LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


LOCAL_MODULE    := Playtomic

MY_FILES := $(wildcard $(LOCAL_PATH)/Playtomic/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/CurlWrap/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/json/src/*.cpp)
MY_FILES += $(wildcard $(LOCAL_PATH)/Tools/*.cpp)
LOCAL_SRC_FILES += $(MY_FILES:$(LOCAL_PATH)/%=%) 

LOCAL_CFLAGS += -fexceptions
LOCAL_CFLAGS += -D__ARM_ARCH_5__
LOCAL_CFLAGS += -D__ANDROID__
#LOCAL_CFLAGS += -D_DEBUG_ANDROID_CONNECTION_


LOCAL_CFLAGS += -I$(LOCAL_PATH)/Dependencies/Android/Boost/ \
                -I$(LOCAL_PATH)/CurlWrap/ \
                -I$(LOCAL_PATH)/Tools/ \
                -I$(LOCAL_PATH)/json/include \
                -I$(LOCAL_PATH)/Dependencies/Android/curllib/include/ \
                -I$(LOCAL_PATH)/Playtomic/
                
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_LDLIBS += $(LOCAL_PATH)/Dependencies/Android/Boost/lib/libboost_thread.a \
                $(LOCAL_PATH)/Dependencies/Android/Boost/lib/libboost_date_time.a \
                $(LOCAL_PATH)/Dependencies/Android/curllib/lib/libcurl.a


include $(BUILD_SHARED_LIBRARY)

# $(ndk)/ndk-build NDK_APPLICATION_MK=./Application.mk