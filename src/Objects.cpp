#include "../include/Objects.h"


Material::Material()
    : diffuse(0.0),
    specular(0.0),
    emission(0.0),
    shininess(0.0) {}
Material::~Material(){}

Triangle::Triangle(float ax, float ay, float az,
        float bx, float by, float bz,
        float cx, float cy, float cz)
    : a(mm::vec3(ax,ay,az)),
    b(mm::vec3(bx,by,bz)),
    c(mm::vec3(cx,cy,cz)),
    transform(mm::mat4(1.0)),
    inv_transform(mm::mat4(1.0)) {}
Triangle::Triangle(mm::vec3 a_, mm::vec3 b_, mm::vec3 c_)
    : a(a_), b(b_), c(c_),
    transform(mm::mat4(1.0)),
    inv_transform(mm::mat4(1.0)) {}


Sphere::Sphere(mm::vec3 pos_, float radius_)
    : pos(pos_), radius(radius_),
    transform(mm::mat4(1.0)),
    inv_transform(mm::mat4(1.0)) {}
Sphere::Sphere(float x, float y, float z, float radius_)
    : pos(mm::vec3(x,y,z)), radius(radius_),
    transform(mm::mat4(1.0)),
    inv_transform(mm::mat4(1.0)) {}


Camera::Camera(mm::vec3 eye_, mm::vec3 center_, mm::vec3 up_, float fovy_)
    : eye(eye_), center(center_), up(up_), fovy(fovy_) {}
Camera::Camera(float ex, float ey, float ez,
    float cx, float cy, float cz,
    float ux, float uy, float uz,
    float fovy_)
    : eye(mm::vec3(ex,ey,ez)),
    center(mm::vec3(cx,cy,cz)),
    up(mm::vec3(ux,uy,uz)),
    fovy(fovy_) {}
