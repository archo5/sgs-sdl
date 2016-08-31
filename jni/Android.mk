
LOCAL_PATH := $(call my-dir)


# Box2D
include $(CLEAR_VARS)
LOCAL_MODULE := box2d
LOCAL_CFLAGS := -std=c++11
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../ext/src/box2d/Box2D
LOCAL_SRC_FILES := ../ext/src/box2d1.cpp
include $(BUILD_STATIC_LIBRARY)

# sgs-Box2D
include $(CLEAR_VARS)
LOCAL_MODULE := sgsbox2d
LOCAL_CFLAGS := -DSGS_COMPILE_MODULE=1
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../sgscript/src $(LOCAL_PATH)/../ext/src/box2d/Box2D
LOCAL_SRC_FILES := ../src/box2d.cpp ../src/cppbc_box2d.cpp
LOCAL_STATIC_LIBRARIES := box2d
LOCAL_SHARED_LIBRARIES := sgscript sgsxgmath
include $(BUILD_SHARED_LIBRARY)


# SGScript
include ../sgscript/jni/Android.mk
