#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

// #include "ru_vasil_justsnake_renderer_NativeRenderer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "justsnake", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "justsnake", __VA_ARGS__))
#define NativeRenderer(n) Java_ru_vasil_justsnake_renderer_NativeRenderer_##n
#define NULL 0

static const char vertexShader[] = {
	"uniform mat4 u_MVPMatrix;        \n"                // A constant representing the combined model/view/projection matrix.
    "attribute vec4 a_Position;     \n"                // Per-vertex position information we will pass in.
    "attribute vec4 a_Color;        \n"                // Per-vertex color information we will pass in.
    "varying vec4 v_Color;          \n"                // This will be passed into the fragment shader.
    "void main()                    \n"                // The entry point for our vertex shader.
    "{                              \n"
    "   v_Color = a_Color;          \n"                // Pass the color through to the fragment shader.
    // It will be interpolated across the triangle.
    "   gl_Position = u_MVPMatrix   \n"         // gl_Position is a special variable used to store the const position.
    "               * a_Position;   \n"     // Multiply the vertex by the matrix to get the const point in
    "}                              \n"    // normalized screen coordinates.
};

static const char fragmentShader[] = {
	 "precision mediump float;       \n"                // Set the default precision to medium. We don't need as high of a
     // precision in the fragment shader.
     "varying vec4 v_Color;          \n"                // This is the color from the vertex shader interpolated across the
     // triangle per fragment.
     "void main()                    \n"                // The entry point for our fragment shader.
     "{                              \n"
     "   gl_FragColor = v_Color;     \n"                // Pass the color directly through the pipeline.
     "}                              \n"
 };

 GLint positionAttr;
 GLint colorAttr;


 static GLuint loadShader( GLenum type, const char* shaderSrc )
 {
    GLuint shader;
    GLint compiled;

 // Create the shader object
    shader = glCreateShader(type);
    if(shader == 0)
       return 0;
 // Load the shader source
   glShaderSource(shader, 1, &shaderSrc, NULL);

 // Compile the shader
   glCompileShader(shader);
 // Check the compile status
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
   if(!compiled) {
       GLint infoLen = 0;
       glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

       if(infoLen > 1) {
           char* infoLog = (char*) malloc(sizeof(char) * infoLen);
           glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
           // esLogMessage("Error compiling shader:\n%s\n", infoLog);
           LOGE( "Shader compilation failed: %s\n", infoLog );
           free(infoLog);
       }
       glDeleteShader(shader);
       return 0;
   }
   return shader;
}

static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader, const GLchar* arguments[], int size) {
  GLuint program = glCreateProgram();
  if (program != NULL) 
  {
     glAttachShader(program, vertexShader);
     glAttachShader(program, fragmentShader);
     for (int i = 0; i < size; i++) 
     {
        glBindAttribLocation(program, i, arguments[i]);
    }
    glLinkProgram(program);
    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(!linked) 
    {
     GLint infoLen = 0;
     glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

     if(infoLen > 1) 
     {
         char* infoLog = (char*) malloc(sizeof(char) * infoLen);
         glGetProgramInfoLog(program, infoLen, NULL, infoLog);
         LOGE("Error linking program:\n%s\n", infoLog);

         free(infoLog);
     }
     glDeleteProgram(program);
     return NULL;
    }
  }
  return program;
}

extern "C" JNIEXPORT void JNICALL
Java_ru_vasil_justsnake_renderer_NativeRenderer_onCreateNative(
  JNIEnv* env, jobject obj )
{
  LOGI( "Natives created!!!" );
}

float color[] = {1.0f, 0.0f, 0.0f, 0.0f};

void clearColor() {
  glClearColor(color[0], color[1], color[2], color[3]);
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
  JNIEnv* env, jclass clazz)
{
  LOGI("onSurfaceCreated");
 	// clearColor();
  glClearColor(0.5, 0.5, 0.5, 0.5);
  const float eyeX = 0.0f;
  const float eyeY = 0.0f;
  const float eyeZ = 1.5f;

        // // We are looking toward the distance
        // const float lookX = 0.0f;
        // const float lookY = 0.0f;
        // const float lookZ = -5.0f;

        // // Set our up vector. This is where our head would be pointing were we holding the camera.
        // const float upX = 0.0f;
        // const float upY = 1.0f;
        // const float upZ = 0.0f;
  glm::mat4 Projection = 
  glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f); 
  glm::mat4 ViewTranslate = glm::translate( 
    glm::mat4(1.0f), 
    glm::vec3(eyeX, eyeY, eyeZ)); 
  glm::mat4 ViewRotateX = glm::rotate( 
    ViewTranslate, 
    0.1f, glm::vec3(-1.0f, 0.0f, 0.0f)); 
  glm::mat4 View = glm::rotate( 
    ViewRotateX, 
    0.2f, glm::vec3(0.0f, 1.0f, 0.0f)); 
  glm::mat4 Model = glm::scale( 
    glm::mat4(1.0f), 
    glm::vec3(0.5f)); 
  glm::mat4 MVP = Projection * View * Model; 
    // glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(MVP)); 

  GLuint vertexShaderHandle = loadShader(GL_VERTEX_SHADER, vertexShader);
  GLuint fragmentShaderHandle = loadShader(GL_FRAGMENT_SHADER, fragmentShader);
  const GLchar* arguments[2] = {"a_Position", "a_Color"};
  GLuint program = createProgram(vertexShaderHandle, fragmentShaderHandle, arguments, 2);
  




        // Set the view matrix. This matrix can be said to represent the camera position.
        // NOTE: In OpenGL 1, a ModelView matrix is used, which is a combination of a model and
        // view matrix. In OpenGL 2, we can keep track of these matrices separately if we choose.


        // Matrix.setLookAtM(mViewMatrix, 0, eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onSurfaceChanged)(
  JNIEnv* env, jclass clazz, jint width, jint height)
{
  LOGI("onSurfaceChanged, %d, %d", width, height);
}

extern "C" JNIEXPORT void JNICALL
NativeRenderer(onDrawFrame)(
  JNIEnv* env, jclass clazz)
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