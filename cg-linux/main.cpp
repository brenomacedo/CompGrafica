#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

int main (int, char**) {

    // TEXTURAS
    Image* texturaMar = new Image("./assets/mar.jpg");
    Image* texturaAreia = new Image("./assets/areia.jpg");
    Image* fundoCeu = new Image("./assets/ceu.jpg");
    Image* madeira = new Image("./assets/madeira.jpg");
    Image* tijolo = new Image("./assets/tijolo.jpg");
    Image* tijolo2 = new Image("./assets/tijolo.jpg");
    Image* tijolo3 = new Image("./assets/tijolo.jpg");
    Image* marmorebranco = new Image("./assets/marmorebranco.jpg");
    Image* marmorebranco2 = new Image("./assets/marmorebranco.jpg");
    Image* marmorepreto = new Image("./assets/marmorepreto.jpg");
    // ----------------------------------------

    // OBJETOS

    // Mar
    PlanWithTexture* mar = new PlanWithTexture(
        texturaMar,
        new Vector(0, -10, 0),
        new Vector(0, 1, 0),
        1
    );
    // ----------------------------------------

    // Ilha
    CylinderWithTextureOnTop* ilha = new CylinderWithTextureOnTop(
        texturaAreia,
        new Vector(0, -10, 0), new Vector(0, 1, 0), 10,
        550, new Vector(0.8, 0.3, 0.1), 5.0
    );
    // ----------------------------------------

    // Construcao do Restaurante
    MeshWithTexture* chaoDoRestaurante = Cube::createWithTexture(
        new Vector(0, 0, 0), 300, madeira, 1
    );
    chaoDoRestaurante->applyScale(1, 3.0/300.0, 1);
    chaoDoRestaurante->setWrapper(
        new Cylinder(new Vector(0, 0, 0), new Vector(0, 1, 0), 3, 213)
    );
    chaoDoRestaurante->applyTranslate(-200, 0, 0);

    MeshWithTexture* paredeDeTras = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(
        tijolo, 1
    );
    paredeDeTras->applyScale(4, 200, 300);
    paredeDeTras->setWrapper(
        new Cylinder(new Vector(0, 100, 150), new Vector(1, 0, 0), 4, 181)
    );
    paredeDeTras->applyTranslate(-350, 3, -150);

    MeshWithTexture* paredeEsquerda = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(
        tijolo2, 1
    );
    paredeEsquerda->applyScale(300, 200, 4);
    paredeEsquerda->setWrapper(
        new Cylinder(new Vector(150, 100, 0), new Vector(0, 0, 1), 4, 181)
    );
    paredeEsquerda->applyTranslate(-350, 3, -150);

    MeshWithTexture* paredeDireita = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(
        tijolo3, 1
    );
    paredeDireita->applyScale(300, 200, 4);
    paredeDireita->setWrapper(
        new Cylinder(new Vector(150, 100, 0), new Vector(0, 0, 1), 4, 181)
    );
    paredeDireita->applyTranslate(-350, 3, -150);
    paredeDireita->applyReflectXY();

    Cone* tetoDoRestaurante = new Cone(
        new Vector(-200, 203, 0), new Vector(0, 1, 0),
        150, 250, new Vector(0.388, 0.329, 0.329), 10
    );

    // INTERIOR DO RESTAURANTE

    MeshWithTexture* balcao = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(marmorebranco, 1.5);
    balcao->applyScale(50, 65, 200);
    balcao->setWrapper(new Cylinder(new Vector(25, 0, 100), new Vector(0, 1, 0), 65, 104));
    balcao->applyTranslate(-200, 3, -146);

    MeshWithTexture* balcaoTopo = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(marmorepreto, 1.5);
    balcaoTopo->applyScale(70, 5, 210);
    balcaoTopo->setWrapper(new Cylinder(new Vector(35, 0, 105), new Vector(0, 1, 0), 5, 111));
    balcaoTopo->applyTranslate(-210, 68, -146);

    Cylinder* bancoTronco = new Cylinder(
        new Vector(-100, 3, -100),
        new Vector(0, 1, 0), 30, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo = new Cylinder(
        new Vector(-100, 33, -100),
        new Vector(0, 1, 0), 5, 20, new Vector(0.9, 0.3, 0.3), 1
    );

    Cylinder* bancoTronco2 = new Cylinder(
        new Vector(-100, 3, -100),
        new Vector(0, 1, 0), 30, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo2 = new Cylinder(
        new Vector(-100, 33, -100),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.9, 0.3), 1
    );
    bancoTronco2->applyTranslate(0, 0, 60);
    bancoTopo2->applyTranslate(0, 0, 60);

    Cylinder* bancoTronco3 = new Cylinder(
        new Vector(-100, 3, -100),
        new Vector(0, 1, 0), 30, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo3 = new Cylinder(
        new Vector(-100, 33, -100),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    bancoTronco3->applyTranslate(0, 0, 120);
    bancoTopo3->applyTranslate(0, 0, 120);

    Mesh* fogao = Cube::createUnitaryWithBorderInCenaryCenter(
        new Vector(0.7, 0.7, 0.7), 1.8
    );
    fogao->applyScale(70, 15, 70);
    fogao->setWrapper(
        new Cylinder(new Vector(35, 0, 35), new Vector(0, 1, 0), 15, 50)
    );
    fogao->applyTranslate(-346, 53, -146);

    Cylinder* bocaFogao1 = new Cylinder(
        new Vector(12.5, 0, 12.5), new Vector(0, 1, 0),
        2, 12.5, new Vector(0.05, 0.05, 0.05), 1
    );
    bocaFogao1->applyTranslate(-341, 68, -141);
    Cylinder* bocaFogao2 = new Cylinder(
        new Vector(12.5, 0, 12.5), new Vector(0, 1, 0),
        2, 12.5, new Vector(0.05, 0.05, 0.05), 1
    );
    bocaFogao2->applyTranslate(-306, 68, -141);
    Cylinder* bocaFogao3 = new Cylinder(
        new Vector(12.5, 0, 12.5), new Vector(0, 1, 0),
        2, 12.5, new Vector(0.05, 0.05, 0.05), 1
    );
    bocaFogao3->applyTranslate(-341, 68, -106);
    Cylinder* bocaFogao4 = new Cylinder(
        new Vector(12.5, 0, 12.5), new Vector(0, 1, 0),
        2, 12.5, new Vector(0.05, 0.05, 0.05), 1
    );
    bocaFogao4->applyTranslate(-306, 68, -106);

    MeshWithTexture* bancada = Cube::createUnitaryWithBorderInCenaryCenterWithTexture(marmorebranco2, 1.5);
    bancada->applyScale(70, 15, 222);
    bancada->setWrapper(new Cylinder(new Vector(35, 0, 111), new Vector(0, 1, 0), 15, 117));
    bancada->applyTranslate(-346, 50, -76);

    Cylinder* corpoGarrafa = new Cylinder(
        new Vector(4, 0, 4), new Vector(0, 1, 0), 20, 8,
        new Vector(0.2, 0.2, 0.8), 0.3
    );
    corpoGarrafa->applyTranslate(-195, 73, 0);
    Sphere* topoGarrafa = new Sphere(
        8, new Vector(0.2, 0.2, 0.8), new Vector(4, 0, 4), 0.3
    );
    topoGarrafa->applyTranslate(-195, 93, 0);
    Cylinder* bocaGarrafa = new Cylinder(
        new Vector(4, 0, 4), new Vector(0, 1, 0), 6, 3,
        new Vector(0.2, 0.2, 0.8), 0.3
    );
    bocaGarrafa->applyTranslate(-195, 99, 0);

    Mesh* copo = Cup::createWithBorderInCenaryCenter(new Vector(0.8, 0.9, 0.9), 0.3);
    copo->setWrapper(
        new Cylinder(new Vector(5, 0, 5), new Vector(0, 1, 0), 10, 8)
    );
    copo->applyTranslate(-175, 73, -10);

    Cylinder* corpoLampada = new Cylinder(
        new Vector(-200, 200, 0), new Vector(0, -1, 0),
        3, 1.5, new Vector(0.2, 0.2, 0.2), 1
    );
    Sphere* cabecaLampada = new Sphere(
        3, new Vector(0.8, 0.8, 0.2),
        new Vector(-200, 195, 0), 0.1
    );

    // ----------------------------------------

    // ILUMINAÇÃO

    Light* sol = new DirectionalLight(
        new Vector(0.5, 0.5, 0.5),
        new Vector(1, -1, 1)
    );
    Light* lampada = new SpotLight(
        new Vector(0.9, 0.9, 0.9), new Vector(0, -1, 0),
        new Vector(-200, 191, 0), M_PI / 2
    );

    // CONFIGURAÇÃO DA CENA

    Sp<Scene> scene = new Scene (
        60.0, 60.0,
        400, 400,
        150,
        new Color (100, 100, 100, 255)
    );
    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );

    scene->addObject(mar);
    scene->addObject(ilha);
    
    scene->addObject(chaoDoRestaurante);
    scene->addObject(paredeDeTras);
    scene->addObject(paredeEsquerda);
    scene->addObject(paredeDireita);
    scene->addObject(tetoDoRestaurante);

    scene->addObject(balcao);
    scene->addObject(balcaoTopo);

    scene->addObject(bancoTronco);
    scene->addObject(bancoTopo);
    scene->addObject(bancoTronco2);
    scene->addObject(bancoTopo2);
    scene->addObject(bancoTronco3);
    scene->addObject(bancoTopo3);

    scene->addObject(fogao);
    scene->addObject(bocaFogao1);
    scene->addObject(bocaFogao2);
    scene->addObject(bocaFogao3);
    scene->addObject(bocaFogao4);

    scene->addObject(corpoGarrafa);
    scene->addObject(topoGarrafa);
    scene->addObject(bocaGarrafa);
    scene->addObject(copo);

    scene->addObject(bancada);

    scene->addObject(corpoLampada);
    scene->addObject(cabecaLampada);

    scene->addLightSource(sol);
    scene->addLightSource(lampada);

    scene->setBackgroundImage(fundoCeu);
    scene->lookAt(
        new Vector(500, 100, 0),
        new Vector(0, 100, 0),
        new Vector(500, 600, 0)
    );

    scene->render();

    return 0;
}
