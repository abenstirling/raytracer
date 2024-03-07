
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
    Parse::parse_file(scene, argv[1]);


    return 0;
}
