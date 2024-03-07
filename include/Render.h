#pragma once

#include "My_math.h"
#include "Scene.h"


class Render{
public: //constructor/destructor
    Render(Scene* scene_);
    ~Render();

public: //vars

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
        Ray ray;
        float t;
        Intersection() : ray(Ray()), t(0.0) {}
        Intersection(Ray ray_, float t_) : ray(ray_), t(t_) {}
    };

public: //fn
    Ray gen_ray(int y, int x);
    void compute();
private: //fn
    Intersection trace(Ray ray);

};
