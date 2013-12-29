TARGET_PLATFORM := android-8
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
LOCAL_MODULE     := justsnake
LOCAL_SRC_FILES += Wrappers.cpp
LOCAL_ARM_MODE := arm
COMMON_CFLAGS := -Werror -DANDROID -DDISABLE_IMPORTGL \
-isystem $(SYSROOT)/usr/include/
ifeq ($(TARGET_ARCH),x86)
  LOCAL_CFLAGS   := $(COMMON_CFLAGS)
else
  ifeq ($(TARGET_ARCH),mips)
    LOCAL_CFLAGS   := -fno-short-enums $(COMMON_CFLAGS)
  else
    LOCAL_CFLAGS   := -mfpu=vfp -mfloat-abi=softfp \
    -fno-short-enums $(COMMON_CFLAGS)
    endif
endif
LOCAL_LDLIBS     := -llog -lGLESv2 -Wl,-s
LOCAL_CPPFLAGS += -std=gnu++0x
include $(BUILD_SHARED_LIBRARY)