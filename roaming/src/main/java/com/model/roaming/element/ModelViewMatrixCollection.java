package com.model.roaming.element;

import android.util.Log;

import java.util.ArrayList;

/**
 * 存放OSG模型视角矩阵的集合
 *
 * @author xi.gong
 */
public class ModelViewMatrixCollection {
    private static ModelViewMatrixCollection mViewMatrixCollection;
    /**
     * 漫游视角矩阵集合
     */
    private ArrayList<ModelViewMatrix> mRoamViewMatrixArrayList;
    /**
     * 导航视角矩阵集合
     */
    private ArrayList<ModelViewMatrix>  mNaviViewMatrixArrayList;
    /**
     * 初始化视角矩阵集合
     */
    private ArrayList<ModelViewMatrix> mInitViewMatrixArrayList;
    /**
     * 当前传下去的OsgView的Matrix
     */
    private ModelViewMatrix            mCurrentViewMatrix;


    private float mOsgAngel;
    private float mOsgMapRatio;
    private float mCullRatio;

    /**
     * 获取视图模型的视角
     * @return
     */
    public static ModelViewMatrixCollection getViewMatrixCollection() {

        if (mViewMatrixCollection == null) {
            mViewMatrixCollection = new ModelViewMatrixCollection();
        }
        return mViewMatrixCollection;
    }

    /**
     * 设置OSG视图模型视角矩阵
     * @param width  屏幕的宽度
     * @param height
     */
    public void setModelViewMatrix(int width,int height) {
        mRoamViewMatrixArrayList =new ArrayList<>();
        mNaviViewMatrixArrayList     =new ArrayList<>();
        mInitViewMatrixArrayList =new ArrayList<>();

        mOsgAngel       =0.0f;
        mOsgMapRatio    =0.0f;
        mCullRatio      =0.0f;

        //------------------------------初始化视角-------------------------------//

        int mScreenWidth   = width;
        int mScreenHeight  = height;

        Log.d("setModelViewMatrix","setModelViewMatrix"+mScreenWidth+"--"+mScreenHeight);

        float asPect = (float) width/(float) height;

        //m_pScreenParam->m_fHdMapRatio
        float maxSide = 1.0f;

        //2D模式下的视角
        mOsgAngel      = 60.0f;


        Vec4f vPerspective2D  = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
        Vec3f vCamera2D       = new Vec3f(0.0f,1.732f * maxSide,0.0f);
        Vec3f vObserve2D      = new Vec3f(0.0f,0.0f,0.0f);
        Vec3f vUp2D           = new Vec3f(0.0f, 0.0f, 1.0f);
        mOsgMapRatio          = maxSide;

        float angel2D         = (float) (Math.atan(Math.abs(vCamera2D.getZ()/vCamera2D.getY()))*180.0f/Math.PI-mOsgAngel/2);
        mCullRatio            = (float) (Math.tan(angel2D*Math.PI/180) * vCamera2D.getY());
        Log.d("2D--","mCullRatio"+mCullRatio+"---"+"mOsgMapRatio"+mOsgMapRatio);

        ModelViewMatrix modelViewMatrix2D = new ModelViewMatrix(vPerspective2D,vCamera2D,vObserve2D,vUp2D,mOsgMapRatio,mCullRatio, CameraModel.CAMERA2D.ordinal());
        mInitViewMatrixArrayList.add(0,modelViewMatrix2D);

        setCurrentViewMatrix(modelViewMatrix2D);

        //m_pScreenParam->m_fHdMapRatio
        maxSide = (float) Math.max(mScreenWidth * 1.1 * 2.0, mScreenHeight  * 1.1 * 1.5) / mScreenHeight;
        //3D模式下的视角
        mOsgAngel      = 60.0f;

        Vec4f vPerspective3D = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
        Vec3f vCamera3D      = new Vec3f(0.0f,0.6f,-2.5f);
        Vec3f vObserve3D     = new Vec3f(0.0f,0.1f,0.0f);
        Vec3f vUp3D          = new Vec3f(0.0f,1.0f,0.0f);
        mOsgMapRatio           = maxSide;

        float angel3D        =0.0f;
        if(vCamera3D.getY()==vObserve3D.getY()) {
            mCullRatio         =(float) (vCamera3D.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCamera3D.getZ());
        }else {
            angel3D            =(float)(Math.atan(Math.abs(vCamera3D.getZ())/(Math.abs(vCamera3D.getY()-vObserve3D.getY())))*180.0f/Math.PI-mOsgAngel/2);
            mCullRatio         =(float)(vCamera3D.getY()*Math.tan(angel3D*Math.PI/180)+vCamera3D.getZ());
            mOsgMapRatio       =(float)(vCamera3D.getY()*Math.tan((angel3D+mOsgAngel/2)*Math.PI/180))-
                    (float)(vCamera3D.getY()*Math.tan(angel3D*Math.PI/180));
        }

        ModelViewMatrix modelViewMatrix3D = new ModelViewMatrix(vPerspective3D,vCamera3D,vObserve3D,vUp3D,mOsgMapRatio,mCullRatio,CameraModel.CAMERA3D.ordinal());
        mInitViewMatrixArrayList.add(1,modelViewMatrix3D);




        //----------------------------------漫游---------------------------------//

        //设置漫游室内视角
        maxSide = (float) Math.max(mScreenWidth * 1.1 * 2.0, mScreenHeight  * 1.1 * 1.5) / mScreenHeight;
        mOsgAngel= 60.0f;

        Vec4f vPerspectiveRoamIn   = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
        Vec3f vCameraRoamIn        = new Vec3f(0.0f,0.15f,-0.2f);
        Vec3f vObserveRoamIn       = new Vec3f(0.0f,0.15f,0.0f);
        Vec3f vUpRoamIn            = new Vec3f(0.0f,1.0f,0.0f);

        mOsgMapRatio               = maxSide;

        float angelRoamIn          =0.0f;
        if(vCameraRoamIn.getY()==vObserveRoamIn.getY()) {
            mCullRatio         =(float) (vCameraRoamIn.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCameraRoamIn.getZ());
            Log.i("angelRoamIn","mCullRatio--D"+mCullRatio);

        }else {
            angelRoamIn        =(float)(Math.atan(Math.abs(vCameraRoamIn.getZ())/(Math.abs(vCameraRoamIn.getY()-vObserveRoamIn.getY())))*180.0f/Math.PI-mOsgAngel/2);
            mCullRatio         =(float)(vCameraRoamIn.getY()*Math.tan(angelRoamIn*Math.PI/180)+vCameraRoamIn.getZ());
        }

        ModelViewMatrix roamViewMatrixInDoor = new ModelViewMatrix(vPerspectiveRoamIn,vCameraRoamIn,vObserveRoamIn,vUpRoamIn,mOsgMapRatio,mCullRatio,CameraModel.CAMERAROVEINDOOR.ordinal());
        mRoamViewMatrixArrayList.add(0,roamViewMatrixInDoor);

        //设置漫游室外
        maxSide = (float) Math.max(mScreenWidth * 1.1 * 2.0, mScreenHeight  * 1.1 * 1.5)/ mScreenHeight;

        mOsgAngel = 60.0f;
        Vec4f vPerspectiveRoamOut   = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
        Vec3f vCameraRoamOut        = new Vec3f(0.0f,1.3f,-1.8f);
        Vec3f vObserveRoamOut       = new Vec3f(0.0f,0.1f,0.0f);
        Vec3f vUpRoamOut            = new Vec3f(0.0f,1.0f,0.0f);
        mOsgMapRatio                = maxSide;

        float angelRoamOut          = 0.0f;
        if(vCameraRoamOut.getY()==vObserveRoamOut.getY()) {
            mCullRatio              =(float) (vCameraRoamOut.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCameraRoamOut.getZ());
        }else {
            angelRoamOut            =(float)(Math.atan(Math.abs(vCameraRoamOut.getZ())/(Math.abs(vCameraRoamOut.getY()-vObserveRoamOut.getY())))*180.0f/Math.PI-mOsgAngel/2);
            mCullRatio              =(float)(vCameraRoamOut.getY()*Math.tan(angelRoamOut*Math.PI/180)+vCameraRoamOut.getZ());
            mOsgMapRatio            =(float)(vCameraRoamOut.getY()*Math.tan((angelRoamOut+mOsgAngel/2)*Math.PI/180))-
                    (float)(vCameraRoamOut.getY()*Math.tan(angelRoamOut*Math.PI/180));
        }

        ModelViewMatrix roamViewMatrixOutDoor = new ModelViewMatrix(vPerspectiveRoamOut,vCameraRoamOut,vObserveRoamOut,vUpRoamOut,mOsgMapRatio,mCullRatio,CameraModel.CAMERAROVEOUTDOOR.ordinal());
        mRoamViewMatrixArrayList.add(1,roamViewMatrixOutDoor);
        //---------------------------导航---------------------------------------------//
        maxSide = (float) Math.max(mScreenWidth * 1.1 * 2.0, mScreenHeight  * 1.1 * 1.5) / mScreenHeight;
        //设置导航室内
        mOsgAngel=90.0f;

        Vec4f vPerspectiveNaviIn     = new Vec4f(mOsgAngel,asPect,0.01f,10.0f);
        Vec3f vCameraNaviIn          = new Vec3f(0.0f,0.15f,-0.12f);
        Vec3f vObserveNaviIn         = new Vec3f(0.0f,0.15f,0.0f);
        Vec3f vUpNaviIn          = new Vec3f(0.0f,1.0f,0.0f);
        mOsgMapRatio                 = maxSide;

        float angelNaviIn            =0.0f;
        if(vCameraNaviIn.getY()==vObserveNaviIn.getY()) {
            mCullRatio               =(float) (vCameraNaviIn.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCameraNaviIn.getZ());
        }else {
            angelNaviIn             =(float)(Math.atan(Math.abs(vCameraNaviIn.getZ())/(Math.abs(vCameraNaviIn.getY()-vObserveNaviIn.getY())))*180.0f/Math.PI-mOsgAngel/2);
            mCullRatio              =(float)(vCameraNaviIn.getY()*Math.tan(angelNaviIn*Math.PI/180)+vCameraNaviIn.getZ());
        }

        ModelViewMatrix naviViewMatrixInDoor = new ModelViewMatrix(vPerspectiveNaviIn,vCameraNaviIn,vObserveNaviIn,vUpNaviIn,mOsgMapRatio,mCullRatio,CameraModel.CAMERANAVIINDOOR.ordinal());
        mNaviViewMatrixArrayList.add(0,naviViewMatrixInDoor);



        //设置导航室外
//        mOsgAngel = 60.0f;
//
//        Vec4f vPerspectiveNaviOut     = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
//        Vec3f vCameraNaviOut          = new Vec3f(0.0f,0.7f,-0.8f);
//        Vec3f vObserveNaviOut         = new Vec3f(0.0f,0.1f,0.0f);
//        Vec3f vUpRoamNaviOut          = new Vec3f(0.0f,1.0f,0.0f);
//        mOsgMapRatio                  = maxSide;
//
//        float angelNaviOut            = 0.0f;
//        if(vCameraNaviOut.getY()==vObserveNaviOut.getY()) {
//            mCullRatio               =(float) (vCameraNaviOut.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCameraNaviOut.getZ());
//        }else {
//            angelNaviOut             =(float)(Math.atan(Math.abs(vCameraNaviOut.getZ())/(Math.abs(vCameraNaviOut.getY()-vObserveNaviOut.getY())))*180.0f/Math.PI-mOsgAngel/2);
//            mCullRatio               =(float)(vCameraNaviOut.getY()*Math.tan(angelNaviOut*Math.PI/180)+vCameraNaviOut.getZ());
//        }
//
//        ModelViewMatrix naviViewMatrixOutDoor = new ModelViewMatrix(vPerspectiveNaviOut,vCameraNaviOut,vObserveNaviOut,vUpRoamNaviOut,mOsgMapRatio,mCullRatio);
//        mNaviViewMatrixArrayList.add(1,naviViewMatrixOutDoor);


        mOsgAngel = 60.0f;
        Vec4f vPerspectiveNaviOut       = new Vec4f(mOsgAngel,asPect,0.1f,10.0f);
        Vec3f vCameraNaviOut            = new Vec3f(0.0f,1.0f,-2.5f);
        Vec3f vObserveNaviOut           = new Vec3f(0.0f,0.1f,0.0f);
        Vec3f vUpNaviOut            = new Vec3f(0.0f,1.0f,0.0f);
        mOsgMapRatio                    = maxSide;

        float angelNaviOut          = 0.0f;
        if(vCameraNaviOut.getY()==vObserveNaviOut.getY()) {
            mCullRatio              =(float) (vCameraNaviOut.getY()*Math.tan((90-mOsgAngel/2.0)*Math.PI/180)+vCameraNaviOut.getZ());
        }else {
            angelNaviOut            =(float)(Math.atan(Math.abs(vCameraNaviOut.getZ())/(Math.abs(vCameraNaviOut.getY()-vObserveNaviOut.getY())))*180.0f/Math.PI-mOsgAngel/2);
            mCullRatio              =(float)(vCameraNaviOut.getY()*Math.tan(angelNaviOut*Math.PI/180)+vCameraNaviOut.getZ());
            mOsgMapRatio            =(float)(vCameraNaviOut.getY()*Math.tan((angelNaviOut+mOsgAngel/2)*Math.PI/180))-
                    (float)(vCameraNaviOut.getY()*Math.tan(angelNaviOut*Math.PI/180));
        }

        ModelViewMatrix naviViewMatrixOutDoor = new ModelViewMatrix(vPerspectiveNaviOut,vCameraNaviOut,vObserveNaviOut,vUpNaviOut,mOsgMapRatio,mCullRatio,CameraModel.CAMERANAVIOUTDOOR.ordinal());
        mNaviViewMatrixArrayList.add(1,naviViewMatrixOutDoor);
    }

    public ArrayList<ModelViewMatrix> getInitViewMatixArrayList()
    {
        return mInitViewMatrixArrayList;
    }

    public ArrayList<ModelViewMatrix> getNaviViewMatrixArrayList()
    {
        return  mNaviViewMatrixArrayList;
    }

    public ArrayList<ModelViewMatrix> getRoamViewMatixArrayList()
    {
        return mRoamViewMatrixArrayList;
    }

    /**
     * 设置当前传入Osg模型的矩阵
     * @param currentZoomRoamViewMatrix
     */
    public void setCurrentViewMatrix(ModelViewMatrix currentZoomRoamViewMatrix){
        this.mCurrentViewMatrix = currentZoomRoamViewMatrix;
    }

    /**
     * 获取当前传入Osg的模型矩阵
     * @return
     */
    public ModelViewMatrix getCurrentViewMatrix(){
        return  mCurrentViewMatrix;
    }
}
