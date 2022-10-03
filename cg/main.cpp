#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Plan* plan1 = new Plan(
        new Vector(0, -170, 0),
        new Vector(0, 1, 0),
        new Vector(0.686, 0.933, 0.933),
        5.0
    );

    Plan* plan2 = new Plan(
        new Vector(200, -150, 0),
        new Vector(-1, 0, 0),
        new Vector(0.686, 0.933, 0.933),
        5.0
    );

    Plan* plan3 = new Plan(
        new Vector(200, -150, -400),
        new Vector(0, 0, 1),
        new Vector(0.686, 0.933, 0.933),
        5.0
    );

    Plan* plan4 = new Plan(
        new Vector(-200, -150, 0),
        new Vector(1, 0, 0),
        new Vector(0.686, 0.933, 0.933),
        5.0
    );

    Plan* plan5 = new Plan(
        new Vector(0, 150, 0),
        new Vector(0, -1, 0),
        new Vector(0.686, 0.933, 0.933),
        5.0
    );

    Mesh* mesh = Cube::create(
        new Vector(0, -170, -165),
        40,
        new Vector(1.0, 0.078, 0.576),
        5.0
    );

    Sphere* sphere = new Sphere(
        5, new Vector(0.854, 0.647, 0.125),
        new Vector(0, 95, -200), 5.0
    );

    Light* light = new Light(
        new Vector (0.7, 0.7, 0.7),
        new Vector (-100, 140, -20)
    );

    Cone* cone = new Cone(
        new Vector(0, -60, -200),
        new Vector(0, 1, 0),
        150, 90,
        new Vector(0, 1, 0.498),
        5.0
    );

    Cylinder* cylinder = new Cylinder(
        new Vector(0, -150, -200),
        new Vector(0, 1, 0),
        90, 5,
        new Vector(0.824, 0.706, 0.549),
        5.0
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        500, 500,
        20,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );
    
    scene->addLightSource(light);
    scene->addObject(plan1);
    scene->addObject(plan2);
    scene->addObject(plan3);
    scene->addObject(plan4);
    scene->addObject(plan5);
    scene->addObject(cylinder);
    scene->addObject(sphere);
    scene->addObject(cone);
    scene->addObject(mesh);

    scene->render();

    return 0;
}
