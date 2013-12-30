#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include <GLES2/gl2.h>
// #include "ru_vasil_justsnake_renderer_NativeRenderer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "justsnake", __VA_ARGS__))
#define NativeRenderer(n) Java_ru_vasil_justsnake_renderer_NativeRenderer_##n

extern "C" JNIEXPORT void JNICALL
Java_ru_vasil_justsnake_renderer_NativeRenderer_onCreateNative(
	JNIEnv* env, jobject obj )
{
	LOGI( "Natives created!!!" );
}

float color[] = {1.0f, 0.0f, 0.0f, 0.0f};

void clearColor() {
	glClearColor(color[0], color[1], color[2], color[3]);
	// glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
}

std::string intToStr( int FromUInt32 )
{
        char buf[64];

        snprintf( buf, 63, "%i", FromUInt32 );

        return std::string( buf );
}

std::string floatToStr(float f) {
	char buf[64];
	snprintf(buf, 63, "%f", f);
	return std::string(buf);
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onSurfaceCreated)(
	JNIEnv* env, jclass clazz, jobject obj)
{
	LOGI("onSurfaceCreated");
	clearColor();
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
	LOGI("NEW VALUE: %f", color[0]);
	if (color[0] < 1.0f) {
		color[0] += 0.01f;
	} else {
		color[0] = 0.0f;
	}
	clearColor();
	glClear(GL_COLOR_BUFFER_BIT);

}