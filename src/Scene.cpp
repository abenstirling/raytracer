#include "../include/Scene.h"
#include <utility>

Scene::Scene(){

}

Scene::~Scene(){

}

void Scene::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;
        parseLine(line);
    }
}

void Scene::parseLine(const std::string& line) {
    std::istringstream iss(line);
    std::string keyword;
    iss >> keyword;

    if (keyword == "size") {
        //
    } else if (keyword == "camera") {
            // The rest of the camera parsing as before
        } else if (keyword == "ambient") {
            // The rest of the ambient light parsing as before
        } else if (keyword == "directional" || keyword == "point") {
            // The rest of the light parsing as before
        } else if (keyword == "diffuse") {
            //
        } else if (keyword == "specular") {
            //
        } else if (keyword == "maxverts") {
            //
        } else if (keyword == "vertex") {
            //
        } else if (keyword == "tri") {
            //
        }
}




void Scene::add_sphere(Objects::Sphere& s){
    spheres.push_back(s);
}

void Scene::add_triangle(Objects::Triangle& t){
    triangles.push_back(t);
}

void add_light(Objects::Light& l){

}
void add_camera(Objects::Camera& c);
