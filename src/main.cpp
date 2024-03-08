
#include "../include/raytrace.h"
#include "../include/stb_image_write.h"

int main(int argc, char* argv[]){
    if(argc<2)
        std::cerr
        << "expected 2 arguments\n"
        << "\t./bin/raytracer <scene_file>"
        << std::endl;


    Scene *scene = new Scene();
    Parse::parse_file(scene, argv[1]);
    Render *render = new Render(scene);

    render->compute();
    render->write();

    return 0;
}
