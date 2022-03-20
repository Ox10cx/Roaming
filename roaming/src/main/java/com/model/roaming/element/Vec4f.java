package com.model.roaming.element;

/**
 * 用来存储参数的4元类
 *
 */
public class Vec4f {
    private float x;
    private float y;
    private float z;
    private float w;

    public Vec4f() {
    }

    public Vec4f(float x, float y, float z, float w) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.w = w;
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

    public float getW() {
        return w;
    }

    public void setW(float w) {
        this.w = w;
    }

    @Override
    public String toString() {
        return "Vec4f{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                ", w=" + w +
                '}';
    }

    /**
     * 判断两个对象的值是否相等
     * @param vec4f
     * @return
     */
    public boolean equals(Vec4f vec4f) {
        if(this.x ==vec4f.getX() &&
                this.y==vec4f.getY() &&
                this.z==vec4f.getZ() &&
                this.w==vec4f.getW())
        {
            return true;
        }else {
            return false;
        }
    }
}
