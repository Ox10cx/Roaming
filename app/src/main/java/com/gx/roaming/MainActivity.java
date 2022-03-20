package com.gx.roaming;


import android.os.Bundle;
import com.model.roaming.RoamingSurfaceView;

public class MainActivity extends BaseActivity {
    private RoamingSurfaceView mRoamingSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mRoamingSurfaceView = findViewById(R.id.roaming);
    }
}