#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Image* floorTexture = new Image("./assets/madeira.jpg");

    PlanWithTexture* plan1 = new PlanWithTexture(
        floorTexture,
        new Vector(0, 0, 0),
        new Vector(0, 1, 0),
        5.0
    );

    Light* light = new PointLight(
        new Vector (0.7, 0.7, 0.7),
        new Vector(350, 350, -150)
    );

    Mesh* column1 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    column1->applyScale(50, 500, 30);

    Mesh* column2 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    column2->applyScale(50, 500, 30);
    column2->applyTranslate(650, 0, 0);

    Mesh* semiCeil1 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    semiCeil1->applyScale(300, 50, 30);
    semiCeil1->applyShearXY(atan(0.75));
    semiCeil1->applyTranslate(50, 450, 0);

    Mesh* semiCeil2 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    semiCeil2->applyScale(300, 50, 30);
    semiCeil2->applyShearXY(atan(-0.75));
    semiCeil2->applyTranslate(350, 675, 0);

    Mesh* column3 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    column3->applyScale(50, 500, 30);
    column3->applyTranslate(0, 0, -1030);

    Mesh* column4 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    column4->applyScale(50, 500, 30);
    column4->applyTranslate(650, 0, -1030);

    Mesh* semiCeil3 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    semiCeil3->applyScale(300, 50, 30);
    semiCeil3->applyShearXY(atan(0.75));
    semiCeil3->applyTranslate(50, 450, -1030);

    Mesh* semiCeil4 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    semiCeil4->applyScale(300, 50, 30);
    semiCeil4->applyShearXY(atan(-0.75));
    semiCeil4->applyTranslate(350, 675, -1030);

    Mesh* ceil1 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    ceil1->applyScale(450, 30, 1000);
    ceil1->applyRotateZ(atan(0.75));
    ceil1->applyTranslate(0, 450, -1030);

    Mesh* ceil2 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    ceil2->applyScale(450, 30, 1000);
    ceil2->applyRotateZ(atan(-0.75));
    ceil2->applyTranslate(320, 720, -1030);

    Mesh* wall1 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    wall1->applyScale(20, 500, 1000);
    wall1->applyTranslate(30, 0, -1000);

    Mesh* wall2 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    wall2->applyScale(20, 500, 1000);
    wall2->applyTranslate(660, 0, -1000);

    Mesh* wall3 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0.898, 0.898, 0), 5.0);
    wall3->applyScale(600, 500, 30);
    wall3->applyTranslate(50, 0, -1060);

    Mesh* tableFoot1 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0, 0.898, 0.898), 5.0);
    tableFoot1->applyScale(150, 95, -5);
    tableFoot1->applyTranslate(275, 0, -195);

    Mesh* tableFoot2 = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0, 0.898, 0.898), 5.0);
    tableFoot2->applyScale(150, 95, -5);
    tableFoot2->applyTranslate(275, 0, -445);

    Mesh* tableTop = Cube::createUnitaryWithBorderInCenaryCenter(new Vector(0, 0.898, 0.898), 5.0);
    tableTop->applyScale(150, 5, -250);
    tableTop->applyTranslate(275, 95, -200);

    Cylinder* treeBase = new Cylinder(
        new Vector(350, 100, -325), new Vector(0, 1, 0), 9, 30, new Vector(0.9,  0.6, 0.1), 5.0
    );

    Cylinder* treeTrunk = new Cylinder(
        new Vector(350, 109, -325), new Vector(0, 1, 0), 40, 6, new Vector(0.9,  0.6, 0.1), 5.0
    );

    Cone* treeCrown = new Cone(
        new Vector(350, 149, -325), new Vector(0, 1, 0), 150, 60, new Vector(0, 0.9, 0.2), 5.0
    );

    Sphere* treeStar = new Sphere(4.5, new Vector(1, 1, 0), new Vector(350, 299, -325), 5.0);

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
    scene->addObject(semiCeil1);
    scene->addObject(semiCeil2);
    scene->addObject(column1);
    scene->addObject(column2);
    scene->addObject(semiCeil3);
    scene->addObject(semiCeil4);
    scene->addObject(column3);
    scene->addObject(column4);
    scene->addObject(ceil1);
    scene->addObject(ceil2);
    scene->addObject(wall1);
    scene->addObject(wall2);
    scene->addObject(wall3);
    scene->addObject(tableFoot1);
    scene->addObject(tableFoot2);
    scene->addObject(tableTop);
    scene->addObject(treeBase);
    scene->addObject(treeTrunk);
    scene->addObject(treeCrown);
    scene->addObject(treeStar);

    scene->lookAt(
        new Vector(400, 400, 400),
        new Vector(400, 250, 0),
        new Vector(400, 400, 0)
    );

    scene->setProjectionType(ProjectionType::PARALLEL);

    scene->render();

    return 0;
}
