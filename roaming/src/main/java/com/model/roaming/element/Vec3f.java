package com.model.roaming.element;

/**
 * 用来存储参数的3元类
 */
public class Vec3f {
    /**三维坐标系x的坐标*/
    private float x;
    /**三维坐标系y的坐标*/
    private float y;
    /**三维坐标系z的坐标*/
    private float z;

    public Vec3f(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vec3f() {
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }

    @Override
    public String toString() {
        return "Vec3f{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                '}';
    }

    /**
     * 判断两个对象的值是否相等
     * @param vec3f
     * @return
     */
    public boolean equals(Vec3f vec3f) {
        if(this.x ==vec3f.getX() &&
                this.y==vec3f.getY() &&
                this.z==vec3f.getZ())
        {
            return true;
        }else {
            return false;
        }
    }
}
