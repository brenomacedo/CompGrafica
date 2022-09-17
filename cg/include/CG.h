#pragma once

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "./image.h"

using std::ostream;

class Object;
class Light;
class Vector;
using ObjectsArray = std::vector<Object*>;
using LightsArray = std::vector<Light*>;

// return the max of a and b
double min (double a, double b);

// return the min of a and b
double max (double a, double b);

// return the vector product of two vectors a and b
Vector vectorProduct (Vector a, Vector b);

enum class ObjectType { SHPERE, PLAN, CYLINDER, CONE };
enum class ObjectRegion { SPHERE_SURFACE, CYLINDER_SURFACE, CYLINDER_BASE, CYLINDER_TOP, PLAN, CONE_SURFACE, CONE_BASE, UNKNOWN };

// vector of 3 positions (x, y, z)
class Vector {
    private:
        double positions[3];

    public:
        // get the magnitude of vector: || vector ||
        double getMagnitude ();

        double& operator [] (int index);
        Vector operator + (const Vector& operand);
        Vector operator + (const double& operand);
        Vector operator - (const Vector& operand);
        Vector operator - (const double& operand);
        Vector operator * (const Vector& operand);
        Vector operator * (const double& operand);
        Vector operator / (const Vector& operand);
        Vector operator / (const double& operand);
        
        Vector ();
        Vector (double x, double y, double z);
};

ostream& operator << (ostream& os, Vector vector);

// returns the scalar product of two vectors
double scalarProduct (Vector a, Vector b);
// returns the scalar product of two vectors
double scalarProduct (Vector *a, Vector *b);

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

        // region of object that was intercepted by the ray
        ObjectRegion region;

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

        // set the object region
        void setObjectRegion (ObjectRegion region);

        // get the object region
        ObjectRegion getObjectRegion ();

        IntersectionResult operator = (const IntersectionResult& result);

        IntersectionResult ();
        IntersectionResult (bool hasIntersection, Vector* intersectionPoint, double distanceFromP0, ObjectRegion region);
        ~IntersectionResult ();
        IntersectionResult (const IntersectionResult& result);

};

class Line {
    public:
        // initial point of the line
        Vector* P0;

        // direction of the line
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
};

class Sphere : public Object {
    private:
        ObjectType type = ObjectType::SHPERE;

        // radius of the sphere
        double radius;

        // reflectivity of the sphere material
        Vector* reflectivity;

        // center of the sphere
        Vector* center;

        // shininess of the sphere (default to 1.0)
        double shininess = 1.0;

    public:
        // return the type of sphere
        ObjectType getObjectType ();

        // set the sphere radius
        void setRadius (double radius);

        // get the sphere radius
        double getRadius ();

        // set the sphere reflectivity
        void setReflectivity (Vector* reflectivity);

        // get the sphere reflectivity
        Vector* getReflectivity ();

        // set the sphere center
        void setCenter (Vector* center);

        // get the sphere center
        Vector* getCenter ();

        // set the sphere shininess
        void setShininess (double shininess);

        // get the sphere shininess
        double getShininess ();

        // get intersection of sphere and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Sphere ();
        Sphere (double radius, Vector* reflectivity, Vector* center, double shininess = 1.0);
        ~Sphere ();
        
};

class Plan : public Object {
    private:
        ObjectType type = ObjectType::PLAN;

        // reference point of the plan
        Vector* initialPoint = nullptr;

        // reflectivity of the sphere material
        Vector* reflectivity = nullptr;

        // normal of the plan
        Vector* normal = nullptr;

        // shininess of the sphere (default to 1.0)
        double shininess = 1.0;

    public:
        // return the type of plan
        ObjectType getObjectType ();

        // set the reference point of the plan
        void setInitialPoint (Vector* initialPoint);

        // get the reference point of the plan
        Vector* getInitialPoint ();

        // set the normal of the plan
        void setNormal (Vector* normal);

        // get the normal of the plan
        Vector* getNormal ();

        // set the plan reflectivity
        void setReflectivity (Vector* reflectivity);

        // get the plan reflectivity
        Vector* getReflectivity ();

        // set the plan shininess
        void setShininess (double shininess);

        // get the plan shininess
        double getShininess ();

        // get intersection of plan and a line
        IntersectionResult* getIntersectionResult (Line* line);

        // get color to be painted
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Plan ();
        Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess = 1.0);
        ~Plan ();
        
};

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

        // alpha = R^2 / H^2
        double alpha;

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

        // environment light of the scene
        Vector* environmentLight = nullptr;

        // background color of the scene
        // if the raycasting do not intercept any
        // object, the pixel will be painted with
        // this color (defaults to nullptr)
        Color* backgroundColor = nullptr;

        // background image of the scene
        // if the raycasting do not intercepy any
        // object, the pixel will be painted
        // with the color of the equivalent pixel
        // of the image (defaults to nullptr)
        //
        // obs: for a while, onyl supports jpg image
        // transparent images will be supported soon
        Image* backgroundImage = nullptr;

        // throw rays for each pixel of canvas
        // and verify if it has intersection with
        // an object and paint the pixel with the result color
        void raycast(SDL_Renderer* renderer);

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

        // set the background color of the scene
        void setBackgroundColor (Color* color);

        // set the background image of the scene
        void setBackgroundImage (Image* image);

        // set the environment light of the scene
        void setEnvironmentLight (Vector* environmentLight);

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

        // get the background color of the scene
        Color* getBackgroundColor ();

        // get the background image of the scene
        Image* getBackgroundImage ();

        // returns the vector that contains
        // the environment light
        Vector* getEnvironmentLight ();

        // returns a copy of the vector
        // with the POINTERS to light sources
        LightsArray getLights ();

        // returns a copy of the vector
        // with the POINTERS to objects
        ObjectsArray getObjects ();

        // open window and render the scene
        void render ();

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