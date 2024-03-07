#pragma once

#include "My_math.h"
#include "Scene.h"
#include "Transform.h"

#include <sstream>
#include <fstream>
#include <string>
#include <stack>


class Parse{
public:
    static void parse_file(Scene* scene, const char* file_name);

private:
    static void read_vals(std::stringstream &ss,int num_vals, float* vals);
    static void read_vals(std::stringstream &ss,int num_vals, int* vals);

public:
    // struct vert_norm{
    //     mm::vec3 pos;
    //     mm::vec3 normal;
    //     vert_norm(mm::vec3 pos_, mm::vec3 normal_)
    //         : pos(pos_), normal(normal_) {}
    // };

private:
    static std::string cur_cmd;
    static uint cur_line;
    static std::vector<mm::vec3> vertices;
    static std::vector<vert_norm> vertices_norm;
};
