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

    Mesh* cube = Cube::create(new Vector(60, -150, -200), 30, new Vector(0,0.5,1), 5.0);
    cube->setWrapper(new Wrapper(26, new Vector(60, -135, -200)));

    Mesh* cube1 = Cube::create(new Vector(60, -150, -200), 30, new Vector(0,0.5,1), 5.0);
    cube1->applyReflectYZ();
    cube1->setWrapper(new Wrapper(26, new Vector(-60, -135, -200)));

    Mesh* cube2 = Cube::create(new Vector(60, -150, -240), 30, new Vector(0,0.5,1), 5.0);
    cube2->applyReflectYZ();
    cube2->setWrapper(new Wrapper(26, new Vector(-60, -135, -240)));
    
    Mesh* cube3 = Cube::create(new Vector(60, -150, -240), 30, new Vector(0,0.5,1), 5.0);
    cube3->setWrapper(new Wrapper(26, new Vector(60, -135, -240)));

    Mesh* cube4 = Cube::create(new Vector(60, -150, -280), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube5 = Cube::create(new Vector(60, -150, -280), 30, new Vector(0,0.5,1), 5.0);
    cube4->applyReflectYZ();
    cube4->setWrapper(new Wrapper(26, new Vector(-60, -135, -280)));
    cube5->setWrapper(new Wrapper(26, new Vector(60, -135, -280)));

    Mesh* cube6 = Cube::create(new Vector(60, -150, -320), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube7 = Cube::create(new Vector(60, -150, -320), 30, new Vector(0,0.5,1), 5.0);
    cube6->applyReflectYZ();
    cube6->setWrapper(new Wrapper(26, new Vector(-60, -135, -320)));
    cube7->setWrapper(new Wrapper(26, new Vector(60, -135, -320)));

    Mesh* cube8 = Cube::create(new Vector(60, -150, -360), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube9 = Cube::create(new Vector(60, -150, -360), 30, new Vector(0,0.5,1), 5.0);
    cube8->applyReflectYZ();
    cube8->setWrapper(new Wrapper(26, new Vector(-60, -135, -360)));
    cube9->setWrapper(new Wrapper(26, new Vector(60, -135, -360)));

    Mesh* cube10 = Cube::create(new Vector(60, -150, -400), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube11 = Cube::create(new Vector(60, -150, -400), 30, new Vector(0,0.5,1), 5.0);
    cube10->applyReflectYZ();
    cube10->setWrapper(new Wrapper(26, new Vector(-60, -135, -400)));
    cube11->setWrapper(new Wrapper(26, new Vector(60, -135, -400)));

    Mesh* cube12 = Cube::create(new Vector(60, -150, -440), 30, new Vector(0,0.5,1), 5.0);
    Mesh* cube13 = Cube::create(new Vector(60, -150, -440), 30, new Vector(0,0.5,1), 5.0);
    cube12->applyReflectYZ();
    cube12->setWrapper(new Wrapper(26, new Vector(-60, -135, -440)));
    cube13->setWrapper(new Wrapper(26, new Vector(60, -135, -440)));

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
    scene->addObject(cube2);
    scene->addObject(cube3);
    scene->addObject(cube4);
    scene->addObject(cube5);
    scene->addObject(cube6);
    scene->addObject(cube7);
    scene->addObject(cube8);
    scene->addObject(cube9);
    scene->addObject(cube10);
    scene->addObject(cube11);
    scene->addObject(cube12);
    scene->addObject(cube13);

    scene->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 0, -1),
        new Vector(0, 1, 0)
    );

    // scene->setProjectionType(ProjectionType::PARALLEL);

    scene->render();

    return 0;
}
