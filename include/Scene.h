#pragma once

#include "Objects.h"

#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>

class Scene{
public: //constructor destructor
    Scene();
    ~Scene();

public: // public vars
    int width;
    int height;
    int maxdepth;
    const char* out_file;

    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<Light> lights;
    Camera camera;

    Eigen::Vector3f ambient;
    Eigen::Vector3f attenuation;

private: //private vars

public: //public fn
    void add_sphere(Sphere& s);
    void add_triangle(Triangle& t);
    void add_light(Light& l);
    // void add_camera(Camera& c);

private: //private fn

};



/**
 * TODO
 * [x] project setup
 * [ ] port readfile from hw2
 *      stack stuff (local to world coords)
 * [ ] do the ray tracing
*/
