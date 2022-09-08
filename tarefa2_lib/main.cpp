#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Sphere* sphere = new Sphere (
        20.0,
        new Vector (1, 1, 1),
        new Vector (0, 0, -80.0)
    );

    Sphere* sphere2 = new Sphere (
        15.0,
        new Vector (1, 1, 1),
        new Vector (0, 30, -80)
    );

    Sphere* eye1 = new Sphere (
        2.0,
        new Vector (0, 0, 0),
        new Vector (5, 30, -60)
    );

    Sphere* eye2 = new Sphere (
        2.0,
        new Vector (0, 0, 0),
        new Vector (-5, 30, -60)
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 5, 0)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        100.0, 100.0,
        500, 500,
        50,
        new Color (100, 100, 100, 255)
    );

    scene->addLightSource(light);
    scene->addObject(sphere);
    scene->addObject(sphere2);
    scene->addObject(eye1);
    scene->addObject(eye2);

    scene->render();

    return 0;
}