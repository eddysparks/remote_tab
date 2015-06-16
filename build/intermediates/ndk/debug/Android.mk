LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := androidVideoExample
LOCAL_SRC_FILES := \
	/home/ekko/Appz/openFrameworks/examples/android/androidVideoExample/jni/Android.mk \
	/home/ekko/Appz/openFrameworks/examples/android/androidVideoExample/jni/Application.mk \

LOCAL_C_INCLUDES += /home/ekko/Appz/openFrameworks/examples/android/androidVideoExample/jni
LOCAL_C_INCLUDES += /home/ekko/Appz/openFrameworks/examples/android/androidVideoExample/src/debug/jni

include $(BUILD_SHARED_LIBRARY)
