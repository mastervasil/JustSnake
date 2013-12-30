APP_OPTIM := release
APP_PLATFORM := android-8
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -DANDROID
APP_CFLAGS += -Wno-error=format-security
APP_ABI := armeabi armeabi-v7a x86 mips
# APP_ABI := armeabi-v7a
APP_MODULES := justsnake
NDK_TOOLCHAIN_VERSION := clang