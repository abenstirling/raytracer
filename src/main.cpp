
#include <iostream>

#include "My_math.h"


int main(int argc, char* argv[]){


    mm::mat2 m(0.0, 0.1,
               1.0, 1.1);

    print_mat(m);
    m(0,0) = 2.0;
    print_mat(m);

    return 0;
}

