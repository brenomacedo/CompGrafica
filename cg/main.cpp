#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Mesh* mesh = Cube::create(
        new Vector(70, 70, -165),
        40,
        new Vector(1.0, 0.078, 0.576),
        5.0
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 60, 0)
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

    scene->setBackgroundImage(
        new Image("./assets/sasq.jpg")
    );
    scene->addLightSource(light);
    scene->addObject(mesh);

    scene->render();

    return 0;
}
