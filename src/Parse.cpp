
#include "../include/Parse.h"
#include <sstream>
#include <string>
#include <stack>

std::vector<Eigen::Vector3f> Parse::vertices;
std::vector<vert_norm> Parse::vertices_norm;
std::string Parse::cur_cmd;
uint Parse::cur_line;

void right_multiply(const Eigen::Matrix4f& M, std::stack<Eigen::Matrix4f> &t_stack){
  Eigen::Matrix4f &T = t_stack.top();
  T = T * M;
}

void Parse::parse_file(Scene* scene, const char* file_name){
    std::ifstream file(file_name);
    std::string line;

    if(!file.is_open()){
        std::cerr << "Unable to open file: " << file_name << std::endl;
        exit(1);
    }

    std::stack<Eigen::Matrix4f> t_stack;
    std::stack<Eigen::Matrix4f> inv_t_stack;
    t_stack.push(Eigen::Matrix4f::Identity());// t_stack.push(Eigen::Matrix4f(1.0));
    inv_t_stack.push(Eigen::Matrix4f::Identity());

    Eigen::Vector3f diffuse;
    diffuse.setZero();
    Eigen::Vector3f specular;
    specular.setZero();
    Eigen::Vector3f emission;
    emission.setZero();
    float shininess = 0.0;
    Eigen::Vector3f ambient;
    ambient.setZero();



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
            std::string out_file;
            ss >> out_file;
            scene->out_file = out_file.c_str();

        }
        //verticies
        else if(cmd == "vertex"){
            read_vals(ss, 3, vals);
            vertices.push_back(Eigen::Vector3f(vals[0],vals[1],vals[2]));
        }
        else if(cmd == "vertexnormal"){
            read_vals(ss, 6, vals);
            vertices_norm.push_back(vert_norm(Eigen::Vector3f(vals[0],vals[1],vals[2]),
                                  Eigen::Vector3f(vals[3],vals[4],vals[5])));
        }
        //triangle a b c
        else if(cmd == "tri"){
            read_vals(ss, 3, indices);

            Triangle t(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);
            t.transform = t_stack.top();
            t.inv_transform = inv_t_stack.top();

            t.diffuse = diffuse;
            t.specular = specular;
            t.shininess = shininess;
            t.emission = emission;
            t.ambient = ambient;
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
            t.shininess = shininess;
            t.emission = emission;
            t.ambient = ambient;
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
            s.shininess = shininess;
            s.emission = emission;
            s.ambient = ambient;

            // mm::print_vec(diffuse);
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

            Eigen::Matrix4f T = Transform::translate(tx,ty,tz);
            Eigen::Matrix4f Top = t_stack.top();
            t_stack.pop();
            t_stack.push(Top * T);

            Eigen::Matrix4f T_inv = Eigen::Matrix4f::Identity();

            // inv_T(T,T_inv);
            T_inv(0,3) = -T(0,3);
            T_inv(1,3) = -T(1,3);
            T_inv(2,3) = -T(2,3);

            Eigen::Matrix4f inv_t = inv_t_stack.top();
            inv_t_stack.pop();
            inv_t_stack.push(T_inv * inv_t);

        }

        else if(cmd == "rotate"){
            read_vals(ss,4,vals);
            Eigen::Vector3f axis(vals[0], vals[1], vals[2]);
            float degrees = vals[3];

            Eigen::Matrix3f R = Transform::rotate(degrees, axis);
            Eigen::Matrix4f R4 = Eigen::Matrix4f::Identity();

            for(int y=0; y<3; y++){
              for(int x=0; x<3; x++){
                R4(y,x) = R(y,x);
              }
            }

            Eigen::Matrix4f T = t_stack.top();
            t_stack.pop();
            t_stack.push(T * R4);

            Eigen::Matrix4f R_inv = Eigen::Matrix4f::Identity();
            //inv_R(R4,R_inv);
            R_inv = R4.transpose();

            Eigen::Matrix4f inv_t = inv_t_stack.top();
            inv_t_stack.pop();
            inv_t_stack.push(R_inv * inv_t);

        }

        else if(cmd == "scale"){
            read_vals(ss,3,vals);
            const float sx = vals[0];
            const float sy = vals[1];
            const float sz = vals[2];

            Eigen::Matrix4f Scale = Transform::scale(sx,sy,sz);
            Eigen::Matrix4f T = t_stack.top();
            t_stack.pop();
            t_stack.push(T * Scale);

            Eigen::Matrix4f S_inv = Scale;
            S_inv(0,0) = 1/S_inv(0,0);
            S_inv(1,1) = 1/S_inv(1,1);
            S_inv(2,2) = 1/S_inv(2,2);
            //inv_S(Scale,S_inv);
            Eigen::Matrix4f inv_t = inv_t_stack.top();
            inv_t_stack.pop();
            inv_t_stack.push(S_inv * inv_t);
        }

        else if (cmd == "pushTransform"){
            Eigen::Matrix4f t = t_stack.top();
            t_stack.push(t);

            Eigen::Matrix4f inv_t = inv_t_stack.top();
            inv_t_stack.push(inv_t);

            // std::cout << t_stack.size() << std::endl;
            // mm::print_mat(t_stack.top());

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
        else if(cmd == "directional"){
            //directional x y z r g b
            read_vals(ss,6,vals);
            float x = vals[0];
            float y = vals[1];
            float z = vals[2];

            float r = vals[3];
            float g = vals[4];
            float b = vals[5];

            Light l(Eigen::Vector3f(x,y,z), Eigen::Vector3f(r,g,b), false);
            scene->add_light(l);
        }
        else if(cmd == "point"){
            //point x y z r g b
            read_vals(ss,6,vals);
            float x = vals[0];
            float y = vals[1];
            float z = vals[2];

            float r = vals[3];
            float g = vals[4];
            float b = vals[5];

            Light l(Eigen::Vector3f(x,y,z), Eigen::Vector3f(r,g,b), true);
            scene->add_light(l);
        }
        else if(cmd == "attenuation"){
            //attenuation const linear quadratic

        }
        else if(cmd == "ambient"){
            //ambient r g b
            read_vals(ss,3,vals);
            ambient = Eigen::Vector3f(vals[0], vals[1], vals[2]);
        }
        //materials
        else if(cmd == "diffuse"){
            read_vals(ss,3,vals);
            diffuse = Eigen::Vector3f(vals[0], vals[1], vals[2]);
        }
        else if(cmd == "specular"){
            read_vals(ss,3,vals);
            specular = Eigen::Vector3f(vals[0], vals[1], vals[2]);

        }
        else if(cmd == "emission"){
            read_vals(ss,3,vals);
            emission = Eigen::Vector3f(vals[0], vals[1], vals[2]);
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

    }
    file.close();
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
