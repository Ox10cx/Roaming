package com.gx.roaming;

import android.Manifest;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.util.ArrayList;
import java.util.List;

public class BaseActivity extends AppCompatActivity {
    private  String[]     mPermissions;
    private List<String> mPermissionList ;
    /**权限请求码 */
    private final int     mRequestCode = 100;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mPermissions = new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.ACCESS_NETWORK_STATE,
                Manifest.permission.INTERNET,Manifest.permission.CHANGE_WIFI_STATE};
        mPermissionList = new ArrayList<>();
    }

    @Override
    protected void onResume() {
        super.onResume();
        initPermission();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    private void initPermission() {
        /**版本大于23时，动态获取权限*/
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
            mPermissionList.clear();
            for(int i=0;i<mPermissions.length;i++){
                if(ContextCompat.checkSelfPermission(this,mPermissions[i])!= PackageManager.PERMISSION_GRANTED){
                    /**添加未授予的权限*/
                    mPermissionList.add(mPermissions[i]);
                }
            }
            /**没有通过申请权限*/
            if(mPermissionList.size()>0){
                ActivityCompat.requestPermissions(this,mPermissions,mRequestCode);
            }else {
                /**动态权限通过*/
            }
        }

    }




    /**
     * 请求权限回调的函数
     * @param requestCode   定义的权限请求码
     * @param permissions   请求的权限名称数组
     * @param grantResults  弹出页面后是否允许权限的标识数组，数组的长度对应的是权限名称数组的长度，数组的数据0表示允许权限，-1表示我们点击了禁止权限
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        boolean hasPermissionDismiss = false;
        if(mRequestCode == requestCode){
            for(int i=0;i<grantResults.length;i++){
                if(grantResults[i]==-1){
                    hasPermissionDismiss =true;
                }
            }
        }
        if(hasPermissionDismiss){
            /**如果权限没有被允许，直接退出*/
            Toast.makeText(this, "请开启权限", Toast.LENGTH_LONG).show();
        }
    }










}
