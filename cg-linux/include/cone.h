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
        double cos2angle;

    public:
        Vector* initialBaseCenter = nullptr;
        Vector* initialTop = nullptr;

        ObjectType getObjectType ();
        void setBaseCenter (Vector* baseCenter);
        Vector* getTop ();
        double getRadius ();
        double getHeight ();
        Vector* getDirection ();
        double getCos2Angle ();
        void applyWorldToCanvasConversion(LookAt* lookAt);
        void updateDirection();

        Vector* getBaseCenter ();
        void setTop (Vector* top);
        void setRadius (double radius);
        void setHeight (double height);
        void setDirection (Vector* direction);
        void setCos2Angle (double cos2angle);
        IntersectionResult* getIntersectionResult (Line* line);

        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight,
            bool isEnvironmentLightActive
        );

        void applyScale(double sx, double sy, double sz);
        void applyTranslate(double x, double y, double z);
        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);
        void applyReflectXY();
        void applyReflectXZ();
        void applyReflectYZ();

        Cone ();
        Cone (Vector* baseCenter, Vector* top, double radius, Vector* reflectivity, double shininess);
        Cone (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess = 1.0);
        ~Cone ();

};