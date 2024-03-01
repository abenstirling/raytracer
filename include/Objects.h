#pragma once
#include "My_math.h"


class Objects{
public:
    class Triangle{
        mm::vec3 a;
        mm::vec3 b;
        mm::vec3 c;
        Triangle(mm::vec3 a_, mm::vec3 b_, mm::vec3 c_)
            : a(a_), b(b_), c(c_) {}
        Triangle(float ax, float ay, float az,
                 float bx, float by, float bz,
                 float cx, float cy, float cz)
            : a(mm::vec3(ax,ay,az)),
            b(mm::vec3(bx,by,bz)),
            c(mm::vec3(cx,cy,cz)) {}
    };

    class Sphere{
        mm::vec3 pos;
        float radius;

        Sphere(mm::vec3 pos_, float radius_)
            : pos(pos_), radius(radius_) {}
        Sphere(float x, float y, float z, float radius_)
            : pos(mm::vec3(x,y,z)), radius(radius_) {}
    };

    class Light{
        mm::vec4 pos;
    };

    class Camera{
        mm::vec3 eye;
        mm::vec3 center;
        mm::vec3 up;

        Camera(mm::vec3 eye_, mm::vec3 center_, mm::vec3 up_)
            : eye(eye_), center(center_), up(up_) {}
        Camera(float ex, float ey, float ez,
               float cx, float cy, float cz,
               float ux, float uy, float uz)
            : eye(mm::vec3(ex,ey,ez)),
            center(mm::vec3(cx,cy,cz)),
            up(mm::vec3(ux,uy,uz)) {}
    };

};
