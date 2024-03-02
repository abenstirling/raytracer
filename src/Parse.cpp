
#include "../include/Parse.h"
#include <sstream>
#include <string>




void Parse::parse_file(Scene* scene, const char* file_name){
    std::ifstream file(file_name);
    std::string line;
    if(!file.is_open()){
        std::cerr << "unabel to open file: " << file_name << std::endl;
        exit(1);
    }

    std::stack<mm::mat4> t_stack;
    t_stack.push(mm::mat4(1.0));


    while(std::getline(file, line)){
        std::string cmd;
        std::stringstream ss(line);
        ss >> cmd;

        float vals[10];
        int indices[3];

        if(cmd == "vertex"){
            read_vals(ss, 3, vals);
            vertices.push_back(mm::vec3(vals[0],vals[1],vals[2]));
        }
        else if(cmd == "triangle"){
            read_vals(ss, 3, indices);
            Triangle t(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);
            scene->add_triangle(t);
        }

        else if(cmd == "sphere"){
            read_vals(ss, 4, vals);
            Sphere s(vals[0], vals[1], vals[2], vals[3]);
            scene->add_sphere(s);
        }

        else if(cmd == "camera"){
            read_vals(ss, 10, vals);
            Camera c(vals[0], vals[1], vals[2],
                     vals[3], vals[4], vals[5],
                     vals[6], vals[7], vals[8],
                     vals[9]);
            scene->add_camera(c);
        }

        else if(cmd == "translate"){
            read_vals(ss,3,vals);
            float tx = vals[0];
            float ty = vals[1];
            float tz = vals[2];

            mm::mat4 T = Transform::translate(tx,ty,tz);
            right_multiply(T, t_stack);

        }

        else if(cmd == "rotate"){

        }

        else if(cmd == "scale"){

        }
    }
}




void Parse::read_vals(std::stringstream &ss,int num_vals, float* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail())
            std::cerr << "Failed reading value " << i << " will skip\n";
    }
}

void Parse::read_vals(std::stringstream &ss,int num_vals, int* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail())
            std::cerr << "Failed reading value " << i << " will skip\n";
    }
}
