
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


# Ogg
LIBOGG_ROOT := ../ext/src/libogg-1.3.1
include $(CLEAR_VARS)
LOCAL_MODULE := ogg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(LIBOGG_ROOT)/include
LOCAL_SRC_FILES := $(LIBOGG_ROOT)/src/bitwise.c $(LIBOGG_ROOT)/src/framing.c
include $(BUILD_STATIC_LIBRARY)

# Vorbis
LIBVORBIS_ROOT := ../ext/src/libvorbis-1.3.3
_LIBVORBIS_SRCNAMES := analysis bitrate block codebook envelope \
	floor0 floor1 info lookup lpc lsp mapping0 mdct psy \
	registry res0 sharedbook smallft synthesis vorbisenc vorbisfile window
include $(CLEAR_VARS)
LOCAL_MODULE := vorbis
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(LIBOGG_ROOT)/include $(LOCAL_PATH)/$(LIBVORBIS_ROOT)/include $(LOCAL_PATH)/$(LIBVORBIS_ROOT)/lib
LOCAL_SRC_FILES := $(patsubst %,$(LIBVORBIS_ROOT)/lib/%.c,$(_LIBVORBIS_SRCNAMES))
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := oggvorbistest
LOCAL_STATIC_LIBRARIES := ogg vorbis
include $(BUILD_SHARED_LIBRARY)


# SGScript
include ../sgscript/jni/Android.mk
