
#include "../include/Parse.h"
#include <sstream>
#include <string>
#include <stack>

std::vector<mm::vec3> Parse::vertices;

void right_multiply(const mm::mat4& M, std::stack<mm::mat4> &t_stack){
  mm::mat4 &T = t_stack.top();
  T = T * M;
}

void Parse::parse_file(Scene* scene, const char* file_name){
    std::ifstream file(file_name);
    std::string line;

    if(!file.is_open()){
        std::cerr << "Unable to open file: " << file_name << std::endl;
        exit(1);
    }

    std::stack<mm::mat4> t_stack;
    t_stack.push(mm::mat4(1.0));

    while(std::getline(file, line)){
        if(line.empty()) continue;
        std::stringstream ss(line);

        std::string cmd;
        ss >> cmd;
        if(cmd == "#") continue;

        float vals[10];
        int indices[5];

        //vertex x y z
        if(cmd == "vertex"){
            read_vals(ss, 3, vals);
            vertices.push_back(mm::vec3(vals[0],vals[1],vals[2]));
        }
        //triangle a b c
        else if(cmd == "triangle"){
            read_vals(ss, 3, indices);

            Triangle t(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);
            scene->add_triangle(t);
        }
        //sphere x y z r
        else if(cmd == "sphere"){
            read_vals(ss, 4, vals);

            // mm::vec3 pos(vals[0], vals[1], vals[2]);
            Sphere s(vals[0], vals[1], vals[2], vals[3], t_stack.top());
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
            read_vals(ss,4,vals);
            mm::vec3 axis(vals[0], vals[1], vals[2]);
            float degrees = vals[3];

            mm::mat3 R  = Transform::rotate(degrees, axis);
            mm::mat4 R4(1.0f);

            for(int y=0; y<3; y++){
              for(int x=0; x<3; x++){
                R4(y,x) = R(y,x);
              }
            }

            right_multiply(R4,t_stack);
        }

        else if(cmd == "scale"){
            read_vals(ss,3,vals);
            float sx = vals[0];
            float sy = vals[1];
            float sz = vals[2];

            mm::mat4 S = Transform::scale(sx,sy,sz);
            right_multiply(S, t_stack);
        }

        else if (cmd == "pushTransform") {
          t_stack.push(t_stack.top());
        }

        else if (cmd == "popTransform") {
          if (t_stack.size() <= 1) {
            std::cerr << "Stack has no elements.  Cannot Pop" << std::endl;
          } else {
            t_stack.pop();
          }
        }

    }
    file.close();
}




void Parse::read_vals(std::stringstream &ss, int num_vals, float* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail())
            std::cerr << "Failed reading value " << i << " will skip\n";
    }
}

void Parse::read_vals(std::stringstream &ss, int num_vals, int* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail())
            std::cerr << "Failed reading value " << i << " will skip\n";
    }
}
