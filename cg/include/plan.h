#pragma once

#include "./CG.h"

class Plan : public Object {
    private:
        ObjectType type = ObjectType::PLAN;

        // reference point of the plan
        Vector* initialPoint = nullptr;

        // reflectivity of the sphere material
        Vector* reflectivity = nullptr;

        // normal of the plan
        Vector* normal = nullptr;

        // shininess of the sphere (default to 1.0)
        double shininess = 1.0;

    public:
        // return the type of plan
        ObjectType getObjectType ();

        // set the reference point of the plan
        void setInitialPoint (Vector* initialPoint);

        // get the reference point of the plan
        Vector* getInitialPoint ();

        // set the normal of the plan
        void setNormal (Vector* normal);

        // get the normal of the plan
        Vector* getNormal ();

        // set the plan reflectivity
        void setReflectivity (Vector* reflectivity);

        // get the plan reflectivity
        Vector* getReflectivity ();

        // set the plan shininess
        void setShininess (double shininess);

        // get the plan shininess
        double getShininess ();

        // get intersection of plan and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Plan ();
        Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        ~Plan ();
        
};