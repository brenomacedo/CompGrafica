#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

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

    // Sphere* sphere = new Sphere(
    //     25, new Vector(0.9, 0, 0),
    //     new Vector(0, 25, 0), 5.0
    // );

    // Cylinder* sphere = new Cylinder(
    //     new Vector(0, 0, 0),
    //     new Vector(0, 1, 0),
    //     50, 25, new Vector(0.9, 0, 0),
    //     5.0
    // );

    // Cone* sphere = new Cone(
    //     new Vector(0, 0, 0),
    //     new Vector(0, 1, 0),
    //     50, 25, new Vector(0.9, 0, 0),
    //     5.0
    // );

    Mesh* sphere = Cube::create(
        new Vector(0, 0, 0), 30,
        new Vector(0.9, 0, 0), 5.0
    );
    sphere->setWrapper(
        new Cylinder(
            new Vector(0, 0, 0),
            new Vector(0, 1, 0),
            50,
            50
        )
    );
    Sphere* sp = new Sphere(
        5, new Vector(0.8, 0.8, 0.8), new Vector(0, 35, 0), 5.0
    );

    // Mesh* sphere = Cup::createWithBorderInCenaryCenter(
    //     new Vector(0.9, 0, 0), 5.0
    // );
    // sphere->setWrapper(
    //     new Cylinder(
    //         new Vector(5, 0, 5),
    //         new Vector(0, 1, 0),
    //         10,
    //         40
    //     )
    // );
    // sphere->applyReflectYZ();


    Light* light = new PointLight(
        new Vector (0.3, 0.3, 0.3),
        new Vector(350, 350, -150)
    );

    Light* slight = new SpotLight(
        new Vector(0.3, 0.3, 0.3),
        new Vector(0, -1, 0),
        new Vector(0, 100, 0),
        M_PI / 4
    );

    Light* dlight = new DirectionalLight(
        new Vector(0.3, 0.3, 0.3),
        new Vector(1, -1, 1)
    );

    Sp<Scene> scene = new Scene (
        60.0, 60.0,
        400, 400,
        150,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );
    
    scene->addLightSource(light);
    scene->addLightSource(dlight);
    scene->addLightSource(slight);
    // scene->addObject(plan1);
    scene->addObject(sphere);
    scene->addObject(sp);

    // scene->setBackgroundImage(fundo);
    scene->lookAt(
        new Vector(400, 400, 400),
        new Vector(0, 25, 0),
        new Vector(0, 500, 0)
    );

    scene->render();

    return 0;
}
