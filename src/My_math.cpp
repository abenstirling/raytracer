
#include "../include/My_math.h"

//addition
mm::vec2 operator+(const mm::vec2& v1, const mm::vec2& v2) {
    return mm::vec2(v1.x+v2.x, v1.y+v2.y);
}
mm::vec3 operator+(const mm::vec3& v1, const mm::vec3& v2) {
    return mm::vec3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}
mm::vec4 operator+(const mm::vec4& v1, const mm::vec4& v2){
    return mm::vec4(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z, v1.w+v2.w);
}

mm::mat2 operator+(const mm::mat2 &m1, const mm::mat2 &m2){
    mm::mat2 ret(0.0);
    for(int i=0; i<4; i++)
        ret.data[i] = m1.data[i] + m2.data[i];
    return ret;
}
mm::mat3 operator+(const mm::mat3 &m1, const mm::mat3 &m2){
    mm::mat3 ret(0.0);
    for(int i=0; i<9; i++)
        ret.data[i] = m1.data[i] + m2.data[i];
    return ret;
}
mm::mat4 operator+(const mm::mat4 &m1, const mm::mat4 &m2){
    mm::mat4 ret(0.0);
    for(int i=0; i<16; i++)
        ret.data[i] = m1.data[i] + m2.data[i];
    return ret;
}

//subtraction
mm::vec2 operator-(const mm::vec2& v1, const mm::vec2& v2){
    return mm::vec2(v1.x-v2.x, v1.y-v2.y);
}
mm::vec3 operator-(const mm::vec3& v1, const mm::vec3& v2){
    return mm::vec3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}
mm::vec4 operator-(const mm::vec4& v1, const mm::vec4& v2){
    return mm::vec4(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z, v1.w-v2.w);
}

//multiplication
float operator*(const mm::vec2& v1, const mm::vec2& v2) {
    return v1.x*v2.x + v1.y*v2.y;
}
float operator*(const float* v1, const mm::vec2& v2){
    return v1[0]*v2.x + v1[1]*v2.y;
}


float operator*(const mm::vec3& v1, const mm::vec3& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
float operator*(const float* v1, const mm::vec3& v2){
    return v1[0]*v2.x + v1[1]*v2.y + v1[2]*v2.z;
}


float operator*(const mm::vec4& v1, const mm::vec4& v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}
float operator*(const float* v1, const mm::vec4& v2){
    return v1[0]*v2.x + v1[1]*v2.y + v1[2]*v2.z + v1[3]*v2.w;
}


//mat operations
mm::mat2 operator*(const mm::mat2 &m, const float &c){
    mm::mat2 ret(0.0);
    for(int i=0; i<4; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}
mm::mat3 operator*(const mm::mat3 &m, const float &c){
    mm::mat3 ret(0.0);
    for(int i=0; i<9; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}
mm::mat4 operator*(const mm::mat4 &m, const float &c){
    mm::mat4 ret(0.0);
    for(int i=0; i<16; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}

mm::mat2 operator*(const float &c, const mm::mat2 &m){
    mm::mat2 ret(0.0);
    for(int i=0; i<4; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}
mm::mat3 operator*(const float &c, const mm::mat3 &m){
    mm::mat3 ret(0.0);
    for(int i=0; i<9; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}
mm::mat4 operator*(const float &c, const mm::mat4 &m){
    mm::mat4 ret(0.0);
    for(int i=0; i<16; i++)
        ret.data[i] = m.data[i] * c;
    return ret;
}

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
            r(y,x) = m1(y)[0]*m2(x)[0] +
                     m1(y)[1]*m2(x)[1];
        }
    }
    return r;
}
mm::mat3 operator*(const mm::mat3& m1, const mm::mat3& m2){
    mm::mat3 r(0.0);
    for(int y=0; y<3; y++){
        for(int x=0; x<3; x++){
            r(y,x) = m1(y)[0]*m2(x)[0] +
                     m1(y)[1]*m2(x)[1] +
                     m1(y)[2]*m2(x)[2];
        }
    }
    return r;
}
mm::mat4 operator*(const mm::mat4& m1, const mm::mat4& m2){
    mm::mat4 r(0.0);
    for(int y=0; y<4; y++){
        for(int x=0; x<4; x++){
            r(y,x) = m1(y)[0]*m2(x)[0] +
                     m1(y)[1]*m2(x)[1] +
                     m1(y)[2]*m2(x)[2] +
                     m1(y)[3]*m2(x)[3];
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
            std::cout << m(y,x) << '\t';
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



mm::vec2 mm::normalize(const mm::vec2& v){
    float len = sqrt(v.x*v.x +v.y*v.y);
    return mm::vec2(v.x / len, v.y / len);
}
mm::vec3 mm::normalize(const mm::vec3& v){
    float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return mm::vec3(v.x / len, v.y / len, v.z / len);

}
mm::vec4 mm::normalize(const mm::vec4& v){
    float len = sqrt(v.x*v.x +v.y*v.y + v.z*v.z + v.w*v.w);
    return mm::vec4(v.x / len, v.y / len, v.z / len, v.w / len);
}

mm::vec3 mm::cross(const mm::vec3& v1, const mm::vec3& v2){
    mm::vec3 ret(0.0);
    ret.x = v1.y * v2.z - v1.z * v2.y;
    ret.y = v1.z * v2.x - v1.x * v2.z;
    ret.z = v1.x * v2.y - v1.y * v2.x;
    return ret;
}
