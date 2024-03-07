
#include "../include/Parse.h"
#include <sstream>
#include <string>
#include <stack>

std::vector<mm::vec3> Parse::vertices;
std::vector<vert_norm> Parse::vertices_norm;
std::string Parse::cur_cmd;
uint Parse::cur_line;

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
    std::stack<mm::mat4> inv_t_stack;
    t_stack.push(mm::mat4(1.0));
    inv_t_stack.push(mm::mat4(1.0));

    mm::vec3 diffuse(0.0);
    mm::vec3 specular(0.0);
    mm::vec3 emission(0.0);
    float shininess = 0.0;


    cur_line = 0;
    while(std::getline(file, line)){
        cur_line++;
        if(line.empty()) continue;
        std::stringstream ss(line);

        std::string cmd;
        ss >> cmd;
        if(cmd == "#") continue;
        cur_cmd = cmd;

        float vals[10];
        int indices[5];

        //vertex x y z
        if(cmd == "size"){
            read_vals(ss, 2, vals);
            scene->width = vals[0];
            scene->height = vals[1];

        }
        else if(cmd == "maxdepth"){
            read_vals(ss, 1, vals);
            scene->maxdepth = vals[0];
        }
        else if(cmd == "output"){
            ss >> scene->out_file;
        }
        //verticies
        else if(cmd == "vertex"){
            read_vals(ss, 3, vals);
            vertices.push_back(mm::vec3(vals[0],vals[1],vals[2]));
        }
        else if(cmd == "vertexnormal"){
            read_vals(ss, 6, vals);
            vertices_norm.push_back(vert_norm(mm::vec3(vals[0],vals[1],vals[2]),
                                  mm::vec3(vals[3],vals[4],vals[5])));
        }
        //triangle a b c
        else if(cmd == "triangle"){
            read_vals(ss, 3, indices);

            Triangle t(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);
            t.transform = t_stack.top();
            t.inv_transform = inv_t_stack.top();

            t.diffuse = diffuse;
            t.specular = specular;
            t.emission = emission;
            t.shininess = shininess;
            scene->add_triangle(t);
        }
        else if(cmd == "trinormal"){
            read_vals(ss, 3, indices);
            vert_norm a = vertices_norm[indices[0]];
            vert_norm b = vertices_norm[indices[1]];
            vert_norm c = vertices_norm[indices[2]];
            Triangle t(a,b,c);

            t.transform = t_stack.top();
            t.inv_transform = inv_t_stack.top();

            t.diffuse = diffuse;
            t.specular = specular;
            t.emission = emission;
            t.shininess = shininess;
            scene->add_triangle(t);



        }
        //sphere x y z r
        else if(cmd == "sphere"){
            read_vals(ss, 4, vals);
            Sphere s(vals[0], vals[1], vals[2], vals[3]);
            s.transform = t_stack.top();
            s.inv_transform = inv_t_stack.top();

            s.diffuse = diffuse;
            s.specular = specular;
            s.emission = emission;
            s.shininess = shininess;
            scene->add_sphere(s);

        }

        else if(cmd == "camera"){
            read_vals(ss, 10, vals);
            Camera c(vals[0], vals[1], vals[2],
                     vals[3], vals[4], vals[5],
                     vals[6], vals[7], vals[8],
                     vals[9]);

            scene->camera = c;
        }

        else if(cmd == "translate"){
            read_vals(ss,3,vals);
            float tx = vals[0];
            float ty = vals[1];
            float tz = vals[2];

            mm::mat4 T = Transform::translate(tx,ty,tz);
            mm::mat4 &Top = t_stack.top();
            Top = Top * T;

            mm::mat4 T_inv(1.0);
            inv_T(T,T_inv);
            mm::mat4 &inv_t = inv_t_stack.top();
            inv_t = T_inv * inv_t;

        }

        else if(cmd == "rotate"){
            read_vals(ss,4,vals);
            mm::vec3 axis(vals[0], vals[1], vals[2]);
            float degrees = vals[3];

            mm::mat3 R = Transform::rotate(degrees, axis);
            mm::mat4 R4(1.0f);

            for(int y=0; y<3; y++){
              for(int x=0; x<3; x++){
                R4(y,x) = R(y,x);
              }
            }

            mm::mat4 &T = t_stack.top();
            T = T * R4;

            mm::mat4 R_inv(1.0);
            inv_R(R4,R_inv);
            mm::mat4 &inv_t = inv_t_stack.top();
            inv_t = R_inv * inv_t;

        }

        else if(cmd == "scale"){
            read_vals(ss,3,vals);
            const float sx = vals[0];
            const float sy = vals[1];
            const float sz = vals[2];

            mm::mat4 Scale = Transform::scale(sx,sy,sz);
            mm::mat4 &T = t_stack.top();
            T = T * Scale;

            mm::mat4 S_inv(1.0);
            inv_S(Scale,S_inv);
            mm::mat4 &inv_t = inv_t_stack.top();
            inv_t = S_inv * inv_t;
        }

        else if (cmd == "pushTransform"){
          t_stack.push(t_stack.top());
          inv_t_stack.push(inv_t_stack.top());

        }

        else if(cmd == "popTransform") {
          if (t_stack.size() <= 1) {
            std::cerr << "t_stack has no elements.  Cannot Pop" << std::endl;
          } else {
            t_stack.pop();
          }
          if (inv_t_stack.size() <= 1) {
            std::cerr << "inv_t_stack has no elements.  Cannot Pop" << std::endl;
          } else {
            inv_t_stack.pop();
          }
        }
        //lights
        // else if(cmd == "directional"){

        // }
        // else if(cmd == "point"){

        // }
        // else if(cmd == "attenuation"){

        // }
        // else if(cmd == "ambient"){

        // }
        //materials
        else if(cmd == "diffuse"){
            read_vals(ss,3,vals);
            diffuse = mm::vec3(vals[0], vals[1], vals[2]);
        }
        else if(cmd == "specular"){
            read_vals(ss,3,vals);
            specular = mm::vec3(vals[0], vals[1], vals[2]);

        }
        else if(cmd == "emission"){
            read_vals(ss,3,vals);
            emission = mm::vec3(vals[0], vals[1], vals[2]);
        }
        else if(cmd == "shininess"){
            read_vals(ss,1,vals);
            shininess = vals[0];
        }

        // else if(cmd == ""){

        // }
        // else if(cmd == ""){

        // }
        // else if(cmd == ""){

        // }

        // std::cout << cur_line << std::endl;
    }
    // file.close();
}




void Parse::read_vals(std::stringstream &ss, int num_vals, float* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail()){
            std::cerr << cur_line << ": " << cur_cmd << "\nFailed reading value " << i << " will skip\n";
            exit(1);
        }
    }
}

void Parse::read_vals(std::stringstream &ss, int num_vals, int* vals){
    for(int i=0; i<num_vals; i++){
        ss >> vals[i];
        if (ss.fail()){
            std::cerr << cur_line << ": " << cur_cmd << "\nFailed reading value " << i << " will skip\n";
            exit(1);
        }
    }
}
