package com.model.roaming;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.model.roaming.element.ModelViewMatrix;
import com.model.roaming.element.ModelViewMatrixCollection;
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

    /**
     * 设置地图显示模式：0-2D地图向上；1-2.5D；3-3D
     */
    public void setMapViewModelLocked(int width, int height) {
        ModelViewMatrixCollection.getViewMatrixCollection().setModelViewMatrix(width, height);
        ModelViewMatrix modelViewMatrix2D = ModelViewMatrixCollection.getViewMatrixCollection().getInitViewMatixArrayList().get(0);
        RoamingNative.init(width, height, modelViewMatrix2D);
    }


    private class SceneRenderer implements GLSurfaceView.Renderer {
        @Override
        public void onDrawFrame(GL10 gl) {
            RoamingNative.step(0, 0, 1.0, 0, 0);
            Log.i(TAG, "----onDrawFrame exit");
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            setMapViewModelLocked(width, height);
            Log.d(TAG,"--onSurfaceChanged---End");

        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            Log.d(TAG,"Test ---------onSurfaceCreated-------------");
        }
    }
}
