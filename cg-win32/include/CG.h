#pragma once

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "./image.h"
#include "./algebra.h"
#include "./interface.h"

class Object;
class Light;
class LookAt;
using ObjectsArray = std::vector<Object*>;
using LightsArray = std::vector<Light*>;

enum class ObjectType { SPHERE, PLAN, CYLINDER, CONE, MESH };
enum class ObjectRegion { SPHERE_SURFACE, CYLINDER_SURFACE, CYLINDER_BASE, CYLINDER_TOP, PLAN, CONE_SURFACE, CONE_BASE, UNKNOWN };
enum class ProjectionType { PARALLEL, PERSPECTIVE };

class Color {
    public:
        int r, g, b, a;
        Color(int r, int g, int b, int a);
};

class IlluminationInfo {
    public:
        Vector l;
        Vector intensity;

        IlluminationInfo();
        IlluminationInfo(Vector l, Vector intensity);
};

class Light {
    private:
        Vector* intensity = nullptr;
        bool active = true;
    public:
        void setActive(bool active);
        bool isActive();

        void setIntensity(Vector* intensity);
        Vector* getIntensity();
        virtual double getDistanceFromPoint(Vector point) = 0;
        virtual IlluminationInfo getIlluminationInfo(Vector intersectionPoint) = 0;
        virtual void applyWorldToCanvasConversion(LookAt* lookat) = 0;

        Light();
        Light(Vector* intensity);
        virtual ~Light();
};

class PointLight : public Light {
    private:
        Vector* position = nullptr;
    
    public:
        void setPosition(Vector* position);
        Vector* getPosition();
        double getDistanceFromPoint(Vector point);
        IlluminationInfo getIlluminationInfo(Vector intersectionPoint);
        virtual void applyWorldToCanvasConversion(LookAt* lookat);

        PointLight();
        PointLight(Vector* intensity, Vector* position);
        ~PointLight();
};

class DirectionalLight : public Light {
    private:
        Vector* direction = nullptr;

    public:
        void setDirection(Vector* direction);
        Vector* getDirection();
        double getDistanceFromPoint(Vector point);
        IlluminationInfo getIlluminationInfo(Vector intersectionPoint);
        virtual void applyWorldToCanvasConversion(LookAt* lookat);

        DirectionalLight();
        DirectionalLight(Vector* intensity, Vector* direction);
        ~DirectionalLight();
};

class SpotLight : public Light {
    private:
        Vector* direction = nullptr;
        Vector* position = nullptr;
        double angle;

    public:
        void setDirection(Vector* direction);
        Vector* getDirection();
        void setPosition(Vector* position);
        Vector* getPosition();
        void setAngle(double angle);
        double getAngle();
        
        double getDistanceFromPoint(Vector point);
        IlluminationInfo getIlluminationInfo(Vector intersectionPoint);
        virtual void applyWorldToCanvasConversion(LookAt* lookat);

        SpotLight();
        SpotLight(Vector* intensity, Vector* direction, Vector* position, double angle);
        ~SpotLight();
};

class IntersectionResult {
    private:
        bool hasIntersection;
        Vector* intersectionPoint = nullptr;
        double distanceFromP0;
        ObjectRegion region;

    public:
        void setHasIntersection(bool hasIntersection);
        void setIntersectionPoint(Vector* intersectionPoint);
        bool getHasIntersection();
        Vector* getIntersectionPoint();
        void setDistanceFromP0(double distanceFromP0);
        double getDistanceFromP0();
        void setObjectRegion(ObjectRegion region);
        ObjectRegion getObjectRegion();

        IntersectionResult operator =(const IntersectionResult& result);

        IntersectionResult();
        IntersectionResult(bool hasIntersection, Vector* intersectionPoint, double distanceFromP0, ObjectRegion region);
        virtual ~IntersectionResult();
        IntersectionResult(const IntersectionResult& result);

};

class Line {
    public:
        Vector* P0;
        Vector* dir;

        Line(Vector* P0, Vector* dir);
        ~Line();
};

class Object {
    protected:
        ObjectType type;
        Vector* kd = nullptr;
        Vector* ka = nullptr;
        Vector* ke = nullptr;
        double shininess = 1.0;

        Color* calculateColorToBePainted(
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight,
            Vector* normal,
            Vector* kd,
            Vector* ka,
            Vector* ke,
            double shininess
        );

        Vector calculateResultColorRate(
            Line* line,
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Vector* normal,
            Vector* kd,
            Vector* ke,
            double shininess
        );

        bool hasIntersectionWithOtherObjects(ObjectsArray objectsArray, Vector* intersectionPoint, Vector* l, Light* light);
        
    public:
        virtual ObjectType getObjectType() = 0;
        Vector* getKd();
        Vector* getKa();
        Vector* getKe();
        double getShininess();

        void setReflectivity(Vector* reflectivity);
        void setKd(Vector* kd);
        void setKa(Vector* ka);
        void setKe(Vector* ke);
        void setShininess(double shininess);

        virtual IntersectionResult* getIntersectionResult(Line* line) = 0;
        virtual Color* getColorToBePainted(
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        ) = 0;
        virtual void applyWorldToCanvasConversion(LookAt* lookat) = 0;

        virtual void applyScale(double sx, double sy, double sz) = 0;
        virtual void applyTranslate(double x, double y, double z) = 0;
        virtual void applyRotateX(double angle) = 0;
        virtual void applyRotateY(double angle) = 0;
        virtual void applyRotateZ(double angle) = 0;
        virtual void applyReflectXY() = 0;
        virtual void applyReflectXZ() = 0;
        virtual void applyReflectYZ() = 0;

        Object();
        Object(Vector* reflectivity);
        virtual ~Object();
};

class LookAt {
    private:
        Vector* eye = nullptr;
        Vector* at = nullptr;
        Vector* up = nullptr;

    public:
        void setEye(Vector* eye);
        Vector* getEye();
        void setAt(Vector* at);
        Vector* getAt();
        void setUp(Vector* up);
        Vector* getUp();

        Vector convertWorldVectorToCanvas(Vector worldVector);

        LookAt();
        LookAt(
            Vector* eye,
            Vector* at,
            Vector* up
        );
        ~LookAt();
};

class Scene {
    private:
        double windowHeight = 100.0;
        double windowWidth = 100.0;
        int canvasHeight = 400;
        int canvasWidth = 400;
        double windowDistance = 50.0;
        ProjectionType projectionType = ProjectionType::PERSPECTIVE;
    
        ObjectsArray objects;
        LightsArray lights;
        
        Vector* environmentLight = nullptr;
        Color* backgroundColor = nullptr;
        Image* backgroundImage = nullptr;
        
        Interface* interface = nullptr;
        LookAt* eyeLookAt = nullptr;

    public:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        void setWindowHeight(double windowHeight);
        void setWindowWidth(double windowWidth);
        void setCanvasWidth(double canvasWidth);
        void setCanvasHeight(double canvasHeight);
        void setWindowDistance(double windowDistance);
        void setBackgroundColor(Color* color);
        void setBackgroundImage(Image* image);
        void lookAt(
            Vector* eye,
            Vector* at,
            Vector* up
        );
        void setProjectionType(ProjectionType projectionType);

        void setEnvironmentLight(Vector* environmentLight);
        void addLightSource(Light* lightSource);
        void addObject(Object* object);

        double getWindowHeight();
        double getWindowWidth();
        double getCanvasWidth();
        double getCanvasHeight();
        double getWindowDistance();
        ProjectionType getProjectionType();

        Color* getBackgroundColor();
        Image* getBackgroundImage();
        
        Vector* getEnvironmentLight();
        LightsArray getLights();
        ObjectsArray getObjects();

        // open window and render the scene
        void render();
        void raycast();
        void update();

        Scene();
        Scene(
            double windowHeight,
            double windowWidth,
            int canvasHeight,
            int canvasWidth,
            double windowDistance,
            Color* backgroundColor = nullptr
        );
        ~Scene();

};
