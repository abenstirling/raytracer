#pragma once

#include "My_math.h"
#include "Objects.h"
#include "Scene.h"
#include "stb_image_write.h"

#include <Eigen/Dense>

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
        Eigen::Vector3f origin;
        Eigen::Vector3f dir;
        Ray(Eigen::Vector3f origin_, Eigen::Vector3f dir_)
            : origin(origin_), dir(dir_) {}
        Ray() : origin(Eigen::Vector3f(0.0)), dir(Eigen::Vector3f(0.0)) {}
    };

    struct Intersection{
        Eigen::Vector3f pos;
        Eigen::Vector3f normal;
        float t;

        Eigen::Vector3f diffuse;
        Eigen::Vector3f specular;
        float shininess;
        Eigen::Vector3f emission;
        Eigen::Vector3f ambient;

        Intersection() : pos(Eigen::Vector3f(0.0)), normal(Eigen::Vector3f(0.0)), t(INFINITY),
            diffuse(Eigen::Vector3f(0.0)), specular(Eigen::Vector3f(0.0)), shininess(0.0f), emission(Eigen::Vector3f(0.0)), ambient(Eigen::Vector3f(0.0)){}
        Intersection(Eigen::Vector3f pos_, Eigen::Vector3f normal_)
            : pos(pos_), normal(normal_), t(INFINITY),
            diffuse(Eigen::Vector3f(0.0)), specular(Eigen::Vector3f(0.0)), shininess(0.0f), emission(Eigen::Vector3f(0.0)), ambient(Eigen::Vector3f(0.0)) {}
    };

public: //fn
    Ray gen_ray(int y, int x);
    void compute();
    void write();

private: //fn
    bool trace(const Ray& ray, Intersection* inter);
    void calc_color(const Ray& ray, const Intersection& inter, Eigen::Vector3f* color);
    void lambert_phong(const Light& light,
                       const Eigen::Vector3f& dir,
                       const Eigen::Vector3f& normal,
                       const Eigen::Vector3f& half_vec,
                       const Eigen::Vector3f& diffuse,
                       const Eigen::Vector3f& specular,
                       const float& shininess,
                       Eigen::Vector3f* color);
    void computeChunk(int start_y, int end_y);
};
