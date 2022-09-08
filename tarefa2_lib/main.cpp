#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Sphere* sphere = new Sphere (
        20.0,
        new Vector (1, 0, 0),
        new Vector (0, 0, -80.0)
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

    scene->render();

    return 0;
}