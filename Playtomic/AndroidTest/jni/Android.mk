LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
PLAYTOMIC_PATH := ../../prebuilt/android#$(LOCAL_PATH)/../..
LOCAL_MODULE := Playtomic-prebuilt
LOCAL_SRC_FILES := $(PLAYTOMIC_PATH)/libs/$(TARGET_ARCH_ABI)/libPlaytomic.so
include $(PREBUILT_SHARED_LIBRARY)


#LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
#LOCAL_PATH := $(call my-dir)

LOCAL_MODULE    := PlaytomicDemo

#MY_FILES := $(wildcard $(LOCAL_PATH)/*.cpp)
#LOCAL_SRC_FILES := $(MY_FILES:$(LOCAL_PATH)/%=%) 

LOCAL_SRC_FILES := JavaInterface.cpp PlaytomicDemo.cpp

LOCAL_CFLAGS += -fexceptions
LOCAL_CFLAGS += -D__ARM_ARCH_5__
LOCAL_CFLAGS += -D__ANDROID__
#LOCAL_CFLAGS += -D__BOOST_HACK__

PLAYTOMIC_PATH := ../../prebuilt/android#$(LOCAL_PATH)/../..
$(call ndk_log,playtomic path : $(PLAYTOMIC_PATH))
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(PLAYTOMIC_PATH)/Dependencies/Android/Boost/ \
					$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/CurlWrap/ \
					$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/Tools/ \
					$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/json/include \
					$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/Dependencies/Android/curllib/include/ \
					$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/Playtomic/ \
                	$(LOCAL_PATH)/$(PLAYTOMIC_PATH)/

#LOCAL_CPPFLAGS += $(LOCAL_CFLAGS)
$(call ndk_log,c inlcudes : $(LOCAL_C_INCLUDES))               
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_SHARED_LIBRARIES := Playtomic-prebuilt

include $(BUILD_SHARED_LIBRARY)
