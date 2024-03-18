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
    Eigen::Vector3f w = (scene->camera.eye - scene->camera.center).normalized(); // Points away from the look direction
    Eigen::Vector3f u = (scene->camera.up.cross(w)).normalized(); // mm::normalize(mm::cross(scene->camera.up, w)); // Right vector
    Eigen::Vector3f v = w.cross(u); //mm::cross(w, u); // Actual up vector
    Eigen::Vector3f ray_dir = (alpha * u + beta * v - w).normalized(); // mm::normalize(alpha * u + beta * v - w);

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
                Eigen::Vector3f color = Eigen::Vector3f::Zero();

                calc_color(ray, hit, &color);
                // std::cout << (hit.mat) << std::endl;
                // exit(0);

                int pos = (y*scene->width + x)*3;
                data[pos +0] = static_cast<uint8_t>(std::min(int(color[0] * 255.0f), 255));
                data[pos +1] = static_cast<uint8_t>(std::min(int(color[1] * 255.0f), 255));
                data[pos +2] = static_cast<uint8_t>(std::min(int(color[2] * 255.0f), 255));
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
            //     Eigen::Vector3f color(0.0);
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
    //float min_t = std::numeric_limits<float>::infinity();

    Intersection* cur_inter = new Intersection;
    inter->t = INFINITY;


    for(Sphere s : scene->spheres){
        // Eigen::Vector3f p0 = (s.inv_transform * Eigen::Vector4f(ray.origin, 1.0)).xyz();
        Eigen::Vector4f temp;
        temp << ray.origin, 1.0;
        Eigen::Vector4f temp2 = (s.inv_transform * temp);
        Eigen::Vector3f p0 = temp2.head<3>();

        Eigen::Vector4f temp3;
       temp3 << ray.dir, 0.0;
        temp2 = (s.inv_transform * temp3);
        Eigen::Vector3f p1 = temp2.head<3>();

        Eigen::Vector3f center = s.pos;
        float r = s.radius;

        float a = p1.dot(p1);
        float b = 2.0 * p1.dot(p0 - center);
        float c = (p0 - center).dot(p0 - center) - r*r;

        float disc = b*b - 4.0 * a * c;
        if(disc>=0){
            float t = (-b - sqrt(disc)) / (2*a);
            if(t>=0){
                Eigen::Vector3f temp = p0+p1*t;
                Eigen::Vector4f temp2;
                temp2 << temp, 1.0;
                cur_inter->pos = (s.transform * temp2).head<3>();
                cur_inter->t = t;
            }
        }





        // if(t0>0 && t1>0){
        //     if(t0<t1){
        //         // cur_inter->pos = (s.transform * Eigen::Vector4f((p0+p1*t0), 1.0)).head<3>();
        //         Eigen::Vector3f temp = p0+p1*t0;
        //         Eigen::Vector4f temp2;
        //         temp2 << temp, 1.0;
        //         cur_inter->pos = (s.transform * temp2).head<3>();
        //         cur_inter->t = t0;
        //     }else{
        //         // cur_inter->pos = (s.transform * Eigen::Vector4f((p0+p1*t1), 1.0)).head<3>();
        //         Eigen::Vector3f temp = p0+p1*t1;
        //         Eigen::Vector4f temp2;
        //         temp2 << temp, 1.0;
        //         cur_inter->pos = (s.transform * temp2).head<3>();
        //         cur_inter->t = t1;
        //     }
        // }
        // else if(t0>0 && t1<0){
        //     // cur_inter->pos = (s.transform * Eigen::Vector4f((p0+p1*t0), 1.0)).head<3>();
        //     Eigen::Vector3f temp = p0+p1*t0;
        //     Eigen::Vector4f temp2;
        //     temp2 << temp, 1.0;
        //     cur_inter->pos = (s.transform * temp2).head<3>();
        //     cur_inter->t = t0;
        // }
        // else if(t0<0 && t1>0){
        //     // cur_inter->pos = (s.transform * Eigen::Vector4f((p0+p1*t1), 1.0)).head<3>();
        //     Eigen::Vector3f temp = p0+p1*t1;
        //     Eigen::Vector4f temp2;
        //     temp2 << temp, 1.0;
        //     cur_inter->pos = (s.transform * temp2).head<3>();
        //     cur_inter->t = t1;
        // }


        if(cur_inter->t < inter->t){
            inter->pos = cur_inter->pos;
            inter->t = cur_inter->t;
            inter->diffuse = s.diffuse;
            inter->specular = s.specular;
            inter->shininess = s.shininess;
            inter->emission = s.emission;
            inter->ambient = s.ambient;

            Eigen::Vector3f n = (inter->pos - center).normalized();
            Eigen::Vector4f n_hom;
            n_hom << n, 0.0;
            Eigen::Vector4f rslt = ((s.inv_transform).transpose()) * n_hom;
            inter->normal = (rslt.head<3>()).normalized();
        }



    }


    // for (Triangle t : scene->triangles) {
    //         Eigen::Vector3f vertexA = (t.transform * Eigen::Vector4f(t.a, 1.0)).xyz();
    //         Eigen::Vector3f vertexB = (t.transform * Eigen::Vector4f(t.b, 1.0)).xyz();
    //         Eigen::Vector3f vertexC = (t.transform * Eigen::Vector4f(t.c, 1.0)).xyz();

    //         Eigen::Vector3f edgeAB = vertexB - vertexA;
    //         Eigen::Vector3f edgeAC = vertexC - vertexA;

    //         Eigen::Vector3f h = mm::cross(ray.dir, edgeAC);
    //         float determinant = edgeAB * h;

    //         if (abs(determinant) < EPSILON) {
    //             continue;
    //         }

    //         float f = 1.0 / determinant;
    //         Eigen::Vector3f rayToVertexA = ray.origin - vertexA;
    //         float u = f * rayToVertexA * h;

    //         if (u < 0.0 || u > 1.0) {
    //             continue;
    //         }

    //         Eigen::Vector3f q = mm::cross(rayToVertexA, edgeAB);
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


void Render::calc_color(const Ray& ray, const Intersection& inter, Eigen::Vector3f* color){
    //inter: pos, normal, t
    //ray: origin, dir

    for(Light light : scene->lights){
        Eigen::Vector3f eye_dir = (ray.origin - inter.pos).normalized();
        // Eigen::Vector3f eye_dir_form_point = (ray.origin - inter.pos);


        if(!light.is_point){ //directional
            Eigen::Vector3f light_dir = (light.pos).normalized();
            Eigen::Vector3f half_vec = (light_dir + eye_dir).normalized();
            lambert_phong(light,
                          light_dir,
                          inter.normal,
                          half_vec,
                          inter.diffuse,
                          inter.specular,
                          inter.shininess,
                          color);

        }else if(light.is_point){//point
            Eigen::Vector3f light_dir = (light.pos - inter.pos).normalized();
            Eigen::Vector3f half_vec = (light_dir + eye_dir).normalized();
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
                   const Eigen::Vector3f& dir,
                   const Eigen::Vector3f& normal,
                   const Eigen::Vector3f& half_vec,
                   const Eigen::Vector3f& diffuse,
                   const Eigen::Vector3f& specular,
                   const float& shininess,
                   Eigen::Vector3f* pix_color) {
    //
    Eigen::Vector3f n = normal.normalized();
    float nDotL = n.dot(dir);
    Eigen::Vector3f lambert =  diffuse.cwiseProduct(light.color) *  std::max(nDotL, 0.0f) ;
    float nDotH = n.dot(half_vec);
    Eigen::Vector3f phong = specular.cwiseProduct(light.color) * pow(std::max(nDotH, 0.0f), shininess);

    Eigen::Vector3f lp = (lambert + phong);

    *pix_color = *pix_color + lp;

}
