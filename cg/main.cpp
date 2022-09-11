#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Image* image = new Image ("./assets/cenario.jpg");

    Cylinder* cylinder = new Cylinder (
        new Vector (0, 20, -100),
        new Vector (0, 40, -100),
        20.0,
        new Vector (0.9, 0.2, 0.2),
        5.0
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        500, 500,
        30,
        new Color (100, 100, 100, 255)
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 60, -30)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );

    scene->addLightSource(light);
    scene->addObject(cylinder);

    scene->render();

    return 0;
}