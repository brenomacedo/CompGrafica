#pragma once

#include "./CG.h"

class Sphere : public Object {
    private:
        ObjectType type = ObjectType::SPHERE;
        double radius;
        Vector* reflectivity;
        Vector* center;
        double shininess = 1.0;

    public:
        ObjectType getObjectType ();
        double getRadius ();
        Vector* getReflectivity ();
        Vector* getCenter ();
        double getShininess ();
        IntersectionResult* getIntersectionResult (Line* line);
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        void setRadius (double radius);
        void setReflectivity (Vector* reflectivity);
        void setCenter (Vector* center);
        void setShininess (double shininess);

        Sphere ();
        Sphere (double radius, Vector* reflectivity, Vector* center, double shininess = 1.0);
        ~Sphere ();
        
};