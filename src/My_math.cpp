
#include "My_math.h"


mm::vec2 operator+(const mm::vec2& v1, const mm::vec2& v2){
    return mm::vec2(v1.x+v2.x, v1.y+v2.y);
}
mm::vec3 operator+(const mm::vec3& v1, const mm::vec3& v2){
    return mm::vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}
mm::vec4 operator+(const mm::vec4& v1, const mm::vec4& v2){
    return mm::vec4(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
}

mm::vec2 operator-(const mm::vec2& v1, const mm::vec2& v2){
    return mm::vec2(v1.x-v2.x, v1.y-v2.y);
}
mm::vec3 operator-(const mm::vec3& v1, const mm::vec3& v2){
    return mm::vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}
mm::vec4 operator-(const mm::vec4& v1, const mm::vec4& v2){
    return mm::vec4(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
}

float operator*(const mm::vec2& v1, const mm::vec2& v2){
    return v1.x*v2.x + v1.y*v2.y;
}
float operator*(const mm::vec3& v1, const mm::vec3& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
float operator*(const mm::vec4& v1, const mm::vec4& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}

//mat operations
mm::vec2 operator*(const mm::mat2& m, const mm::vec2& v){
    return mm::vec2(m(0)*v, m(1)*v);
}
mm::vec3 operator*(const mm::mat3& m, const mm::vec3& v){
    return mm::vec3(m(0)*v, m(1)*v, m(2)*v);
}
mm::vec4 operator*(const mm::mat4& m, const mm::vec4& v){
    return mm::vec4(m(0)*v, m(1)*v, m(2)*v, m(3)*v);
}

mm::mat2 operator*(const mm::mat2& m1, const mm::mat2& m2){
    mm::mat2 r(0.0);
    for(int y=0; y<2; y++){
        for(int x=0; x<2; x++){
            r(y,x) = m1(y)*m2(x);
        }
    }
    return r;
}
mm::mat3 operator*(const mm::mat3& m1, const mm::mat3& m2){
    mm::mat3 r(0.0);
    for(int y=0; y<3; y++){
        for(int x=0; x<3; x++){
            r(y,x) = m1(y)*m2(x);
        }
    }
    return r;
}
mm::mat4 operator*(const mm::mat4& m1, const mm::mat4& m2){
    mm::mat4 r(0.0);
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            r(y,x) = m1(y)*m2(x);
        }
    }
    return r;
}

void mm::print_mat(mm::mat2& m){
    for(int y=0; y<2; y++){
        for(int x=0; x<2; x++){
            std::cout << m(y,x) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void mm::print_mat(mm::mat3& m){
    for(int y=0; y<3; y++){
        for(int x=0; x<3; x++){
            std::cout << m(y,x << '\t');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void mm::print_mat(mm::mat4& m){
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            std::cout << m(y,x) << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void mm::print_vec(mm::vec2& v){
    for(int i=0; i<2; i++){   
        std::cout << v(i) << '\t';
    }
    std::cout << std::endl;
    std::cout << std::endl;

}

void mm::print_vec(mm::vec3& v){
    for(int i=0; i<3; i++){   
        std::cout << v(i) << '\t';
    }
    std::cout << std::endl;
    std::cout << std::endl;

}

void mm::print_vec(mm::vec4& v){
    for(int i=0; i<4; i++){   
        std::cout << v(i) << '\t';
    }
    std::cout << std::endl;
    std::cout << std::endl;

}