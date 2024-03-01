
#include "../include/My_math.h"
#include "../include/Scene.h"

int main(int argc, char* argv[]){

    if (argc < 2) {
            std::cerr << "usage is something like: " << argv[0] << " scene1.test" << std::endl;
            return 1;
        }
    Scene scene;

    scene.loadFromFile(argv[1]);

    return 0;
}
