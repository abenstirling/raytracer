
#include <iostream>

#include "../include/My_math.h"
#include "../include/Scene.h"

int main(int argc, char *argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <scene_file>" << std::endl;
    return 1;
  }

  Scene::load(argv[1]);

  mm::mat2 m(0.0, 0.1, 1.0, 1.1);
  mm::print_mat(m);
  m(0, 0) = 2.0;
  mm::print_mat(m);

  mm::vec2 v(1.0);
  mm::print_vec(v);
  v(1) = 9.0;
  mm::print_vec(v);

  return 0;
}
