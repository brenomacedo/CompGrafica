#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main (int, char**) {

    Image* fundo = new Image("./assets/fundo.jpg");
    // Image* floorTexture = new Image("./assets/grama.jpg");

    // PlanWithTexture* plan1 = new PlanWithTexture(
    //     floorTexture,
    //     new Vector(0, -150, 0),
    //     new Vector(0, 1, 0),
    //     5.0
    // );

    Plan* plan1 = new Plan(
        new Vector(0, 0, 0),
        new Vector(0, 1, 0),
        new Vector(0.2, 0.7, 0.7),
        5.0
    );

    Sphere* sphere = new Sphere(
        25, new Vector(0.9, 0, 0),
        new Vector(0, 25, 0), 5.0
    );

    Light* light = new PointLight(
        new Vector (0.7, 0.7, 0.7),
        new Vector(350, 350, -150)
    );

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
    scene->addObject(sphere);

    scene->setBackgroundImage(fundo);
    scene->lookAt(
        new Vector(400, 400, 400),
        new Vector(0, 25, 0),
        new Vector(400, 500, 400)
    );

    // scene->setProjectionType(ProjectionType::PARALLEL);

    scene->render();

    return 0;
}
