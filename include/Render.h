#pragma once

#include "My_math.h"
#include "Scene.h"


class Render{
public:
    Render(Scene* scene);
    ~Render();

public:
    void compute();

};
