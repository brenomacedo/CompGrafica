#pragma once

#include "./CG.h"

class Cone : public Object {

    private:
        // object type
        ObjectType type = ObjectType::CONE;

        // center of the cylinder base
        Vector* baseCenter = nullptr;

        // top of cylinder
        Vector* top = nullptr;

        // radius of cone
        double radius;

        // height of the cone
        double height;

        // cone direciton
        Vector* direction = nullptr;

        // cone shininess
        double shininess;

        // cos2angle
        double cos2angle;

        // cone reflectivity
        Vector* reflectivity = nullptr;

    public:
        // returns the type of object
        ObjectType getObjectType ();

        // returns the base center of cone
        Vector* getBaseCenter ();

        // set the base center of cone
        void setBaseCenter (Vector* baseCenter);

        // returns the cone top
        Vector* getTop ();

        // set the cone top
        void setTop (Vector* top);

        // returns the cone radius
        double getRadius ();

        // set the cone radius
        void setRadius (double radius);

        // returns the cone height
        double getHeight ();

        // set the cone height
        void setHeight (double height);

        // returns the cone direction
        Vector* getDirection ();

        // set the cone direction
        void setDirection (Vector* direction);

        // returns the cosin ^ 2 of cone angle
        double getCos2Angle ();

        // set the cosin ^ 2 of cone angle
        void setCos2Angle (double cos2angle);

        // returns the cone shininess
        double getShininess ();

        // set the cone shininess
        void setShininess (double shininess);

        // returns the cone reflectivity
        Vector* getReflectivity ();

        // set the cone reflectivity
        void setReflectivity (Vector* reflectivity);

        // get intersection of cone and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Cone ();
        Cone (Vector* baseCenter, Vector* top, double radius, Vector* reflectivity, double shininess);
        Cone (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~Cone ();

};