#pragma once

#include "My_math.h"
#include "Objects.h"
#include "Scene.h"
#include "stb_image_write.h"

#include <limits>
#include <algorithm>
#include <thread>


class Render{
public: //constructor/destructor
    Render(Scene* scene_);
    ~Render();

public: //vars
    uint8_t* data;
    Scene* scene;
private: //vars


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

        mm::vec3 diffuse;
        mm::vec3 specular;
        float shininess;
        mm::vec3 emission;
        mm::vec3 ambient;

        Intersection() : pos(mm::vec3(0.0)), normal(mm::vec3(0.0)), t(INFINITY),
            diffuse(mm::vec3(0.0)), specular(mm::vec3(0.0)), shininess(0.0f), emission(mm::vec3(0.0)), ambient(mm::vec3(0.0)){}
        Intersection(mm::vec3 pos_, mm::vec3 normal_)
            : pos(pos_), normal(normal_), t(INFINITY),
            diffuse(mm::vec3(0.0)), specular(mm::vec3(0.0)), shininess(0.0f), emission(mm::vec3(0.0)), ambient(mm::vec3(0.0)) {}
    };

public: //fn
    Ray gen_ray(int y, int x);
    void compute();
    void write();

private: //fn
    bool trace(const Ray& ray, Intersection* inter);
    void calc_color(const Ray& ray, const Intersection& inter, mm::vec3* color);
    void lambert_phong(const Light& light,
                       const mm::vec3& dir,
                       const mm::vec3& normal,
                       const mm::vec3& half_vec,
                       const mm::vec3& diffuse,
                       const mm::vec3& specular,
                       const float& shininess,
                       mm::vec3* color);
    void computeChunk(int start_y, int end_y);
};
