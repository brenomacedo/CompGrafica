#pragma once

#include "./mesh.h"
#include "./CG.h"

class MeshWithTexture : public Mesh {
    private:
        Image* texture = nullptr;

    public:
        void setTexture(Image* texture);
        Image* getTexture();

        Color* getColorToBePainted(
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        MeshWithTexture();
        MeshWithTexture(Image* image, double shininess);
        ~MeshWithTexture();
};
