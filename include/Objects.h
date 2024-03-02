#pragma once
#include "My_math.h"

class Triangle{
public:
    mm::vec3 a;
    mm::vec3 b;
    mm::vec3 c;
    Triangle(mm::vec3 a_, mm::vec3 b_, mm::vec3 c_);
    Triangle(float ax, float ay, float az,
            float bx, float by, float bz,
            float cx, float cy, float cz);
};

class Sphere{
public:
    mm::vec3 pos;
    float radius;

    Sphere(mm::vec3 pos_, float radius_);
    Sphere(float x, float y, float z, float radius_);
};

class Light{
public:
    mm::vec4 pos;
};

class Camera{
public:
    float fovy;
    mm::vec3 eye;
    mm::vec3 center;
    mm::vec3 up;

    Camera(mm::vec3 eye_, mm::vec3 center_, mm::vec3 up_, float fovy);
    Camera(float ex, float ey, float ez,
        float cx, float cy, float cz,
        float ux, float uy, float uz,
        float fovy);
};
