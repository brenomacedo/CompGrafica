#pragma once

#include "./cylinder.h"

class CylinderWithTextureOnTop : public Cylinder {
    private:
        ObjectType type = ObjectType::CYLINDER_WITH_TEXTURE_ON_TOP;
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
            Vector* environmentLight
        );

        CylinderWithTextureOnTop();
        CylinderWithTextureOnTop(Image* texture, Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess = 1.0);
        CylinderWithTextureOnTop(Image* texture, Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~CylinderWithTextureOnTop();
};
