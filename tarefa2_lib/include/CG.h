#pragma once

#include <vector>

enum class ObjectType { SHPERE, PLAN, CYLINDER };

// vector of 3 positions (x, y, z)
class Vector {
    public:
        double positions[3];

        double& operator [] (int index);
        Vector operator + (const Vector& operand);
        Vector operator + (const double& operand);
        Vector operator - (const Vector& operand);
        Vector operator - (const double& operand);
        Vector operator * (const Vector& operand);
        Vector operator * (const double& operand);
        Vector operator / (const Vector& operand);
        Vector operator / (const double& operand);
        Vector operator = (const Vector& operand);
        
        Vector (double x, double y, double z);
};

class Light {
    private:
        // intensity of the light source
        Vector* intensity = nullptr;

        // position of the light source
        Vector* position = nullptr;

    public:
        // set the intensity of the light
        void setIntensity (Vector* intensity);

        // set the position of the light
        void setPosition (Vector* position);

        // returns the pointer to the vector
        // that contains the intensity of the light
        Vector* getIntensity ();

        // returns the pointer to the vector
        // that contains the position of the light
        Vector* getPosition();

        Light ();
        Light (Vector* intensity, Vector* position);
        ~Light();
};

class IntersectionResult {
    private:
        // boolean that says if the line intercepted
        // the object
        bool hasIntersection;

        // vector that contains the point
        // of interception
        Vector* intersectionPoint = nullptr;

        // distance between the p0 of the line and the intersection point
        double distanceFromP0;

    public:
        // set if the line cross the object
        void setHasIntersection (bool hasIntersection);

        // set the intersection point of the line and the object
        void setIntersectionPoint (Vector* intersectionPoint);

        // returns if the line cross the object
        bool getHasIntersection ();

        // returns the point of intersection between
        // the line and the object
        Vector* getIntersectionPoint ();

        // set the distance between the p0 and the intersection point
        void setDistanceFromP0 (double distanceFromP0);

        // returns the distance between the p0 and the intersection point
        double getDistanceFromP0 ();

        IntersectionResult ();
        IntersectionResult (bool hasIntersection, Vector* intersectionPoint);
        ~IntersectionResult ();

};

class Object {
    protected:
        ObjectType type;
        
    public:
        virtual ObjectType getObjectType () = 0;
        virtual IntersectionResult* getIntersectionResult (Line line) = 0;
        virtual Color* getColorToBePainted (IntersectionResult* intersectionResult, LightsArray lightsArray);
};

class Line {
    public:
        // initial point of the line
        double P0;

        // direction of the line
        Vector* dir;

        Line (double P0, Vector* dir);
        ~Line();
        
};

class Color {
    public:
        // value of R (red) color (max to 255)
        int r;
        // value of G (green) color (max to 255)
        int g;
        // value of B (blue) color (max to 255)
        int b;
        // value of A (opacity) color (max to 255)
        int a;

        Color (int r, int g, int b, int a);
};

using ObjectsArray = std::vector<Object*>;
using LightsArray = std::vector<Light*>;

class Scene {
    private:
        // position where the eye is
        Vector* eyeCenter = nullptr;

        // window height (defaults to 100.0)
        double windowHeight = 100.0;

        // window width (defaults to 100.0)
        double windowWidth = 100.0;

        // canvas height (defaults to 400)
        int canvasHeight = 400;

        // canvas width (defaults to 400)
        int canvasWidth = 400;

        // for a while, the window center will only be
        // placed in the Z axis with the normal being the Z axis
        // in the future, this may be updated to a more complex position
        // (defaults to 50.0)
        double windowDistance = 50.0;

        // set of objects in the scene
        ObjectsArray objects;

        // set of light sources in the scene
        LightsArray lights;

        // background color of the scene
        // if the raycasting do not intercept any
        // object, the pixel will be painted with
        // this color (defaults to Color (0, 0, 0, 255))
        Color* backgroundColor = nullptr;

    public:
        // setters and getters

        // set the eye position in the scene
        void setEyeCenter (Vector* eyeCenter);

        // set the window's height
        void setWindowHeight (double windowHeight);

        // set the window's width
        void setWindowWidth (double windowWidth);

        // set the canvas width
        void setCanvasWidth (double canvasWidth);

        // set the canvas height
        void setCanvasHeight (double canvasHeight);

        // set the distance of the window to the eye
        // for a while, the window center will only be
        // placed in the Z axis with the normal being the Z axis
        // in the future, this may be updated to a more complex position
        void setWindowDistance (double windowDistance);

        void setBackgroundColor (Color* color);

        // add a light source to the scene
        void addLightSource (Light* lightSource);

        // add an object to the scene
        void addObject (Object* object);

        // returns the pointer to the vector that
        // represents the eye center in the scene
        Vector* getEyeCenter ();

        // returns the window height
        double getWindowHeight ();

        // returns the window width
        double getWindowWidth ();

        // returns the canvas width
        double getCanvasWidth ();

        // returns the canvas height
        double getCanvasHeight ();

        // returns the window distance to the eye
        double getWindowDistance ();

        // returns a copy of the vector
        // with the POINTERS to light sources
        LightsArray getLights ();

        // returns a copy of the vector
        // with the POINTERS to objects
        ObjectsArray getObjects ();

        Scene ();

        // eyeCenter: vector that represents the position of eye in the scene
        // windowHeight: height of the window
        // window width: width of the window
        // canvasHeight: height of the canvas
        // canvasWidth: width of the canvas
        // windowDistance: distance of the window to the eye
        // color: color of the background of the canvas
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