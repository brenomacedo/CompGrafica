#pragma once

#include "./CG.h"

class Plan : public Object {
    private:
        ObjectType type = ObjectType::PLAN;
        Vector* initialPoint = nullptr;
        Vector* reflectivity = nullptr;
        Vector* normal = nullptr;
        double shininess = 1.0;

    public:
        ObjectType getObjectType ();
        Vector* getInitialPoint ();
        Vector* getNormal ();
        Vector* getReflectivity ();
        double getShininess ();
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
        void setReflectivity (Vector* reflectivity);
        void setShininess (double shininess);

        Plan ();
        Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        ~Plan ();
        
};