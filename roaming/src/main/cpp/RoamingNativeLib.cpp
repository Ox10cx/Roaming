//
// Created by 龚喜 on 2022/3/19.
//

#include  "OsgMainApp.h"


OsgMainApp mainApp;

extern  "C"{
JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_init(JNIEnv* env, jclass obj, jint width, jint height);
JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_step(JNIEnv* env, jclass obj);
}
JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_init(JNIEnv* env, jclass obj, jint width, jint height)
{
    mainApp.initOsgWindow( 0,  0, width, height);
}

JNIEXPORT  void JNICALL Java_com_model_roaming_jni_RoamingNative_step(JNIEnv* env, jclass obj){
    mainApp.draw();
}
