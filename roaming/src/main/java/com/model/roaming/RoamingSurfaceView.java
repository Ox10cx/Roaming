package com.model.roaming;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.model.roaming.jni.RoamingNative;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class RoamingSurfaceView extends GLSurfaceView {
    private static final String TAG = RoamingSurfaceView.class.getCanonicalName();
    /**
     * 场景渲染器
     */
    private SceneRenderer mRenderer;

    public RoamingSurfaceView(Context context) {
        this(context, null);
    }

    public RoamingSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        //设置使用OPENGL ES2.0
        this.setEGLContextClientVersion(2);
        //创建场景渲染器
        mRenderer = new SceneRenderer();
        //设置渲染器
        setRenderer(mRenderer);
        //设置渲染模式为主动渲染
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }


    private class SceneRenderer implements GLSurfaceView.Renderer {
        @Override
        public void onDrawFrame(GL10 gl) {
            RoamingNative.step();
            Log.i(TAG, "----onDrawFrame exit ");
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            RoamingNative.init(width, height);
            Log.d(TAG,"--onSurfaceChanged---End");

        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            Log.d(TAG,"Test ---------onSurfaceCreated-------------");
        }
    }
}
