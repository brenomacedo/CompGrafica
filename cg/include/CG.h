#pragma once

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "./image.h"
#include "./algebra.h"

class Object;
class Light;
using ObjectsArray = std::vector<Object*>;
using LightsArray = std::vector<Light*>;

enum class ObjectType { SPHERE, PLAN, CYLINDER, CONE, MESH };
enum class ObjectRegion { SPHERE_SURFACE, CYLINDER_SURFACE, CYLINDER_BASE, CYLINDER_TOP, PLAN, CONE_SURFACE, CONE_BASE, UNKNOWN };

class Color {
    public:
        int r, g, b, a;
        Color (int r, int g, int b, int a);
};

class Light {
    private:
        Vector* intensity = nullptr;
        Vector* position = nullptr;

    public:
        void setIntensity (Vector* intensity);
        void setPosition (Vector* position);
        
        Vector* getIntensity ();
        Vector* getPosition();

        Light ();
        Light (Vector* intensity, Vector* position);
        ~Light();
};

class IntersectionResult {
    private:
        bool hasIntersection;
        Vector* intersectionPoint = nullptr;
        double distanceFromP0;
        ObjectRegion region;

    public:
        void setHasIntersection (bool hasIntersection);
        void setIntersectionPoint (Vector* intersectionPoint);
        bool getHasIntersection ();
        Vector* getIntersectionPoint ();
        void setDistanceFromP0 (double distanceFromP0);
        double getDistanceFromP0 ();
        void setObjectRegion (ObjectRegion region);
        ObjectRegion getObjectRegion ();

        IntersectionResult operator = (const IntersectionResult& result);

        IntersectionResult ();
        IntersectionResult (bool hasIntersection, Vector* intersectionPoint, double distanceFromP0, ObjectRegion region);
        virtual ~IntersectionResult ();
        IntersectionResult (const IntersectionResult& result);

};

class Line {
    public:
        Vector* P0;
        Vector* dir;

        Line (Vector* P0, Vector* dir);
        ~Line();
};

class Object {
    protected:
        ObjectType type;
        Vector* reflectivity;
        double shininess;
        
    public:
        virtual ObjectType getObjectType () = 0;
        virtual IntersectionResult* getIntersectionResult (Line* line) = 0;
        virtual Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        ) = 0;

        static Color* calculateColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight,
            Vector* normal,
            Vector* reflectivity,
            double shininess,
            Object* objAddr
        );

        virtual ~Object ();
};

class Scene {
    private:
        Vector* eyeCenter = nullptr;
        double windowHeight = 100.0;
        double windowWidth = 100.0;
        int canvasHeight = 400;
        int canvasWidth = 400;
        double windowDistance = 50.0;
    
        ObjectsArray objects;
        LightsArray lights;
        
        Vector* environmentLight = nullptr;
        Color* backgroundColor = nullptr;
        Image* backgroundImage = nullptr;
        
        void raycast(SDL_Renderer* renderer);

    public:
        void setEyeCenter (Vector* eyeCenter);
        void setWindowHeight (double windowHeight);
        void setWindowWidth (double windowWidth);
        void setCanvasWidth (double canvasWidth);
        void setCanvasHeight (double canvasHeight);
        void setWindowDistance (double windowDistance);
        void setBackgroundColor (Color* color);
        void setBackgroundImage (Image* image);
        
        void setEnvironmentLight (Vector* environmentLight);
        void addLightSource (Light* lightSource);
        void addObject (Object* object);
        
        Vector* getEyeCenter ();
        double getWindowHeight ();
        double getWindowWidth ();
        double getCanvasWidth ();
        double getCanvasHeight ();
        double getWindowDistance ();
        
        Color* getBackgroundColor ();
        Image* getBackgroundImage ();
        
        Vector* getEnvironmentLight ();
        LightsArray getLights ();
        ObjectsArray getObjects ();

        // open window and render the scene
        void render ();

        Scene ();
        Scene (
            Vector* eyeCenter,
            double windowHeight,
            double windowWidth,
            int canvasHeight,
            int canvasWidth,
            double windowDistance,
            Color* backgroundColor = nullptr
        );
        ~Scene ();

};
