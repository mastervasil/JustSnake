package ru.vasil.justsnake.renderer;

import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.os.Message;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author vasil
 */
public class NativeRendererWrapper implements GLSurfaceView.Renderer {
    private Handler handler;
    private float f = 0;

    public void setHandler(Handler info) {
        this.handler = info;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        NativeRenderer.onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeRenderer.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        f += 0.5;
        if (f >= 360) {
            f = 0;
        }
        if (handler != null && Math.abs(Math.round(f) - f) < 0.001) {
            Message msg = new Message();
            msg.obj = "" + Math.round(f);
            handler.sendMessage(msg);
        }
        NativeRenderer.onDrawFrame(f);
    }
}
