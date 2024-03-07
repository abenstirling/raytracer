#include "../include/Render.h"
#include <cmath>

Render::Render(Scene* scene_)
    :scene(scene_){

}

Render::~Render(){

}

Render::Ray Render::gen_ray(int y, int x){
    Render::Ray return_ray;

    //compute fovx and aspect ratio
    double aspect_ratio = (float)scene->width / (float)scene->height;
    double fovy = scene->camera.fovy;
    double fovx = fovy * aspect_ratio;

    double alpha = tan(fovx / 2.0)) * (y - scene->width / 2.0) / (scene->width / 2.0));
    double beta = tan(fovy / 2.0) * (scene->height / 2.0 - x) / (scene->height / 2.0);





}

void Render::compute(){
    for(int y=0; y<scene->height; y++){
        for(int x=0; x<scene->width; x++){
            Ray ray = gen_ray(y, x);
            Intersection hit = trace(ray);

        }
    }
}

Render::Intersection Render::trace(Ray ray){
    for(Sphere s : scene->spheres)
}
