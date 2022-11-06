#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Image* floorTexture = new Image("./assets/madeira.jpg");

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

    Mesh* cube = Cube::create(new Vector(60, -150, -100), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube1 = Cube::create(new Vector(60, -150, -100), 30, new Vector(0,0.5,1), 5.0);
    cube1->applyReflectYZ();

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
    scene->addObject(plan1);
    scene->addObject(cube);
    scene->addObject(cube1);

    scene->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 0, -1),
        new Vector(0, 1, 0)
    );

    // scene->setProjectionType(ProjectionType::PARALLEL);

    scene->render();

    return 0;
}
