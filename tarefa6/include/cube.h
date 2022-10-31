#pragma once

#include "./CG.h"
#include "./mesh.h"

class Cube {
    public:
        static Mesh* create(Vector* baseCenter, double edgeSize, Vector* reflectivity, double shininness);
        static Mesh* createUnitaryWithBorderInCenaryCenter(Vector* reflectivity, double shininness);
};