#include "Scene.h"
#include <fstream>
#include <iostream>
#include <sstream>

struct Camera {
  float eye[3];
  float lookat[3];
  float up[3];
  float fov;
};

Scene::Scene() {}

Scene::~Scene() {}

Scene::load(const char *filename) {
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;
    parseLine(line);
  }
