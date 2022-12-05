#pragma once

#include "./CG.h"

class Cylinder : public Object {

    private:
        ObjectType type = ObjectType::CYLINDER;
        Vector* baseCenter = nullptr;
        Vector* topCenter = nullptr;
        double radius;
        double height;
        Vector* direction = nullptr;

    public:
        Vector* initialBaseCenter = nullptr;
        Vector* initialTopCenter = nullptr;
        
        ObjectType getObjectType ();
        Vector* getBaseCenter ();
        Vector* getTopCenter ();
        void setRadius (double radius);
        double getRadius ();
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
        void applyWorldToCanvasConversion(LookAt* lookAt);

        void setBaseCenter (Vector* baseCenter);
        void setTopCenter (Vector* topCenter);
        void setHeight (double height);
        void setDirection (Vector* vector);
        void updateDirection();

        void applyScale(double sx, double sy, double sz);
        void applyTranslate(double x, double y, double z);
        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);
        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        bool isInside(Vector* point);

        Cylinder ();
        Cylinder (Vector* baseCenter, Vector* direction, double height, double radius);
        Cylinder (Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess = 1.0);
        Cylinder (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~Cylinder ();

};
