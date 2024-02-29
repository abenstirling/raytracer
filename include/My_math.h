#pragma once

#include <utility>


class mm{
public:
    struct vec2{
        float data[3];
        float& x;
        float& y;

        vec2(float n)
            : x(data[0]), y(data[1]) {
            for(int i=0; i<2; i++){
                data[i] = n;
            }
        }
        vec2(float x_, float y_) 
            : x(data[0]), y(data[1]) {
            data[0]=x_;
            data[1]=y_;
        }

        float& operator[](int index) {
            return data[index];
        }
    };

    struct vec3{
        float data[3];
        float& x;
        float& y;
        float& z;
        vec3(float n)
            : x(data[0]), y(data[1]), z(data[2]) {
            for(int i=0; i<3; i++){
                data[i] = n;
            }
        }
        vec3(float x_, float y_, float z_) 
            : x(data[0]), y(data[1]), z(data[2]) {
            data[0]=x_;
            data[1]=y_;
            data[2]=z_;
        }

        float& operator[](int index) {
            return data[index];
        }
    };

    struct vec4{
        float data[4];
        float& x;
        float& y;
        float& z;
        float& w;
        vec4(float n)
            : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {
            for(int i=0; i<4; i++){
                data[i] = n;
            }
        }
        vec4(float x_, float y_, float z_, float w_) 
            : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {
            data[0]=x_;
            data[1]=y_;
            data[2]=z_;
            data[3]=w_;

        }

        float& operator[](int index) {
            return data[index];
        }
    };

    struct mat2{
        float data[2][2];
        mat2(float n){
            for(int y=0; y<2; y++){
                for(int x=0; x<2; x++){
                    data[y][x] = n;       
                }
            }
        }
        mat2(float p00, float p01,
            float p10, float p11 ){
                data[0][0] = p00;
                data[0][1] = p01;

                data[1][0] = p10;
                data[1][1] = p11;
        }
        float* operator[](int index) {
            return data[index];
        }
    };

    struct mat3{
        float data[3][3];
        mat3(float n){
            for(int y=0; y<3; y++){
                for(int x=0; x<3; x++){
                    data[y][x] = n;       
                }
            }
        }
        mat3(float p00, float p01, float p02,
            float p10, float p11 , float p12,
            float p20, float p21 , float p22){
                data[0][0] = p00;
                data[0][1] = p01;
                data[0][2] = p02;

                data[1][0] = p10;
                data[1][1] = p11;
                data[1][2] = p12;

                data[2][0] = p20;
                data[2][1] = p21;
                data[2][2] = p22;
        }
        float* operator[](int index) {
            return data[index];
        }
        float& operator[](std::pair<int, int> indices) {
            return data[indices.first][indices.second];
        }

    };

    struct mat4{
        float data[4][4];
        mat4(float n){
            for(int y=0; y<4; y++){
                for(int x=0; x<4; x++){
                    data[y][x] = n;       
                }
            }
        }
        mat4(float p00, float p01, float p02, float p03,
            float p10, float p11, float p12, float p13,
            float p20, float p21, float p22, float p23,
            float p30, float p31, float p32, float p33){
                data[0][0] = p00;
                data[0][1] = p01;
                data[0][2] = p02;
                data[0][3] = p03;

                data[1][0] = p10;
                data[1][1] = p11;
                data[1][2] = p12;
                data[1][3] = p13;

                data[2][0] = p20;
                data[2][1] = p21;
                data[2][2] = p22;
                data[2][3] = p23;

                data[3][0] = p30;
                data[3][1] = p31;
                data[3][2] = p32;
                data[3][3] = p33;

        }
        float* operator[](int index) {
            return data[index];
        }
    };
    friend vec2 operator+(const vec2& v1, const vec2& v2);
    friend vec3 operator+(const vec3& v1, const vec3& v2);
    friend vec4 operator+(const vec4& v1, const vec4& v2);

    friend vec2 operator-(const vec2& v1, const vec2& v2);
    friend vec3 operator-(const vec3& v1, const vec3& v2);
    friend vec4 operator-(const vec4& v1, const vec4& v2);

    friend float operator*(const vec2& v1, const vec2& v2);
    friend float operator*(const vec3& v1, const vec3& v2);
    friend float operator*(const vec4& v1, const vec4& v2);

};


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



