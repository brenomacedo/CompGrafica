#pragma once

#include "./CG.h"
#include "./mesh.h"

class Cup {
    public:
        static Mesh* createWithBorderInCenaryCenter(Vector* reflectivity, double shininness);
};