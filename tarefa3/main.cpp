#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Sphere* sphere = new Sphere (
        40.0,
        new Vector (0.7, 0.2, 0.2),
        new Vector (0, 0, -100),
        10.0
    );

    Plan* plan = new Plan (
        new Vector (0, -40, 0),
        new Vector (0, 1, 0),
        new Vector (0.2, 0.7, 0.2),
        1.0
    );

    Plan* plan2 = new Plan (
        new Vector (0, 0, -200),
        new Vector (0, 0, 1),
        new Vector (0.3, 0.3, 0.7),
        1.0
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 60, -30)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        500, 500,
        30,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );

    scene->addLightSource(light);
    scene->addObject(sphere);
    scene->addObject(plan);
    scene->addObject(plan2);

    scene->render();

    return 0;
}