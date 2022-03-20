package com.model.roaming.element;

/**
 * OSG模型视角矩阵
 */
public class ModelViewMatrix {
    /**
     * 透视投影
     */
    private Vec4f mPerspective;
    /**
     * 摄像机
     */
    private Vec3f mCamera;
    /**
     * 观察点
     */
    private Vec3f mObserve;
    /**
     * 坐标轴的分量
     */
    private Vec3f mUp;
    /**
     * 地图的长宽对应的OSG三维坐标系
     */
    private float mMapRatio;
    private float mCullRatio;

    private int mCameraModel;

    public ModelViewMatrix() {
    }

    public ModelViewMatrix(Vec4f mPerspective, Vec3f mCamera, Vec3f mObserve, Vec3f mUp, float mMapRatio, float mCullRatio,int cameraModel) {
        this.mPerspective = mPerspective;
        this.mCamera = mCamera;
        this.mObserve = mObserve;
        this.mUp = mUp;
        this.mMapRatio = mMapRatio;
        this.mCullRatio = mCullRatio;
        this.mCameraModel = cameraModel;
    }

    public ModelViewMatrix(ModelViewMatrix modelViewMatrix){
        this.mPerspective = new Vec4f(modelViewMatrix.getPerspective().getX(),modelViewMatrix.getPerspective().getY(),modelViewMatrix.getPerspective().getZ(),modelViewMatrix.getPerspective().getW());
        this.mCamera      = new Vec3f(modelViewMatrix.getCamera().getX(),modelViewMatrix.getCamera().getY(),modelViewMatrix.getCamera().getZ());
        this.mObserve     = new Vec3f(modelViewMatrix.getObserve().getX(),modelViewMatrix.getObserve().getY(),modelViewMatrix.getObserve().getZ());
        this.mUp          = new Vec3f(modelViewMatrix.getUp().getX(),modelViewMatrix.getUp().getY(),modelViewMatrix.getUp().getZ());
        this.mCullRatio   = modelViewMatrix.getCullRatio();
        this.mMapRatio    = modelViewMatrix.getMapRatio();
        this.mCameraModel = modelViewMatrix.getCameraModel();
    }

    public Vec4f getPerspective() {
        return mPerspective;
    }

    public void setPerspective(Vec4f mPerspective) {
        this.mPerspective.setX(mPerspective.getX());
        this.mPerspective.setY(mPerspective.getY());
        this.mPerspective.setZ(mPerspective.getZ());
        this.mPerspective.setW(mPerspective.getW());
    }

    public Vec3f getCamera() {
        return mCamera;
    }

    public void setCamera(Vec3f mCamera) {
        this.mCamera.setX(mCamera.getX());
        this.mCamera.setY(mCamera.getY());
        this.mCamera.setZ(mCamera.getZ());
    }

    public Vec3f getObserve() {
        return mObserve;
    }

    public void setObserve(Vec3f mObserve) {
        this.mObserve.setX(mObserve.getX());
        this.mObserve.setY(mObserve.getY());
        this.mObserve.setZ(mObserve.getZ());
    }

    public Vec3f getUp() {
        return mUp;
    }

    public void setUp(Vec3f mUp) {
        this.mUp = mUp;
    }

    public float getMapRatio() {
        return mMapRatio;
    }

    public void setMapRatio(float mMapRatio) {
        this.mMapRatio = mMapRatio;
    }

    public float getCullRatio() {
        return mCullRatio;
    }

    public void setCullRatio(float mCullRatio) {
        this.mCullRatio = mCullRatio;
    }

    public int getCameraModel(){return mCameraModel;}

    public void setCameraModel(int cameraModel){this.mCameraModel = cameraModel;}

    @Override
    public String toString() {
        return "ModelViewMatrix{" +
                "mPerspective=" + mPerspective +
                ", mCamera=" + mCamera +
                ", mObserve=" + mObserve +
                ", mUp=" + mUp +
                ", mMapRatio=" + mMapRatio +
                ", mCullRatio=" + mCullRatio +
                ", mCameraModel"+mCameraModel+
                '}';
    }

    /**
     * 判断两个对象的值是否相等
     * @param modelViewMatrix
     * @return
     */
    public boolean equals(ModelViewMatrix  modelViewMatrix) {
        if(this.mMapRatio == modelViewMatrix.getMapRatio()&&
                this.mCullRatio== modelViewMatrix.getCullRatio()&&
                this.mPerspective.equals(modelViewMatrix.getPerspective())&&
                this.mCamera.equals(modelViewMatrix.getCamera())&&
                this.mObserve.equals(modelViewMatrix.getObserve())&&
                this.mUp.equals(modelViewMatrix.getUp())&&
                this.mCameraModel == modelViewMatrix.getCameraModel())
        {
            return true;
        }else {
            return false;
        }
    }

}
