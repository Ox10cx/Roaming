//
// Created by 龚喜 on 2022/3/19.
//

#include  "OsgMainApp.h"


COsgMainApp mainApp;

extern  "C"{
JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_init(JNIEnv*, jclass, jint, jint, jobject);
JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_step(JNIEnv *, jclass, jint, jint, jdouble ,jfloat, jfloat);
}

JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_init(JNIEnv* env, jclass args, jint width, jint height, jobject jObjModelViewMatrix)
{
    ModelViewMatrix initModelViewMatrix;

    jclass jClassModelViewMatrix= (env)->FindClass("com/model/roaming/element/ModelViewMatrix");
    jclass jClassVec4f          = (env)->FindClass("com/model/roaming/element/Vec4f");
    jclass jClassVec3f          = (env)->FindClass("com/model/roaming/element/Vec3f");

    jfieldID jfID = (env)->GetFieldID(jClassModelViewMatrix, "mMapRatio", "F");
    initModelViewMatrix.m_fMapRatio=(env)->GetFloatField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mCullRatio", "F");
    initModelViewMatrix.m_CullRatio=(env)->GetFloatField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mCameraModel", "I");
    initModelViewMatrix.m_CameraModel=(env)->GetIntField(jObjModelViewMatrix, jfID);

    //--透视投影--------------------------------
    osg::Vec4f  vPerspective;
    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mPerspective", "Lcom/model/roaming/element/Vec4f;");
    jobject jObjPerspective = (env)->GetObjectField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassVec4f, "x", "F");
    vPerspective._v[0] =(env)->GetFloatField(jObjPerspective, jfID);

    jfID = (env)->GetFieldID(jClassVec4f, "y", "F");
    vPerspective._v[1] =(env)->GetFloatField(jObjPerspective, jfID);

    jfID = (env)->GetFieldID(jClassVec4f, "z", "F");
    vPerspective._v[2] =(env)->GetFloatField(jObjPerspective, jfID);

    jfID = (env)->GetFieldID(jClassVec4f, "w", "F");
    vPerspective._v[3] =(env)->GetFloatField(jObjPerspective, jfID);

    initModelViewMatrix.m_vPerspective = vPerspective;
    //--透视投影--------------------------------

    //--摄像机--------------------------------
    osg::Vec3f  vCamera;
    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mCamera", "Lcom/model/roaming/element/Vec3f;");
    jobject jObjCamera = (env)->GetObjectField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "x", "F");
    vCamera._v[0] =(env)->GetFloatField(jObjCamera, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "y", "F");
    vCamera._v[1] =(env)->GetFloatField(jObjCamera, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "z", "F");
    vCamera._v[2] =(env)->GetFloatField(jObjCamera, jfID);

    initModelViewMatrix.m_vCamera = vCamera;
    //--摄像机--------------------------------

    //--观察点--------------------------------
    osg::Vec3f  vObserve;
    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mObserve", "Lcom/model/roaming/element/Vec3f;");
    jobject jObjObserve = (env)->GetObjectField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "x", "F");
    vObserve._v[0] =(env)->GetFloatField(jObjObserve, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "y", "F");
    vObserve._v[1] =(env)->GetFloatField(jObjObserve, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "z", "F");
    vObserve._v[2] =(env)->GetFloatField(jObjObserve, jfID);
    initModelViewMatrix.m_vObserve = vObserve;
    //--观察点--------------------------------

    //--UP分量--------------------------------
    LOGI("init up");
    osg::Vec3f  vUp;
    jfID = (env)->GetFieldID(jClassModelViewMatrix, "mUp", "Lcom/model/roaming/element/Vec3f;");
    jobject jObjUp = (env)->GetObjectField(jObjModelViewMatrix, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "x", "F");
    vUp._v[0] =(env)->GetFloatField(jObjUp, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "y", "F");
    vUp._v[1] =(env)->GetFloatField(jObjUp, jfID);

    jfID = (env)->GetFieldID(jClassVec3f, "z", "F");
    vUp._v[2] =(env)->GetFloatField(jObjUp, jfID);

    initModelViewMatrix.m_vUp = vUp;
    //--UP分量--------------------------------

    env->DeleteLocalRef(jClassModelViewMatrix);
    env->DeleteLocalRef(jClassVec4f);
    env->DeleteLocalRef(jClassVec3f);
    env->DeleteLocalRef(jObjPerspective);
    env->DeleteLocalRef(jObjObserve);
    env->DeleteLocalRef(jObjUp);
    //LOGI("init eye end: %f,%f, %f,%f", curViewMatrix._v[0], curViewMatrix._v[1], curViewMatrix._v[2] , curViewMatrix._v[3]);

    mainApp.InitOsgWindow(width, height, initModelViewMatrix);
}

JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_step(JNIEnv* env, jclass args, int centerX, int centerY ,double scale, float angle,float tile){
    mainApp.Draw(centerX, centerY, scale, angle, tile);
}
