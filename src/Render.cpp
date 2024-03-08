#include "../include/Render.h"
#include <cmath>
#include <cstdint>

Render::Render(Scene* scene_)
    :scene(scene_){
    data = new uint8_t[scene->width * scene->height * 3];
}

Render::~Render(){
    delete(data);
}

Render::Ray Render::gen_ray(int y, int x){
    Ray ray;

    //compute fovx and aspect ratio
    float aspect_ratio = (float)scene->width / (float)scene->height;
    float fovy = scene->camera.fovy;
    float fovx = fovy * aspect_ratio;

    float alpha = tan(fovx/2.0 * M_PI/180.0) * (x - scene->width / 2.0) / (scene->width / 2.0);
    float beta = tan(fovy/2.0 * M_PI/180.0) * (scene->height / 2.0 - y) / (scene->height / 2.0);

    // orthonormal basis vectors
    mm::vec3 w = mm::normalize(scene->camera.eye - scene->camera.center); // Points away from the look direction
    mm::vec3 u = mm::normalize(mm::cross(scene->camera.up, w)); // Right vector
    mm::vec3 v = mm::cross(w, u); // Actual up vector
    mm::vec3 ray_dir = mm::normalize(alpha * u + beta * v - w);

    ray.origin = scene->camera.eye;
    ray.dir = ray_dir;

    return ray;
}

void Render::compute(){

    // Ray ray = gen_ray(50, 30);

    // Intersection hit;
    // if(trace(ray, &hit)){
    //     // mm::print_vec(ray.origin);
    //     // mm::print_vec(ray.dir);

    //     std::cout << '.' << std::endl;
    //     //lighting calculation

    //     // data[y*scene->width + x +0] = static_cast<uint8_t>(0.0 * 255.0);
    //     // data[y*scene->width + x +1] = static_cast<uint8_t>(1.0 * 255.0);
    //     // data[y*scene->width + x +2] = static_cast<uint8_t>(0.3 * 255.0);

    // }



    for(int y=0; y<scene->height; y++){
        for(int x=0; x<scene->width; x++){

            Ray ray = gen_ray(y, x);

            Intersection hit;
            if(trace(ray, &hit)){
                int pos = (y*scene->width + x)*3;
                // std::cout << '.' << std::endl;
                //lighting calculation
                // mm::vec3 color(0.0);
                // calc_color(hit, &color);
                data[pos +0] = static_cast<uint8_t>(0.0 * 255.0);
                data[pos +1] = static_cast<uint8_t>(1.0 * 255.0);
                data[pos +2] = static_cast<uint8_t>(0.3 * 255.0);
            }
        }
    }

}

void Render::write(){

    // std::cout << scene->out_file << std::endl;

    if(!stbi_write_png("test_out.png", scene->width, scene->height, 3, data, scene->width*3)) {
        std::cerr << "Error: Failed to write PNG file!" << std::endl;
        exit(1);
    }
}


bool Render::trace(const Ray& ray, Intersection* inter){

    for(Sphere s : scene->spheres){
        // std::cout << "inv" << std::endl;
        // mm::print_mat(s.inv_transform);
        // std::cout << "t" << std::endl;
        // mm::print_mat(s.transform);

        mm::vec3 p0 = (s.inv_transform * mm::vec4(ray.origin, 1.0)).xyz();
        mm::vec3 p1 = (s.inv_transform * mm::vec4(ray.dir, 1.0)).xyz();
        mm::vec3 center = s.pos;
        float r = s.radius;

        mm::vec3 T0(0.0);
        mm::vec3 T1(1.0);

        float a = p1 * p1;
        float b = 2.0 * p1 * (p0 - center);
        float c = (p0 - center) * (p0 - center) - r*r;

        float disc = b*b - 4.0 * a *c;
        if(disc<0)//no intersection
            continue;

        float t0 = (-b + sqrt(disc)) / (2*a);
        float t1 = (-b - sqrt(disc)) / (2*a);

        mm::vec3 P0 = (s.transform * mm::vec4(p0,1.0)).xyz();
        mm::vec3 P1 = (s.transform * mm::vec4(p1,1.0)).xyz();

        if(t0>0 && t1>0){
            if(t0<t1){
                mm::vec4 posh =(s.transform * mm::vec4((p0+p1*t0), 1.0));
                inter->pos = posh.xyz()*(1/posh.w);
                // inter->pos = (s.transform * mm::vec4((p0+p1*t0), 1.0)).xyz();
                inter->t = t0;

            }else{
                mm::vec4 posh =(s.transform * mm::vec4((p0+p1*t1), 1.0));
                inter->pos = posh.xyz()*(1/posh.w);
                // inter->pos = (s.transform * mm::vec4((p0+p1*t1), 1.0)).xyz();
                inter->t = t1;
            }
        }
        else if(t0>0 && t1<0){
            // inter->pos = P0 + P1*t0;
            mm::vec4 posh =(s.transform * mm::vec4((p0+p1*t0), 1.0));
            inter->pos = posh.xyz()*(1/posh.w);
            inter->t = t0;
        }
        else if(t0<0 && t1>0){
            mm::vec4 posh =(s.transform * mm::vec4((p0+p1*t1), 1.0));
            inter->pos = posh.xyz()*(1/posh.w);
            // inter->pos = (s.transform * mm::vec4((p0+p1*t1), 1.0)).xyz();
            inter->t = t1;
        }

        mm::vec3 n = mm::normalize(center - inter->pos);
        inter->normal = ((s.inv_transform).T() * mm::vec4(n.x, n.y, n.z,1.0)).xyz();

    }


    // for(Triangle t : scene->triangles){

    //     //
    //     mm::vec3 vertexA = t.a;
    //     mm::vec3 vertexB = t.b;
    //     mm::vec3 vertexC = t.c;
    //     // baracentric coordinates

    //     mm::vec3 edgeAB = vertexB - vertexA;
    //     mm::vec3 edgeAC = vertexC - vertexA;

    //     float determinant, f, u, v;
    //     mm::vec3 h = mm::cross(ray.dir, edgeAC);
    //     determinant = edgeAB * h;

    //     if (abs(determinant) < EPSILON) {
    //         continue;
    //     }
    //     // f is inverse determinant
    //     f = 1.0 / determinant;
    //     mm::vec3 rayToVertexA = ray.origin - vertexA;
    //     // u is barycentricU
    //     u = f * rayToVertexA * h;

    //     //
    //     if (u < 0.0 || u > 1.0) {
    //         continue;
    //     }

    //     mm::vec3 q = mm::cross(rayToVertexA, edgeAB);
    //     // v is barycentricV
    //     v = f * ray.dir * q;

    //     //outside the triangle
    //     if (v < 0.0 || u + v > 1.0) {
    //         continue;
    //     }

    //     float rayIntersectionDistance = f * edgeAC * q;

    //     if (rayIntersectionDistance > EPSILON) {
    //         mm::vec3 intersection = ray.origin + ray.dir * rayIntersectionDistance;
    //         // do we need to check
    //     }

    // }

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
