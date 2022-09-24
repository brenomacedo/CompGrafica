#pragma once

#include "./CG.h"

class Cylinder : public Object {

    private:
        // get the type of object
        ObjectType type = ObjectType::CYLINDER;

        // center of the cylinder base
        Vector* baseCenter = nullptr;

        // center of the cylinder top
        Vector* topCenter = nullptr;

        // radius of the cylinder
        double radius;

        // reflectivity of cylinder
        Vector* reflectivity = nullptr;

        // shininess of cylinder
        double shininess;

        // height of cylinder
        double height;

        // cylinder direction
        Vector* direction = nullptr;

    public:
        // return the type of plan
        ObjectType getObjectType ();

        // set the base center of cylinder
        void setBaseCenter (Vector* baseCenter);

        // get the base center of cylinder
        Vector* getBaseCenter ();

        // set the top center of cylinder top
        void setTopCenter (Vector* topCenter);

        // get the top center of cylinder top
        Vector* getTopCenter ();

        // set the radius of cylinder
        void setRadius (double radius);

        // get the radius of cylinder
        double getRadius ();

        // set the reflectivity of cylinder
        void setReflectivity (Vector* reflectivity);

        // get the reflectivity of cylinder
        Vector* getReflectivity ();

        // set the shininess of cylinder
        void setShininess (double shininess);

        // get the shininess of cylinder
        double getShininess ();

        // set the height of cylinder
        void setHeight (double height);

        // get the height of cylinder
        double getHeight ();

        // set the cylinder direction
        void setDirection (Vector* vector);

        // get the cylinder direction
        Vector* getDirection ();

        // get intersection of cylinder and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Cylinder ();
        Cylinder (Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess = 1.0);
        Cylinder (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~Cylinder ();

};