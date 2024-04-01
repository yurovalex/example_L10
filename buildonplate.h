#pragma once

#include <iostream>
#include "baseopengl.h"
#include <list>

class BuildOnPlate
{
private:
    BaseOpenGL *objGL;
    double WIDTH, HEIGHT;
public:
    BuildOnPlate(BaseOpenGL &tmp, double w, double h):
        objGL{&tmp}, WIDTH{w}, HEIGHT{h}
    {
    }
    double normalize(double value, double min, double max);
    void DrawEllipse();
    void DrawHyperbola();
};


