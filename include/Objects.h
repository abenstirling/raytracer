#pragma once
#include "My_math.h"

struct vert_norm{
    mm::vec3 pos;
    mm::vec3 normal;
    vert_norm(mm::vec3 pos_, mm::vec3 normal_)
        : pos(pos_), normal(normal_) {}
};

class Material{
public:
    Material();
    ~Material();
public:
    mm::vec3 diffuse;
    mm::vec3 specular;
    mm::vec3 emission;
    float shininess;

};


class Triangle : public Material{
public:
    Triangle(mm::vec3 a_, mm::vec3 b_, mm::vec3 c_);
    Triangle(float ax, float ay, float az,
            float bx, float by, float bz,
            float cx, float cy, float cz);
    Triangle(vert_norm a_,vert_norm b_, vert_norm c_);

public:
    mm::vec3 a;
    mm::vec3 b;
    mm::vec3 c;

    bool normals_defined;
    mm::vec3 na;
    mm::vec3 nb;
    mm::vec3 nc;

    mm::mat4 transform;
    mm::mat4 inv_transform;
};


class Sphere : public Material{
public:
    Sphere(mm::vec3 pos_, float radius_);
    Sphere(float x, float y, float z, float radius_);

public:
    mm::vec3 pos;
    float radius;

    mm::mat4 transform;
    mm::mat4 inv_transform;
};


class Light{
public:
    mm::vec4 pos;
    mm::mat4 inverse_transform;
};


class Camera{
public:
    Camera(mm::vec3 eye_, mm::vec3 center_, mm::vec3 up_, float fovy);
    Camera(float ex, float ey, float ez,
        float cx, float cy, float cz,
        float ux, float uy, float uz,
        float fovy);
    Camera();
public:
    mm::vec3 eye;
    mm::vec3 center;
    mm::vec3 up;
    float fovy;
};
