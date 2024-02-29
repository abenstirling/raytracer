
#include <iostream>

#include "My_math.h"


int main(int argc, char* argv[]){


    mm::mat2 m(0.0, 0.1,
               1.0, 1.1);

    std::cout << m[0][0] << std::endl;

    return 0;
}

