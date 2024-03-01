#pragma once

#include <iostream>
#include <utility>

class mm {
public:
struct vec2 {
    float *data;
    float &x;
    float &y;

    vec2(float n)
        : data(new float[2]), x(data[0]), y(data[1]) {
        for (int i = 0; i < 2; i++) {
            data[i] = n;
        }
    }

    vec2(float x_, float y_)
        : data(new float[2]), x(data[0]), y(data[1]) {
        data[0] = x_;
        data[1] = y_;
    }

    float &operator()(int index){
        return data[index];
    }

    mm::vec2& operator=(const mm::vec2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            // z = other.z;
        }
        return *this;
    }

};

struct vec3 {
    float *data;
    float &x;
    float &y;
    float &z;

    vec3(float n) : data(new float[3]), x(data[0]), y(data[1]), z(data[2]) {
        for (int i = 0; i < 3; i++) {
            data[i] = n;
        }
    }

    vec3(float x_, float y_, float z_) : data(new float[3]), x(data[0]), y(data[1]), z(data[2]) {
        data[0] = x_;
        data[1] = y_;
        data[2] = z_;
    }

    float &operator()(int index) {
        return data[index];
    }

    mm::vec3& operator=(const mm::vec3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

};

struct vec4 {
    float *data;
    float &x;
    float &y;
    float &z;
    float &w;

    vec4(float n)
        : data(new float[4]), x(data[0]), y(data[1]), z(data[2]), w(data[3]) {
        for (int i = 0; i < 3; i++) {
            data[i] = n;
        }
    }
    vec4(float x_, float y_, float z_, float w_)
        : data(new float[4]), x(data[0]), y(data[1]), z(data[2]), w(data[3]) {
        data[0] = x_;
        data[1] = y_;
        data[2] = z_;
        data[3] = w_;
    }

    float &operator()(int index){
        return data[index];
    }

    mm::vec4& operator=(const mm::vec4& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }
        return *this;
    }
};

struct mat2 {
    float* data;

    mat2(float n)
        : data(new float(4)) {
        for (int i = 0; i<4; i++) {
            data[i] = n;
        }
    }


    mat2(float p00, float p01,
         float p10, float p11)
        : data(new float(4)) {
        data[0*2 + 0] = p00;
        data[0*2 + 1] = p01;

        data[1*2 + 0] = p10;
        data[1*2 + 1] = p11;
    }

    float& operator()(int y, int x) {
        return data[y*2 + x];
    }
    float* operator()(int row) const{
        return &data[row*2];
    }
};

struct mat3 {
    float* data;

    mat3(float n)
        : data(new float(9)) {
        for (int i = 0; i<9; i++) {
            data[i] = n;
        }
    }
    mat3(float p00, float p01, float p02,
         float p10, float p11, float p12,
         float p20, float p21, float p22)
        : data(new float(9)) {
        data[0*3 + 0] = p00;
        data[0*3 + 1] = p01;
        data[0*3 + 2] = p02;

        data[1*3 + 0] = p10;
        data[1*3 + 1] = p11;
        data[1*3 + 2] = p12;

        data[2*2 + 0] = p20;
        data[2*2 + 1] = p21;
        data[2*2 + 2] = p22;
    }

    float& operator()(int y, int x) {
        return data[y*3 + x];
    }
    float* operator()(int row) const{
        return &data[row*3];
    }
};

struct mat4 {
    float* data;

    mat4(float n)
        : data(new float(16)) {
        for (int i = 0; i<16; i++) {
            data[i] = n;
        }
    }
    mat4(float p00, float p01, float p02, float p03,
        float p10, float p11, float p12, float p13,
        float p20, float p21, float p22, float p23,
        float p30, float p31, float p32, float p33) {
        data[0*4 + 0] = p00;
        data[0*4 + 1] = p01;
        data[0*4 + 2] = p02;
        data[0*4 + 3] = p03;

        data[1*4 + 0] = p10;
        data[1*4 + 1] = p11;
        data[1*4 + 2] = p12;
        data[1*4 + 3] = p13;

        data[2*4 + 0] = p20;
        data[2*4 + 1] = p21;
        data[2*4 + 2] = p22;
        data[2*4 + 3] = p23;

        data[3*4 + 0] = p30;
        data[3*4 + 1] = p31;
        data[3*4 + 2] = p32;
        data[3*4 + 3] = p33;

    }
    float& operator()(int y, int x) {
        return data[y*4 + x];
    }
    float* operator()(int row) const{
        return &data[row*4];
    }
};
friend vec2 operator+(const vec2 &v1, const vec2 &v2);
friend vec3 operator+(const vec3 &v1, const vec3 &v2);
friend vec4 operator+(const vec4 &v1, const vec4 &v2);

friend vec2 operator-(const vec2 &v1, const vec2 &v2);
friend vec3 operator-(const vec3 &v1, const vec3 &v2);
friend vec4 operator-(const vec4 &v1, const vec4 &v2);

friend float operator*(const vec2 &v1, const vec2 &v2);
friend float operator*(const vec3 &v1, const vec3 &v2);
friend float operator*(const vec4 &v1, const vec4 &v2);

friend vec2 operator*(const mat2 &m, const vec2 &v);
friend vec3 operator*(const mat3 &m, const vec3 &v);
friend vec4 operator*(const mat4 &m, const vec4 &v);

friend mat2 operator*(const mat2 &m1, const mat2 &m2);
friend mat3 operator*(const mat3 &m1, const mat3 &m2);
friend mat4 operator*(const mat4 &m1, const mat4 &m2);

static void print_mat(mm::mat2 &m);
static void print_mat(mm::mat3 &m);
static void print_mat(mm::mat4 &m);

static void print_vec(mm::vec2 &v);
static void print_vec(mm::vec3 &v);
static void print_vec(mm::vec4 &v);
};
