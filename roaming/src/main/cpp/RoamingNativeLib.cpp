//
// Created by 龚喜 on 2022/3/19.
//


#include  "OsgMainApp.h"

#define LOG_TAG  "RoamingNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

jclass jClassModelViewMatrix = nullptr;
jclass jClassVec4f = nullptr;
jclass jClassVec3f = nullptr;

jfieldID jModelViewMatrixMapRatioField = nullptr;
jfieldID jModelViewMatrixCullRatioField = nullptr;
jfieldID jModelViewMatrixCameraModelField = nullptr;

jfieldID jModelViewMatrixPerspectiveField = nullptr;
jfieldID jModelViewMatrixCameraField = nullptr;
jfieldID jModelViewMatrixObserveField = nullptr;
jfieldID jModelViewMatrixUpField = nullptr;

jfieldID jVec4fXField = nullptr;
jfieldID jVec4fYField = nullptr;
jfieldID jVec4fZField = nullptr;
jfieldID jVec4fWField = nullptr;

jfieldID jVec3fXField = nullptr;
jfieldID jVec3fYField = nullptr;
jfieldID jVec3fZField = nullptr;

COsgMainApp mainApp;

static void InitOsgWindow(JNIEnv* env, jobject object, jint width, jint height, jobject jObjModelViewMatrix) {

    ModelViewMatrix initModelViewMatrix;
    initModelViewMatrix.m_fMapRatio=(env)->GetFloatField(jObjModelViewMatrix, jModelViewMatrixMapRatioField);
    initModelViewMatrix.m_CullRatio=(env)->GetFloatField(jObjModelViewMatrix, jModelViewMatrixCullRatioField);
    initModelViewMatrix.m_CameraModel=(env)->GetIntField(jObjModelViewMatrix, jModelViewMatrixCameraModelField);

    //--透视投影--------------------------------
    osg::Vec4f  vPerspective;
    jobject jObjPerspective = (env)->GetObjectField(jObjModelViewMatrix, jModelViewMatrixPerspectiveField);
    vPerspective._v[0] =(env)->GetFloatField(jObjPerspective, jVec4fXField);
    vPerspective._v[1] =(env)->GetFloatField(jObjPerspective, jVec4fYField);
    vPerspective._v[2] =(env)->GetFloatField(jObjPerspective, jVec4fZField);
    vPerspective._v[3] =(env)->GetFloatField(jObjPerspective, jVec4fWField);
    initModelViewMatrix.m_vPerspective = vPerspective;
    //--透视投影--------------------------------

    //--摄像机--------------------------------
    osg::Vec3f  vCamera;
    jobject jObjCamera = (env)->GetObjectField(jObjModelViewMatrix, jModelViewMatrixCameraField);
    vCamera._v[0] =(env)->GetFloatField(jObjCamera, jVec3fXField);
    vCamera._v[1] =(env)->GetFloatField(jObjCamera, jVec3fYField);
    vCamera._v[2] =(env)->GetFloatField(jObjCamera, jVec3fZField);
    initModelViewMatrix.m_vCamera = vCamera;
    //--摄像机--------------------------------

    //--观察点--------------------------------
    osg::Vec3f  vObserve;
    jobject jObjObserve = (env)->GetObjectField(jObjModelViewMatrix, jModelViewMatrixObserveField);
    vObserve._v[0] =(env)->GetFloatField(jObjObserve, jVec3fXField);
    vObserve._v[1] =(env)->GetFloatField(jObjObserve, jVec3fYField);
    vObserve._v[2] =(env)->GetFloatField(jObjObserve, jVec3fZField);
    initModelViewMatrix.m_vObserve = vObserve;
    //--观察点--------------------------------

    //--UP分量--------------------------------
    LOGI("init up");
    osg::Vec3f  vUp;
    jobject jObjUp = (env)->GetObjectField(jObjModelViewMatrix, jModelViewMatrixUpField);
    vUp._v[0] =(env)->GetFloatField(jObjUp, jVec3fXField);
    vUp._v[1] =(env)->GetFloatField(jObjUp, jVec3fYField);
    vUp._v[2] =(env)->GetFloatField(jObjUp, jVec3fZField);
    initModelViewMatrix.m_vUp = vUp;
    //--UP分量--------------------------------

    env->DeleteLocalRef(jObjPerspective);
    env->DeleteLocalRef(jObjObserve);
    env->DeleteLocalRef(jObjUp);

    mainApp.InitOsgWindow(width, height, initModelViewMatrix);
}

static void Draw(JNIEnv* env, jobject object, int centerX, int centerY ,double scale, float angle, float tile) {
    mainApp.Draw(centerX, centerY, scale, angle, tile);
}

static JNINativeMethod methods[] = {
        {"init", "(IILcom/model/roaming/element/ModelViewMatrix;)V", (void *)InitOsgWindow},
        {"step",  "(IIDFF)V",  (void *)Draw}
};

static jint registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *methods,
                                  int numMethods) {
    jclass clazz = env->FindClass(className);
    if (nullptr == clazz) {
        LOGE( "Find class %s failed! Is %s not exist? %s", className);
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, methods, numMethods) < 0) {
        LOGE( "RegisterNatives failed for %s", className);
        return JNI_FALSE;
    }
    return JNI_TRUE;
}



static jint registerNatives(JNIEnv *env, const char *className) {
    // 注册OSG 相关JNI调用函数
    if (!registerNativeMethods(env, className, methods,
            sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    jint result = JNI_ERR;
    LOGI( "JNI_OnLoad enter.");

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE( "ERROR: GetEnv failed");
        return result;
    }
    assert(env != nullptr);

    if (registerNatives(env, "com/model/roaming/jni/RoamingNative") == JNI_FALSE) {
        LOGE( "RoamingNative native registration failed");
        return result;
    }


    jClassModelViewMatrix = env->FindClass("com/model/roaming/element/ModelViewMatrix");
    jClassVec4f = env->FindClass("com/model/roaming/element/Vec4f");
    jClassVec3f = env->FindClass("com/model/roaming/element/Vec3f");


    jModelViewMatrixMapRatioField = env->GetFieldID(jClassModelViewMatrix, "mMapRatio", "F");
    jModelViewMatrixCullRatioField = env->GetFieldID(jClassModelViewMatrix, "mCullRatio", "F");
    jModelViewMatrixCameraModelField = env->GetFieldID(jClassModelViewMatrix, "mCameraModel", "I");

    jModelViewMatrixPerspectiveField = env->GetFieldID(jClassModelViewMatrix, "mPerspective", "Lcom/model/roaming/element/Vec4f;");
    jModelViewMatrixCameraField = env->GetFieldID(jClassModelViewMatrix, "mCamera", "Lcom/model/roaming/element/Vec3f;");
    jModelViewMatrixObserveField = env->GetFieldID(jClassModelViewMatrix, "mObserve", "Lcom/model/roaming/element/Vec3f;");
    jModelViewMatrixUpField = env->GetFieldID(jClassModelViewMatrix, "mUp", "Lcom/model/roaming/element/Vec3f;");

    jVec4fXField = env->GetFieldID(jClassVec4f, "x", "F");
    jVec4fYField = env->GetFieldID(jClassVec4f, "y", "F");
    jVec4fZField = env->GetFieldID(jClassVec4f, "z", "F");
    jVec4fWField = env->GetFieldID(jClassVec4f, "w", "F");

    jVec3fXField = env->GetFieldID(jClassVec3f, "x", "F");
    jVec3fYField = env->GetFieldID(jClassVec3f, "y", "F");
    jVec3fZField = env->GetFieldID(jClassVec3f, "z", "F");

    result = JNI_VERSION_1_6;

    return result;
}

extern "C"
JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI( "JNI_OnUnload enter.");
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE( "ERROR: GetEnv failed");
        return;
    }
    // 引用
    env->DeleteLocalRef(jClassModelViewMatrix);
    env->DeleteLocalRef(jClassVec4f);
    env->DeleteLocalRef(jClassVec3f);

}
