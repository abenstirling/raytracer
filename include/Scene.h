#pragma once

#include "Objects.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Scene{
public:
    Scene();
    void loadFromFile(const std::string& filename);
    ~Scene();

private:
    std::vector<Objects::Sphere> spheres;
    std::vector<Objects::Triangle> triangles;
    std::vector<Objects::Light> lights;
    std::vector<Objects::Camera> cameras;




    /**
     * TODO
     * [x] project setup
     * [ ] port readfile from hw2
     *      stack stuff (local to world coords)
     * [ ] do the ray tracing
    */
    void parseLine(const std::string& line);

public:
    void add_sphere(Objects::Sphere& s);
    void add_triangle(Objects::Triangle& t);
    void add_light(Objects::Light& l);
    void add_camera(Objects::Camera& c);



};
