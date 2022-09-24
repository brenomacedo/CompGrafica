#pragma once

#include "./CG.h"

class Sphere : public Object {
    private:
        ObjectType type = ObjectType::SPHERE;

        // radius of the sphere
        double radius;

        // reflectivity of the sphere material
        Vector* reflectivity;

        // center of the sphere
        Vector* center;

        // shininess of the sphere (default to 1.0)
        double shininess = 1.0;

    public:
        // return the type of sphere
        ObjectType getObjectType ();

        // set the sphere radius
        void setRadius (double radius);

        // get the sphere radius
        double getRadius ();

        // set the sphere reflectivity
        void setReflectivity (Vector* reflectivity);

        // get the sphere reflectivity
        Vector* getReflectivity ();

        // set the sphere center
        void setCenter (Vector* center);

        // get the sphere center
        Vector* getCenter ();

        // set the sphere shininess
        void setShininess (double shininess);

        // get the sphere shininess
        double getShininess ();

        // get intersection of sphere and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Sphere ();
        Sphere (double radius, Vector* reflectivity, Vector* center, double shininess = 1.0);
        ~Sphere ();
        
};