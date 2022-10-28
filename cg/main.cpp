#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Image* floorTexture = new Image("./assets/madeira.jpg");

    PlanWithTexture* plan1 = new PlanWithTexture(
        floorTexture,
        new Vector(0, -100, 0),
        new Vector(0, 1, 0),
        5.0
    );

    Sphere* sphere = new Sphere(
        30, new Vector(0.2, 0.7, 0.7),
        new Vector(0, -70, -150), 5.0
    );

    Light* spotLight = new SpotLight(
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, -1, 0),
        new Vector (0, 100, -170),
        M_PI / 8
    );

    Sp<Scene> scene = new Scene (
        60.0, 60.0,
        800, 800,
        20,
        new Color (0, 0, 0, 255)
    );

    scene->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 70, -150),
        new Vector(0, 100, 0)
    );

    scene->setBackgroundImage(new Image("./assets/arca.jpg"));

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );
    
    scene->addLightSource(spotLight);
    scene->addObject(plan1);
    scene->addObject(sphere);

    scene->render();

    return 0;
}
