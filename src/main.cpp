
#include "../include/My_math.h"
#include "../include/Scene.h"
#include "../include/Parse.h"


int main(int argc, char* argv[]){

    Scene *scene = new Scene();
    Parse::parse_file(scene, argv[1]);


    return 0;
}
