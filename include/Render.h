#pragma once

#include "My_math.h"
#include "Objects.h"
#include "Scene.h"
#include "stb_image_write.h"

#include "Eigen/Dense"

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
        Ray() : origin(Eigen::Vector3f(0.0,0.0,0.0)), dir(Eigen::Vector3f(0.0, 0.0, 0.0)) {}
    };

    struct Intersection{
        Eigen::Vector3f pos;
        Eigen::Vector3f normal;
        float t;
        Material mat;

        Intersection() : pos(Eigen::Vector3f(0.0,0.0,0.0)), normal(Eigen::Vector3f(0.0,0.0,0.0)), t(INFINITY), mat(Material()) {}

        Intersection(Eigen::Vector3f pos_, Eigen::Vector3f normal_)
            : pos(pos_), normal(normal_), t(INFINITY), mat(Material()) {}
    };

public: //fn
    Ray gen_ray(int y, int x);
    void compute();
    void write();

private: //fn
    bool trace(const Ray& ray, Intersection* inter);
    void calc_color(const Ray& ray, const Intersection& inter, Eigen::Vector3f& color, int max_depth);
    Eigen::Vector3f lambert_phong(const Light& light,
                       const Intersection& intersect,
                       const Eigen::Vector3f& dir,
                       const Eigen::Vector3f& half_vec);
    void computeChunk(int start_y, int end_y);
    Eigen::Vector3f reflect(const Eigen::Vector3f& incident, const Eigen::Vector3f& normal);
};
