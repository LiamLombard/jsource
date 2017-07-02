
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jnative
LOCAL_MODULE_FILENAME    := libjnative

LOCAL_LDLIBS := 

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
  LOCAL_CFLAGS := -fPIC -O1 -fwrapv -Werror -fno-strict-aliasing -march=armv8-a
  LOCAL_ARM_NEON := true
endif
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
  LOCAL_CFLAGS := -fPIC -O1 -fwrapv -Werror -fno-strict-aliasing -mfloat-abi=softfp -mfpu=vfpv3-d16 -march=armv7-a
  LOCAL_ARM_MODE := arm
endif
ifeq ($(TARGET_ARCH_ABI),armeabi)
  LOCAL_CFLAGS := -fPIC -Os -fwrapv -Werror -fno-strict-aliasing -mfloat-abi=softfp -march=armv5te
  LOCAL_ARM_MODE := arm
endif
ifeq ($(TARGET_ARCH),x86_64)
  LOCAL_CFLAGS := -fPIC -O1 -fwrapv -Werror -fno-strict-aliasing -march=x86-64 -mtune=intel -msse4.2 -mpopcnt -fno-stack-protector
endif
ifeq ($(TARGET_ARCH),x86)
  LOCAL_CFLAGS := -fPIC -O1 -fwrapv -Werror -fno-strict-aliasing -march=i686 -mtune=intel -mssse3 -mfpmath=sse -fno-stack-protector
endif

LOCAL_SRC_FILES := andjnative.c jeload.c
LOCAL_LDLIBS := -ldl -llog

include $(BUILD_SHARED_LIBRARY)
