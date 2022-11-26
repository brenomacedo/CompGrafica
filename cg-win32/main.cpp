#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main (int, char**) {

    Image* floorTexture = new Image("./assets/grama.jpg");

    PlanWithTexture* plan1 = new PlanWithTexture(
        floorTexture,
        new Vector(0, -150, 0),
        new Vector(0, 1, 0),
        5.0
    );

    Light* light = new PointLight(
        new Vector (0.7, 0.7, 0.7),
        new Vector(350, 350, -150)
    );

    Mesh* cube = Cube::createWithTexture(new Vector(60, -150, -200), 30, floorTexture, 5.0);
    cube->setWrapper(new Cylinder(new Vector(60, -150, -200), new Vector(0, 1, 0), 30, 60));

    // cube->applyReflectYZ();

    Sp<Scene> scene = new Scene (
        60.0, 60.0,
        500, 500,
        20,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );
    
    scene->addLightSource(light);
    // scene->addObject(plan1);
    scene->addObject(cube);

    scene->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 0, -1),
        new Vector(0, 1, 0)
    );

    // scene->setProjectionType(ProjectionType::PARALLEL);

    scene->render();

    return 0;
}
