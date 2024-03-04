
#include "../include/My_math.h"
#include "../include/Scene.h"
#include "../include/Parse.h"


int main(int argc, char* argv[]){
    if(argc<2)
        std::cerr
        << "expected 2 arguments\n"
        << "\t./bin/raytracer <scene_file>"
        << std::endl;

    Scene *scene = new Scene();
    Parse::parse_file(scene, argv[1]);

    // std::cout << scene->spheres[0].radius << std::endl;
    mm::vec3  test = scene->cameras[0].up;
    mm::print_vec(test);
    std::cout << scene->cameras[0].fovy << std::endl;

    return 0;
}
