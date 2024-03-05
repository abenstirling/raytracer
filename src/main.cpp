
#include "../include/My_math.h"
#include "../include/Scene.h"
#include "../include/Parse.h"
#include "../include/Render.h"



int main(int argc, char* argv[]){
    if(argc<2)
        std::cerr
        << "expected 2 arguments\n"
        << "\t./bin/raytracer <scene_file>"
        << std::endl;

    Scene *scene = new Scene();
    // std::cout << "here" << std::endl;
    Parse::parse_file(scene, argv[1]);
    // mm::mat2 m = mm::mat2(1.0);
    // mm::print_mat(m);

    // std::cout << scene->spheres[0].pos.x << std::endl;
    // std::cout << scene->spheres.size() << std::endl;



    return 0;
}
