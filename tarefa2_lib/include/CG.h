#pragma once

#include <vector>

class Light {

};

class Object {

};

class Line {

};

class Vector {

};

class Color {

};

using ObjectsArray = std::vector<Object>;
using LightsArray = std::vector<Light>;

class Scene {
    private:
        // position where the eye is
        Vector* eyeCenter;

        // window height
        double windowHeight;

        // window width
        double windowWidth;

        // canvas width
        int canvasWidth;

        // canvas height
        int canvasHeight;

        // for a while, the window center will only be
        // placed in the Z axis with the normal being the Z axis
        // in the future, this may be updated to a more complex position
        double windowDistance;

        // set of objects in the scene
        ObjectsArray objects;

        // set of light sources in the scene
        LightsArray lights;

};