package com.model.roaming.jni;

public class RoamingNative {

    static {
        System.loadLibrary( "roaming");
    }


    public  static native  void       init( int width,  int height);
    public  static native  void       step();

}
