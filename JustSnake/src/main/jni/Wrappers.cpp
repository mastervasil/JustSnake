#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
// #include "ru_vasil_justsnake_renderer_NativeRenderer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "justsnake", __VA_ARGS__))
#define NativeRenderer(n) Java_ru_vasil_justsnake_renderer_NativeRenderer_##n

extern "C" JNIEXPORT void JNICALL
Java_ru_vasil_justsnake_renderer_NativeRenderer_onCreateNative(
	JNIEnv* env, jobject obj )
{
	LOGI( "Natives created!!!" );
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onSurfaceCreated)(
	JNIEnv* env, jclass clazz, jobject obj)
{
	LOGI("onSurfaceCreated");
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onSurfaceChanged)(
	JNIEnv* env, jclass clazz, jobject obj, jint width, jint height)
{
	LOGI("onSurfaceChanged");
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onDrawFrame)(
	JNIEnv* env, jclass clazz, jobject obj)
{
	LOGI("onDrawFrame");
}