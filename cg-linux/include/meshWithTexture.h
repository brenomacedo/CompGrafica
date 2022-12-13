#pragma once

#include "./mesh.h"
#include "./CG.h"

class MeshWithTexture : public Mesh {
    private:
        ObjectType type = ObjectType::MESH_WITH_TEXTURE;
        Image* texture = nullptr;
        bool active = true;

    public:
        void setTexture(Image* texture);
        Image* getTexture();

        bool isActive();
        void setActive(bool active);
        ObjectType getObjectType();

        Color* getColorToBePainted(
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight,
            bool isEnvironmentLightActive
        );

        MeshWithTexture();
        MeshWithTexture(Image* image, double shininess);
        ~MeshWithTexture();
};
