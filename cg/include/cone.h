#pragma once

#include "./CG.h"

class Cone : public Object {

    private:
        ObjectType type = ObjectType::CONE;
        Vector* baseCenter = nullptr;
        Vector* top = nullptr;
        double radius;
        double height;
        Vector* direction = nullptr;
        double shininess;
        double cos2angle;
        Vector* reflectivity = nullptr;

    public:
        ObjectType getObjectType ();
        void setBaseCenter (Vector* baseCenter);
        Vector* getTop ();
        double getRadius ();
        double getHeight ();
        Vector* getDirection ();
        double getCos2Angle ();
        double getShininess ();
        Vector* getReflectivity ();

        Vector* getBaseCenter ();
        void setTop (Vector* top);
        void setRadius (double radius);
        void setHeight (double height);
        void setDirection (Vector* direction);
        void setCos2Angle (double cos2angle);
        void setShininess (double shininess);
        void setReflectivity (Vector* reflectivity);
        IntersectionResult* getIntersectionResult (Line* line);

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