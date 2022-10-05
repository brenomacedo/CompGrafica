#pragma once

#include "./CG.h"

class Plan : public Object {
    private:
        ObjectType type = ObjectType::PLAN;
        Vector* initialPoint = nullptr;
        Vector* normal = nullptr;

    public:
        ObjectType getObjectType ();
        Vector* getInitialPoint ();
        Vector* getNormal ();
        IntersectionResult* getIntersectionResult (Line* line);
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        void setInitialPoint (Vector* initialPoint);
        void setNormal (Vector* normal);

        Plan ();
        Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        ~Plan ();
        
};