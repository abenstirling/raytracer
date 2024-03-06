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
    static mm::mat4 inv_stack();
private:
    static std::vector<mm::vec3> vertices;

};
