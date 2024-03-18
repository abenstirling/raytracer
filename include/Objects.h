#pragma once
//#include "My_math.h"
#include "Eigen/Dense"

struct vert_norm{
    Eigen::Vector3f pos;
    Eigen::Vector3f normal;
    vert_norm(Eigen::Vector3f pos_, Eigen::Vector3f normal_)
        : pos(pos_), normal(normal_) {}
};

class Material{
public:
    Material();
    Material(Eigen::Vector3f diffuse_,  Eigen::Vector3f specular_, float shininess_, Eigen::Vector3f emission_, Eigen::Vector3f ambient_);
public:
    Eigen::Vector3f diffuse;
    Eigen::Vector3f specular;
    float shininess;
    Eigen::Vector3f emission;
    Eigen::Vector3f ambient;
};


class Triangle{
public:
    Triangle(Eigen::Vector3f a_, Eigen::Vector3f b_, Eigen::Vector3f c_);
    Triangle(float ax, float ay, float az,
            float bx, float by, float bz,
            float cx, float cy, float cz);
    Triangle(vert_norm a_,vert_norm b_, vert_norm c_);

public:
    Eigen::Vector3f a;
    Eigen::Vector3f b;
    Eigen::Vector3f c;

    bool normals_defined;
    Eigen::Vector3f na;
    Eigen::Vector3f nb;
    Eigen::Vector3f nc;

    Eigen::Matrix4f transform;
    Eigen::Matrix4f inv_transform;

    Material mat;
};


class Sphere{
public:
    Sphere(Eigen::Vector3f pos_, float radius_);
    Sphere(float x, float y, float z, float radius_);

public:
    Eigen::Vector3f pos;
    float radius;

    Eigen::Matrix4f transform;
    Eigen::Matrix4f inv_transform;
    Material mat;
};


class Light{
public:
    Eigen::Vector3f pos;
    Eigen::Vector3f color;
    bool is_point;

    Light();
    Light(Eigen::Vector3f pos_, Eigen::Vector3f color_, bool is_point);

};


class Camera{
public:
    Camera(Eigen::Vector3f eye_, Eigen::Vector3f center_, Eigen::Vector3f up_, float fovy);
    Camera(float ex, float ey, float ez,
        float cx, float cy, float cz,
        float ux, float uy, float uz,
        float fovy);
    Camera();
public:
    Eigen::Vector3f eye;
    Eigen::Vector3f center;
    Eigen::Vector3f up;
    float fovy;
};
