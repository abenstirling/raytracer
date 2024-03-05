#include "../include/Objects.h"

Triangle::Triangle(float ax, float ay, float az,
        float bx, float by, float bz,
        float cx, float cy, float cz)
    : a(mm::vec3(ax,ay,az)),
    b(mm::vec3(bx,by,bz)),
    c(mm::vec3(cx,cy,cz)) {}
Triangle::Triangle(mm::vec3 a_, mm::vec3 b_, mm::vec3 c_)
    : a(a_), b(b_), c(c_) {}


Sphere::Sphere(mm::vec3 pos_, float radius_, mm::mat4 t_)
    : pos(pos_), radius(radius_), t(t_) {}
Sphere::Sphere(float x, float y, float z, float radius_, mm::mat4 t_)
    : pos(mm::vec3(x,y,z)), radius(radius_), t(t_) {}


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
