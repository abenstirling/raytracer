#pragma once

#include "My_math.h"
#include "Scene.h"
#include <limits>


class Render{
public: //constructor/destructor
    Render(Scene* scene_);
    ~Render();

public: //vars
    float* data;

private: //vars
    Scene* scene;

    struct Ray{
        mm::vec3 origin;
        mm::vec3 dir;
        Ray(mm::vec3 origin_, mm::vec3 dir_)
            : origin(origin_), dir(dir_) {}
        Ray() : origin(mm::vec3(0.0)), dir(mm::vec3(0.0)) {}
    };

    struct Intersection{
        mm::vec3 pos;
        mm::vec3 normal;
        float t;
        Intersection() : pos(mm::vec3(0.0)), normal(mm::vec3(0.0)), t(INFINITY) {}
        Intersection(mm::vec3 pos_, mm::vec3 normal_)
            : pos(pos_), normal(normal_), t(INFINITY) {}
    };

public: //fn
    Ray gen_ray(int y, int x);
    void compute();
private: //fn
    bool trace(const Ray& ray, Intersection* inter);
    void calc_color(Intersection& inter, mm::vec3* color);

};
