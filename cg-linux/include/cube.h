#pragma once

#include "./CG.h"
#include "./mesh.h"
#include "./meshWithTexture.h"

class Cube {
    public:
        static Mesh* create(Vector* baseCenter, double edgeSize, Vector* reflectivity, double shininness);
        static Mesh* createUnitaryWithBorderInCenaryCenter(Vector* reflectivity, double shininness);
        static Mesh* createWithTexture(Vector* baseCenter, double edgeSize, Image* image, double shininness);
};