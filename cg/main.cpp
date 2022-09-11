#include <iostream>
#include <string>
#include "./include/CG.h"
#include "./include/utils.impl.h"
#include "./include/pixels.h"

using std::string;



int main () {

    Image* image = new Image ("./assets/sasq.jpg");

    Cylinder* cylinder = new Cylinder (
        new Vector (0, 80, -150),
        new Vector (0, 85, -150),
        30.0,
        new Vector (0.2, 0.2, 0.2),
        5.0
    );

    Cylinder* cylinder2 = new Cylinder (
        new Vector (0, 85, -150),
        new Vector (0, 100, -150),
        25.0,
        new Vector (0.2, 0.2, 0.2),
        5.0
    );

    Sphere* sphere = new Sphere (
        40.0,
        new Vector (0.8, 0.8, 0.8),
        new Vector (0, 0, -160),
        10.0
    );

    Sphere* sphere2 = new Sphere (
        30.0,
        new Vector (0.8, 0.8, 0.8),
        new Vector (0, 60, -150),
        10.0
    );

    Sphere* eye1 = new Sphere (
        3.0,
        new Vector (0, 0, 0),
        new Vector (-15, 60, -120),
        10.0
    );

    Sphere* eye2 = new Sphere (
        3.0,
        new Vector (0, 0, 0),
        new Vector (15, 60, -120),
        10.0
    );

    Sphere* nose = new Sphere (
        3.0,
        new Vector (0.8, 0, 0),
        new Vector (0, 50, -120),
        10.0
    );

    Sphere* button1 = new Sphere (
        3.0,
        new Vector (0, 0.5, 0),
        new Vector (0, 0, -120),
        10.0
    );

    Sphere* button2 = new Sphere (
        3.0,
        new Vector (0, 0.5, 0),
        new Vector (0, 10, -122),
        10.0
    );

    Sphere* button3 = new Sphere (
        3.0,
        new Vector (0, 0.5, 0),
        new Vector (0, -10, -122),
        10.0
    );

    Plan* plan = new Plan (
        new Vector (0, -40, 0),
        new Vector (0, 1, 0),
        new Vector (0.2, 0.7, 0.2),
        1.0
    );

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 60, -30)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        1000, 1000,
        30,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );

    scene->addLightSource(light);
    scene->setBackgroundImage(image);
    scene->addObject(sphere);
    scene->addObject(sphere2);
    scene->addObject(eye1);
    scene->addObject(eye2);
    scene->addObject(nose);
    scene->addObject(button1);
    scene->addObject(button2);
    scene->addObject(button3);
    scene->addObject(cylinder);
    scene->addObject(cylinder2);
    scene->addObject(plan);

    scene->render();

    return 0;
}