package ru.vasil.justsnake.renderer;

/**
 * @author vasil
 */
public class NativeRenderer {
    native static public void onSurfaceCreated();

    native static public void onSurfaceChanged(int width, int height);

    native static public void onDrawFrame(float f);
}
