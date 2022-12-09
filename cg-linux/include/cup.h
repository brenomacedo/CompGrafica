#pragma once

#include "./CG.h"
#include "./mesh.h"
#include "./meshWithTexture.h"

class Cup {
    public:
        static Mesh* createWithBorderInCenaryCenter(Vector* reflectivity, double shininness);
        static MeshWithTexture* createWithBorderInCenaryCenterWithTexture(Image* image, double shininness);
};