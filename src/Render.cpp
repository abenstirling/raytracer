#include "../include/Render.h"
#include <cmath>
#include <cstdint>
#include <limits>

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

void Render::computeChunk(int start_y, int end_y) {
    for(int y = start_y; y < end_y; y++) {
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << (float)y / scene->height << std::endl;
        for(int x = 0; x < scene->width; x++) {
            Ray ray = gen_ray(y, x);

            Intersection hit;
            if(trace(ray, &hit)){
                // mm::print_vec(hit.normal);

                //lighting calculation
                mm::vec3 color(0.0);
                calc_color(ray, hit, &color);
                // std::cout << (hit.mat) << std::endl;
                // exit(0);

                int pos = (y*scene->width + x)*3;
                data[pos +0] = static_cast<uint8_t>(std::min(int(color.x * 255.0f), 255));
                data[pos +1] = static_cast<uint8_t>(std::min(int(color.y * 255.0f), 255));
                data[pos +2] = static_cast<uint8_t>(std::min(int(color.z * 255.0f), 255));
                // data[pos +0] = static_cast<uint8_t>(0.0 * 255.0);
                // data[pos +1] = static_cast<uint8_t>(0.6 * 255.0);
                // data[pos +2] = static_cast<uint8_t>(0.3 * 255.0);
            }
        }
    }
}

void Render::compute(){
    const int num_threads = std::thread::hardware_concurrency(); // Get the number of hardware threads
    const int chunk_size = std::ceil(scene->height / static_cast<float>(num_threads));

    std::vector<std::thread> threads;
    for(int i = 0; i < num_threads; i++) {
        int start_y = i * chunk_size;
        int end_y = std::min((i + 1) * chunk_size, scene->height);
        threads.emplace_back(&Render::computeChunk, this, start_y, end_y);
    }

    for(auto& thread : threads) {
        thread.join();
    }

    // for(int y=0; y<scene->height; y++){
    //     std::cout << std::setprecision(2) << std::fixed;
    //     std::cout << (float)y/scene->height << std::endl;
    //     for(int x=0; x<scene->width; x++){

            // Ray ray = gen_ray(y, x);

            // Intersection hit;
            // if(trace(ray, &hit)){
            //     // mm::print_vec(hit.normal);

            //     //lighting calculation
            //     mm::vec3 color(0.0);
            //     calc_color(ray, hit, &color);
            //     // std::cout << (hit.mat) << std::endl;
            //     // exit(0);

            //     int pos = (y*scene->width + x)*3;
            //     data[pos +0] = static_cast<uint8_t>(std::min(int(color.x * 255.0f), 255));
            //     data[pos +1] = static_cast<uint8_t>(std::min(int(color.y * 255.0f), 255));
            //     data[pos +2] = static_cast<uint8_t>(std::min(int(color.z * 255.0f), 255));
            //     // data[pos +0] = static_cast<uint8_t>(0.0 * 255.0);
            //     // data[pos +1] = static_cast<uint8_t>(0.6 * 255.0);
            //     // data[pos +2] = static_cast<uint8_t>(0.3 * 255.0);
            // }
    //     }
    // }

}

void Render::write(){

    // std::cout << scene->out_file << std::endl;

    if(!stbi_write_png("test_out.png", scene->width, scene->height, 3, data, scene->width*3)) {
        std::cerr << "Error: Failed to write PNG file!" << std::endl;
        exit(1);
    }
}


bool Render::trace(const Ray& ray, Intersection* inter){
    float min_t = std::numeric_limits<float>::infinity();

    Intersection* cur_inter = new Intersection;
    inter->t = std::numeric_limits<float>::infinity();


    for(Sphere s : scene->spheres){
        // std::cout << "t" << std::endl;
        // mm::print_mat(s.transform);
        // std::cout << "inv" << std::endl;
        // mm::print_mat(s.inv_transform);
        // std::cout << "I?" << std::endl;
        // mm::mat4 test = s.inv_transform * s.transform;
        // mm::print_mat(test);

        mm::vec3 p0 = (s.inv_transform * mm::vec4(ray.origin, 1.0)).xyz();
        mm::vec3 p1 = (s.inv_transform * mm::vec4(ray.dir, 0.0)).xyz();
        mm::vec3 center = s.pos;
        float r = s.radius;

        float a = p1 * p1;
        float b = 2.0 * p1 * (p0 - center);
        float c = (p0 - center) * (p0 - center) - r*r;

        float disc = b*b - 4.0 * a *c;
        if(disc<0)//no intersection
            continue;

        float t0 = (-b + sqrt(disc)) / (2*a);
        float t1 = (-b - sqrt(disc)) / (2*a);



        if(t0>0 && t1>0){
            if(t0<t1){
                cur_inter->pos = (s.transform * mm::vec4((p0+p1*t0), 1.0)).xyz();
                cur_inter->t = t0;
            }else{
                cur_inter->pos = (s.transform * mm::vec4((p0+p1*t1), 1.0)).xyz();
                cur_inter->t = t1;
            }
        }
        else if(t0>0 && t1<0){
            cur_inter->pos = (s.transform * mm::vec4((p0+p1*t0), 1.0)).xyz();
            cur_inter->t = t0;
        }
        else if(t0<0 && t1>0){
            cur_inter->pos = (s.transform * mm::vec4((p0+p1*t1), 1.0)).xyz();
            cur_inter->t = t1;
        }


        if(cur_inter->t < inter->t){
            inter->pos = cur_inter->pos;
            inter->t = cur_inter->t;
            inter->diffuse = s.diffuse;
            inter->specular = s.specular;
            inter->shininess = s.shininess;
            inter->emission = s.emission;
            inter->ambient = s.ambient;
        }


        mm::vec3 n = mm::normalize(inter->pos - center);
        inter->normal = ((s.inv_transform).T() * mm::vec4(n,0.0)).xyz();
    }


    // for (Triangle t : scene->triangles) {
    //         mm::vec3 vertexA = (t.transform * mm::vec4(t.a, 1.0)).xyz();
    //         mm::vec3 vertexB = (t.transform * mm::vec4(t.b, 1.0)).xyz();
    //         mm::vec3 vertexC = (t.transform * mm::vec4(t.c, 1.0)).xyz();

    //         mm::vec3 edgeAB = vertexB - vertexA;
    //         mm::vec3 edgeAC = vertexC - vertexA;

    //         mm::vec3 h = mm::cross(ray.dir, edgeAC);
    //         float determinant = edgeAB * h;

    //         if (abs(determinant) < EPSILON) {
    //             continue;
    //         }

    //         float f = 1.0 / determinant;
    //         mm::vec3 rayToVertexA = ray.origin - vertexA;
    //         float u = f * rayToVertexA * h;

    //         if (u < 0.0 || u > 1.0) {
    //             continue;
    //         }

    //         mm::vec3 q = mm::cross(rayToVertexA, edgeAB);
    //         float v = f * ray.dir * q;

    //         if (v < 0.0 || u + v > 1.0) {
    //             continue;
    //         }

    //         float rayIntersectionDistance = f * edgeAC * q;

    //         if (rayIntersectionDistance > EPSILON && rayIntersectionDistance < inter->t) {
    //             inter->t = rayIntersectionDistance;
    //             inter->pos = ray.origin + ray.dir * rayIntersectionDistance;
    //             inter->normal = mm::normalize(mm::cross(edgeAB, edgeAC));
    //             inter->diffuse = t.diffuse;
    //             inter->specular = t.specular;
    //             inter->emission = t.emission;
    //             inter->shininess = t.shininess;
    //             inter->ambient = t.ambient;
    //         }
    // }

    delete(cur_inter);
    if(inter->t == INFINITY)
        return false;
    return true;
}


void Render::calc_color(const Ray& ray, const Intersection& inter, mm::vec3* color){
    //inter: pos, normal, t
    //ray: origin, dir

    for(Light light : scene->lights){
        mm::vec3 eye_dir_form_point = mm::normalize(ray.origin - inter.pos);

        if(!light.is_point){ //directional
            mm::vec3 light_dir = mm::normalize(light.pos);
            mm::vec3 half_vec = mm::normalize (light_dir + eye_dir_form_point);
            lambert_phong(light,
                          light_dir,
                          inter.normal,
                          half_vec,
                          inter.diffuse,
                          inter.specular,
                          inter.shininess,
                          color);
        }else if(light.is_point){//point
            mm::vec3 light_dir = mm::normalize(light.pos - inter.pos);
            mm::vec3 half_vec = mm::normalize(light_dir + eye_dir_form_point);
            lambert_phong(light,
                          light_dir,
                          inter.normal,
                          half_vec,
                          inter.diffuse,
                          inter.specular,
                          inter.shininess,
                          color);
        }

    }

    *color = *color + inter.ambient + inter.emission;
}

void Render::lambert_phong(const Light& light,
                   const mm::vec3& dir,
                   const mm::vec3& normal,
                   const mm::vec3& half_vec,
                   const mm::vec3& diffuse,
                   const mm::vec3& specular,
                   const float& shininess,
                   mm::vec3* pix_color) {
    //
    float nDotL = normal * dir;
    mm::vec3 lambert =  diffuse* std::max(nDotL, 0.0f) ;
    float nDotH = normal * half_vec;
    mm::vec3 phong = specular * pow(std::max(nDotH, 0.0f), shininess);

    mm::vec3 lp = (lambert + phong);

    *pix_color = *pix_color + mm::vec3(lp.x*light.color.x,
                                       lp.y*light.color.y,
                                       lp.z*light.color.z);

}
