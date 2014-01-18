package ru.vasil.justsnake;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toast;
import ru.vasil.justsnake.renderer.NativeRendererWrapper;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("justsnake");
    }

    private Handler handler;

    private GLSurfaceView glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityManager activityManager
                = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 = (configurationInfo != null && configurationInfo.reqGlEsVersion >= 0x20000)
                || isProbablyEmulator();

        setContentView(R.layout.activity_main);
        final TextView textView = (TextView) findViewById(R.id.info);
        textView.setText("Test");
        if (supportsEs2) {
//            glView = new GLSurfaceView(this);
            glView = (GLSurfaceView) findViewById(R.id.glView);

            if (isProbablyEmulator()) {
                // Avoids crashes on startup with some emulator images.
                glView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
            }

            glView.setEGLContextClientVersion(2);
            NativeRendererWrapper renderer = new NativeRendererWrapper();
            glView.setRenderer(renderer);
//            setContentView(glView);

            handler = new Handler() {
                @Override
                public void handleMessage(Message msg) {
                    textView.setText("" + msg.obj);
                }
            };
            renderer.setHandler(handler);
        } else {
            // Should never be seen in production, since the manifest filters
            // unsupported devices.
            Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
                    Toast.LENGTH_LONG).show();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        glView.onPause();
    }


    @Override
    protected void onResume() {
        super.onResume();
        glView.onResume();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        switch (item.getItemId()) {
            case R.id.action_settings:
                return true;
        }
        return super.onOptionsItemSelected(item);
    }


    private boolean isProbablyEmulator() {
        return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
                && (Build.FINGERPRINT.startsWith("generic")
                || Build.FINGERPRINT.startsWith("unknown")
                || Build.MODEL.contains("google_sdk")
                || Build.MODEL.contains("Emulator")
                || Build.MODEL.contains("Android SDK built for x86"));
    }
}
