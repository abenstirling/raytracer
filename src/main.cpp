
#include "../include/My_math.h"


int main(int argc, char* argv[]){


    mm::mat2 m(0.0, 0.1,
               1.0, 1.1);
    mm::print_mat(m);
    m(0,0) = 2.0;
    mm::print_mat(m);

    mm::vec2 v1(1.0);
    mm::vec2 v2(1.0);
    mm::print_vec(v1);
    v1(1) = 9.0;
    mm::print_vec(v1);

    mm::vec2 v3 = v1-v2;
    mm::print_vec(v3);
    return 0;
}
