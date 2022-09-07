#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Sphere* sphere = new Sphere (
        20.0,
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 0, -80.0)
    );

    Sphere* sphere2 = new Sphere (
        20.0,
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 20, -80.0)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        100.0, 100.0,
        500, 500,
        50,
        new Color (0, 0, 0, 255)
    );

    scene->addObject(sphere);
    scene->addObject(sphere2);

    scene->render();

    return 0;
}