#pragma once

#include "./plan.h"

class PlanWithTexture : public Plan {
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

        PlanWithTexture();
        PlanWithTexture(Image* texture, Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        ~PlanWithTexture();
};
