#pragma once

#include "./CG.h"

class Cylinder : public Object {

    private:
        ObjectType type = ObjectType::CYLINDER;
        Vector* baseCenter = nullptr;
        Vector* topCenter = nullptr;
        double radius;
        Vector* reflectivity = nullptr;
        double shininess;
        double height;
        Vector* direction = nullptr;

    public:
        ObjectType getObjectType ();
        Vector* getBaseCenter ();
        Vector* getTopCenter ();
        void setRadius (double radius);
        double getRadius ();
        Vector* getReflectivity ();
        double getShininess ();
        double getHeight ();
        Vector* getDirection ();
        IntersectionResult* getIntersectionResult (Line* line);
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        void setBaseCenter (Vector* baseCenter);
        void setTopCenter (Vector* topCenter);
        void setReflectivity (Vector* reflectivity);
        void setShininess (double shininess);
        void setHeight (double height);
        void setDirection (Vector* vector);

        Cylinder ();
        Cylinder (Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess = 1.0);
        Cylinder (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~Cylinder ();

};
