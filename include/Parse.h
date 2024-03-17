#pragma once

#include "My_math.h"
#include "Scene.h"
#include "Transform.h"

#include "Eigen/Dense"

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
    //     Eigen::Vector3f pos;
    //     Eigen::Vector3f normal;
    //     vert_norm(Eigen::Vector3f pos_, Eigen::Vector3f normal_)
    //         : pos(pos_), normal(normal_) {}
    // };

private:
    static std::string cur_cmd;
    static uint cur_line;
    static std::vector<Eigen::Vector3f> vertices;
    static std::vector<vert_norm> vertices_norm;
};
