#include "../include/Render.h"
#include <cmath>

Render::Render(Scene* scene_)
    :scene(scene_){
    data = new float[scene->width * scene->height * 3];
}

Render::~Render(){
    delete(data);
}

Render::Ray Render::gen_ray(int y, int x){
    Render::Ray return_ray;

    //compute fovx and aspect ratio
    float aspect_ratio = (float)scene->width / (float)scene->height;
    float fovy = scene->camera.fovy;
    float fovx = fovy * aspect_ratio;


    float alpha = tan(fovx * M_PI/ 2.0 * 180.0) * (y - scene->width / 2.0) / (scene->width / 2.0);
    float beta = tan(fovy * M_PI/ 2.0 * 180.0) * (scene->height / 2.0 - x) / (scene->height / 2.0);

    // orthonormal basis vectors
    mm::vec3 w = mm::normalize(scene->camera.eye - scene->camera.center); // Points away from the look direction
    mm::vec3 u = mm::normalize(mm::cross(scene->camera.up, w));        // Right vector
    mm::vec3 v = mm::cross(w, u);                           // Actual up vector

    // need to overload the
    mm::vec3 ray_dir = mm::normalize(alpha * u + beta * v - w);

    return_ray.origin = scene->camera.eye;
    return_ray.dir = ray_dir;

    return return_ray;
}

void Render::compute(){
    for(int y=0; y<scene->height; y++){
        for(int x=0; x<scene->width; x++){
            Ray ray = gen_ray(y, x);
            Intersection hit;
            if(trace(ray, &hit)){
                //lighting calculation

            }
        }
    }
}

bool Render::trace(const Ray& ray, Intersection* inter){


    for(Sphere s : scene->spheres){
        //TODO inverse transform ray

        mm::vec3 p0 = ray.origin;
        mm::vec3 p1 = ray.dir;
        mm::vec3 center = s.pos;
        float r = s.radius;

        for(int i=0; i<3; i++){

            float a = p1(i) * p1(i);
            float b = 2 * p1(i) * (p0(i) - center(i));
            float c = (p0(i) - center(i)) * (p0(i) - center(i));

            float disc = b*b - 4* a *c;
            if(disc<0) //no intersection
                continue;

            float t0 = (b + sqrt(disc)) / (2*a);
            float t1 = (b - sqrt(disc)) / (2*a);

            if(t0>0 && t1>0){
                inter->pos = t0<t1 ? p0+p1*t0 :p0+p1*t1;
            }
            else if(t0>0 && t1<0){
                inter->pos = p0+p1*t0;
            }
            else if(t0<0 && t1>0){
                inter->pos = p0+p1*t1;
            }
            mm::vec3 n = mm::normalize(center - inter->pos);
            inter->normal = ((s.inv_transform).T() * mm::vec4(n.x, n.y, n.z,1.0)).xyz;
        }
    }


    for(Triangle t : scene->triangles){

        //
        mm::vec3 vertexA = t.a;
        mm::vec3 vertexB = t.b;
        mm::vec3 vertexC = t.c;
        // baracentric coordinates

        mm::vec3 edge1 = vertexB - vertexA;
        mm::vec3 edge2 = vertexC - vertexA;

        float a, f, u, v;
        edge1 = vertexB - vertexA;
        edge2 = vertexC - vertexA;
        mm::vec3 h = mm::cross(ray.dir, edge2);
        a = edge1 * h;

        if (abs(a) < EPSILON) {
            continue;
        }
        f = 1.0 / a;
        mm::vec3 s = ray.origin - vertexA;
        u = f * s * h;

        //
        if (u < 0.0 || u > 1.0) {
            continue;
        }

        mm::vec3 q = mm::cross(s, edge1);
        v = f * ray.dir * q;

        //outside the triangle
        if (v < 0.0 || u + v > 1.0) {
            continue;
        }

        float rayIntersectionDistance = f * edge2 * q;

        if (z > EPSILON) {
            mm::vec3 intersection = ray.origin + ray.dir * z;
            if ()
        }

    }

    if(inter->t == INFINITY)
        return false;
    return true;
}


void Render::calc_color(Intersection& inter, mm::vec3* color){
    // for(Light l : scene->lights){

    // }
    color->x = 0.0;
    color->y = 1.0;
    color->z = 0.3;


}
