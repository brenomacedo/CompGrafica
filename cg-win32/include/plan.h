#pragma once

#include "./CG.h"

class Plan : public Object {
    private:
        ObjectType type = ObjectType::PLAN;
        Vector* initialPoint = nullptr;
        Vector* normal = nullptr;

    public:
        ObjectType getObjectType ();
        Vector* getInitialPoint ();
        Vector* getNormal ();
        IntersectionResult* getIntersectionResult (Line* line);
        virtual Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        void setInitialPoint (Vector* initialPoint);
        void setNormal (Vector* normal);
        void applyWorldToCanvasConversion(LookAt* lookAt);

        void applyScale(double sx, double sy, double sz);
        void applyTranslate(double x, double y, double z);
        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);
        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        Plan ();
        Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        virtual ~Plan ();
        
};