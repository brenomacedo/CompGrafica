#pragma once

#include "./CG.h"

class Sphere : public Object {
    private:
        ObjectType type = ObjectType::SPHERE;
        double radius;
        Vector* center;

    public:
        Vector* initialCenter = nullptr;

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

        void applyScale(double sx, double sy, double sz);
        void applyTranslate(double x, double y, double z);
        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);
        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        bool isInside(Vector* point);

        Sphere ();
        Sphere (double radius, Vector* center);
        Sphere (double radius, Vector* reflectivity, Vector* center, double shininess = 1.0);
        ~Sphere ();
        
};