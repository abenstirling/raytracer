
#include "../include/My_math.h"
#include "../include/Scene.h"
#include "../include/Parse.h"
#include "../include/Render.h"
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




    // // test for stb_image_write
    // int width = 256;
    // int height = 256;
    // int channels = 3;
    // unsigned char *data = (unsigned char *)malloc(width * height * channels);
    // for (int i = 0; i < width * height * channels; i++)
    // {
    //     data[i] = 0;
    // }

    // for (int i = 0; i < width * height; i++)
    // {
    //     data[i * channels + 0] = i % 256;
    //     data[i * channels + 1] = i / 256;
    //     data[i * channels + 2] = 0;
    // }

    // stbi_write_png("test.png", width, height, channels, data, width * channels);

    // free(data);

    return 0;
}
