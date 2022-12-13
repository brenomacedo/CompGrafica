#pragma once

#include "./plan.h"

class PlanWithTexture : public Plan {
    private:
        ObjectType type = ObjectType::PLAN_WITH_TEXTURE;
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

        PlanWithTexture();
        PlanWithTexture(Image* texture, Vector* initialPoint, Vector* normal, double shininess = 1.0);
        ~PlanWithTexture();
};
