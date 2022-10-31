#pragma once

#include "./CG.h"

class Sphere : public Object {
    private:
        ObjectType type = ObjectType::SPHERE;
        double radius;
        Vector* center;

    public:
        ObjectType getObjectType ();
        double getRadius ();
        Vector* getCenter ();
        IntersectionResult* getIntersectionResult (Line* line);
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );
        void applyWorldToCanvasConversion(LookAt* lookAt);

        void setRadius (double radius);
        void setCenter (Vector* center);

        Sphere ();
        Sphere (double radius, Vector* reflectivity, Vector* center, double shininess = 1.0);
        ~Sphere ();
        
};