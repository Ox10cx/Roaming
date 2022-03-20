package com.model.roaming.jni;

import com.model.roaming.element.ModelViewMatrix;

public class RoamingNative {

    static {
        System.loadLibrary( "roaming");
    }


    public  static native  void       init(int width,  int height, ModelViewMatrix modelViewMatrix);
    public  static native  void       step(int centerX, int centerY, double scale, float angle, float title);

}
