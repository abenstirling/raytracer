
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

    // Scene *scene = new Scene();
    // std::cout << "here" << std::endl;
    // Parse::parse_file(scene, argv[1]);

    mm::mat4 m = mm::mat4(2.0);
    m(0,3) = 8.0;
    mm::mat4 inv(0.0);
    // mm::print_mat(m);
    inv_R(m,inv);
    mm::print_mat(m);
    mm::print_mat(inv);




    return 0;
}
