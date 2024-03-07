#include "../include/Scene.h"

Scene::Scene()
    : width(0), height(0), maxdepth(1){
}

Scene::~Scene(){

}


void Scene::add_sphere(Sphere& s){
    spheres.push_back(s);
}

void Scene::add_triangle(Triangle& t){
    triangles.push_back(t);
}

void Scene::add_light(Light& l){
    lights.push_back(l);

}
// void Scene::add_camera(Camera& c){
//     cameras.push_back(c);
// }
