#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Cone* cone = new Cone (
        new Vector (0, -50, -100),
        new Vector (0, 0, -150),
        20.0,
        new Vector (0.2, 0.2, 0.7),
        5.0
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 0, -30)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        600, 600,
        30,
        new Color (100, 100, 100, 255)
    );

    scene->addLightSource(light);
    scene->addObject(cone);

    scene->render();

    return 0;
}