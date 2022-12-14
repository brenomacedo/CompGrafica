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
        600, new Vector(0.8, 0.3, 0.1), 5.0
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

    Link* linkBalcao = new Link("balcao"); // --
    linkBalcao->addObject(balcao);
    linkBalcao->addObject(balcaoTopo);

    Cylinder* bancoTronco = new Cylinder(
        new Vector(-100, 3, -100),
        new Vector(0, 1, 0), 30, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo = new Cylinder(
        new Vector(-100, 33, -100),
        new Vector(0, 1, 0), 5, 20, new Vector(0.9, 0.3, 0.3), 1
    );

    Link* bancoVermelho = new Link("banco vermelho"); // --
    bancoVermelho->addObject(bancoTronco);
    bancoVermelho->addObject(bancoTopo);

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

    Link* bancoVerde = new Link("banco verde"); // --
    bancoVerde->addObject(bancoTronco2);
    bancoVerde->addObject(bancoTopo2);

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

    Link* bancoAzul = new Link("banco azul"); // --
    bancoAzul->addObject(bancoTronco3);
    bancoAzul->addObject(bancoTopo3);

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

    Link* linkFogao = new Link("Fogao"); // --
    linkFogao->addObject(fogao);
    linkFogao->addObject(bocaFogao1);
    linkFogao->addObject(bocaFogao2);
    linkFogao->addObject(bocaFogao3);
    linkFogao->addObject(bocaFogao4);

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

    Link* linkGarrafa = new Link("Garrafa azul"); // --
    linkGarrafa->addObject(corpoGarrafa);
    linkGarrafa->addObject(topoGarrafa);
    linkGarrafa->addObject(bocaGarrafa);

    Mesh* copo = Cup::createWithBorderInCenaryCenter(new Vector(0.8, 0.2, 0.9), 0.3);
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

    // MESAS E CADEIRAS
    // == mesa 1
    Cylinder* baseMesa1 = new Cylinder(
        new Vector(300, 0, 0),
        new Vector(0, 1, 0),
        60, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* topoMesa1 = new Cylinder(
        new Vector(300, 60, 0),
        new Vector(0, 1, 0),
        5, 60, new Vector(0.8, 0.2, 0.2), 1
    );
    Cylinder* troncoGuardaSolMesa1 = new Cylinder(
        new Vector(235, 0, -65),
        new Vector(0, 1, 0),
        120, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cone* guardaSolMesa1 = new Cone(
        new Vector(235, 120, -65),
        new Vector(0, 1, 0),
        20, 80, new Vector(0.15, 0.95, 0.7), 1
    );
    Cylinder* bancoTronco1mesa1 = new Cylinder(
        new Vector(230, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo1mesa1 = new Cylinder(
        new Vector(230, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco2mesa1 = new Cylinder(
        new Vector(370, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo2mesa1 = new Cylinder(
        new Vector(370, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco3mesa1 = new Cylinder(
        new Vector(300, 0, 70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo3mesa1 = new Cylinder(
        new Vector(300, 25, 70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco4mesa1 = new Cylinder(
        new Vector(300, 0, -70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo4mesa1 = new Cylinder(
        new Vector(300, 25, -70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );

    Link* mesa1 = new Link("Mesa da esquerda");
    mesa1->addObject(baseMesa1);
    mesa1->addObject(topoMesa1);
    mesa1->addObject(troncoGuardaSolMesa1);
    mesa1->addObject(guardaSolMesa1);
    mesa1->addObject(bancoTronco1mesa1);
    mesa1->addObject(bancoTopo1mesa1);
    mesa1->addObject(bancoTronco2mesa1);
    mesa1->addObject(bancoTopo2mesa1);
    mesa1->addObject(bancoTronco3mesa1);
    mesa1->addObject(bancoTopo3mesa1);
    mesa1->addObject(bancoTronco4mesa1);
    mesa1->addObject(bancoTopo4mesa1);

    mesa1->applyTranslate(-70, 0, 250, nullptr);
    // ----------------------------------------

    // == mesa 2
    Cylinder* baseMesa2 = new Cylinder(
        new Vector(300, 0, 0),
        new Vector(0, 1, 0),
        60, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* topoMesa2 = new Cylinder(
        new Vector(300, 60, 0),
        new Vector(0, 1, 0),
        5, 60, new Vector(0.8, 0.2, 0.2), 1
    );
    Cylinder* troncoGuardaSolMesa2 = new Cylinder(
        new Vector(235, 0, -65),
        new Vector(0, 1, 0),
        120, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cone* guardaSolMesa2 = new Cone(
        new Vector(235, 120, -65),
        new Vector(0, 1, 0),
        20, 80, new Vector(0.95, 0.7, 0.15), 1
    );
    Cylinder* bancoTronco1mesa2 = new Cylinder(
        new Vector(230, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo1mesa2 = new Cylinder(
        new Vector(230, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco2mesa2 = new Cylinder(
        new Vector(370, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo2mesa2 = new Cylinder(
        new Vector(370, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco3mesa2 = new Cylinder(
        new Vector(300, 0, 70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo3mesa2 = new Cylinder(
        new Vector(300, 25, 70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco4mesa2 = new Cylinder(
        new Vector(300, 0, -70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo4mesa2 = new Cylinder(
        new Vector(300, 25, -70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );

    Link* mesa2 = new Link("Mesa do meio");
    mesa2->addObject(baseMesa2);
    mesa2->addObject(topoMesa2);
    mesa2->addObject(troncoGuardaSolMesa2);
    mesa2->addObject(guardaSolMesa2);
    mesa2->addObject(bancoTronco1mesa2);
    mesa2->addObject(bancoTopo1mesa2);
    mesa2->addObject(bancoTronco2mesa2);
    mesa2->addObject(bancoTopo2mesa2);
    mesa2->addObject(bancoTronco3mesa2);
    mesa2->addObject(bancoTopo3mesa2);
    mesa2->addObject(bancoTronco4mesa2);
    mesa2->addObject(bancoTopo4mesa2);

    // ----------------------------------------
    // == mesa 3
    Cylinder* baseMesa3 = new Cylinder(
        new Vector(300, 0, 0),
        new Vector(0, 1, 0),
        60, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* topoMesa3 = new Cylinder(
        new Vector(300, 60, 0),
        new Vector(0, 1, 0),
        5, 60, new Vector(0.8, 0.2, 0.2), 1
    );
    Cylinder* troncoGuardaSolMesa3 = new Cylinder(
        new Vector(235, 0, -65),
        new Vector(0, 1, 0),
        120, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cone* guardaSolMesa3 = new Cone(
        new Vector(235, 120, -65),
        new Vector(0, 1, 0),
        20, 80, new Vector(0.9, 0.9, 0.9), 1
    );
    Cylinder* bancoTronco1mesa3 = new Cylinder(
        new Vector(230, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo1mesa3 = new Cylinder(
        new Vector(230, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco2mesa3 = new Cylinder(
        new Vector(370, 0, 0),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo2mesa3 = new Cylinder(
        new Vector(370, 25, 0),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco3mesa3 = new Cylinder(
        new Vector(300, 0, 70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo3mesa3 = new Cylinder(
        new Vector(300, 25, 70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );
    Cylinder* bancoTronco4mesa3 = new Cylinder(
        new Vector(300, 0, -70),
        new Vector(0, 1, 0), 25, 5, new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bancoTopo4mesa3 = new Cylinder(
        new Vector(300, 25, -70),
        new Vector(0, 1, 0), 5, 20, new Vector(0.3, 0.3, 0.9), 1
    );

    Link* mesa3 = new Link("Mesa da direita");
    mesa3->addObject(baseMesa3);
    mesa3->addObject(topoMesa3);
    mesa3->addObject(troncoGuardaSolMesa3);
    mesa3->addObject(guardaSolMesa3);
    mesa3->addObject(bancoTronco1mesa3);
    mesa3->addObject(bancoTopo1mesa3);
    mesa3->addObject(bancoTronco2mesa3);
    mesa3->addObject(bancoTopo2mesa3);
    mesa3->addObject(bancoTronco3mesa3);
    mesa3->addObject(bancoTopo3mesa3);
    mesa3->addObject(bancoTronco4mesa3);
    mesa3->addObject(bancoTopo4mesa3);

    mesa3->applyTranslate(-70, 0, -250, nullptr);

    // POSTES
    Cylinder* troncoPoste1 = new Cylinder(
        new Vector(375, 0, 200),
        new Vector(0, 1, 0), 150, 5,
        new Vector(0.3, 0.3, 0.3), 1
    );
    Cone* conePoste1 = new Cone(
        new Vector(375, 150, 200),
        new Vector(0, 1, 0), 15, 8,
        new Vector(0.96, 0.72, 0.25), 1
    );

    Link* linkPoste1 = new Link("Poste da esquerda");
    linkPoste1->addObject(troncoPoste1);
    linkPoste1->addObject(conePoste1);

    Cylinder* troncoPoste2 = new Cylinder(
        new Vector(375, 0, 200),
        new Vector(0, 1, 0), 150, 5,
        new Vector(0.3, 0.3, 0.3), 1
    );
    Cone* conePoste2 = new Cone(
        new Vector(375, 150, 200),
        new Vector(0, 1, 0), 15, 8,
        new Vector(0.96, 0.72, 0.25), 1
    );
    Link* linkPoste2 = new Link("Poste da direita");
    linkPoste2->addObject(troncoPoste2);
    linkPoste2->addObject(conePoste2);
    linkPoste2->applyReflectXY(nullptr);

    // ARVORES
    Cylinder* troncoArvoreEsquerda = new Cylinder(
        new Vector(-100, 0, 450),
        new Vector(0, 1, 0),
        80, 40, new Vector(0.2, 0.2, 0.2), 1
    );
    Cone* copa1ArvoreEsquerda = new Cone(
        new Vector(-100, 80, 450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.8, 0.3), 1
    );
    Cone* copa2ArvoreEsquerda = new Cone(
        new Vector(-100, 140, 450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.9, 0.5), 1
    );
    Cone* copa3ArvoreEsquerda = new Cone(
        new Vector(-100, 200, 450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.8, 0.3), 1
    );

    Link* arvoreEsquerda = new Link("Arvore esquerda");
    arvoreEsquerda->addObject(troncoArvoreEsquerda);
    arvoreEsquerda->addObject(copa1ArvoreEsquerda);
    arvoreEsquerda->addObject(copa2ArvoreEsquerda);
    arvoreEsquerda->addObject(copa3ArvoreEsquerda);
    
    Cylinder* troncoArvoreDireita = new Cylinder(
        new Vector(-100, 0, -450),
        new Vector(0, 1, 0),
        80, 40, new Vector(0.2, 0.2, 0.2), 1
    );
    Cone* copa1ArvoreDireita = new Cone(
        new Vector(-100, 80, -450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.8, 0.3), 1
    );
    Cone* copa2ArvoreDireita = new Cone(
        new Vector(-100, 140, -450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.9, 0.5), 1
    );
    Cone* copa3ArvoreDireita = new Cone(
        new Vector(-100, 200, -450),
        new Vector(0, 1, 0),
        160, 100, new Vector(0.2, 0.8, 0.3), 1
    );

    Link* arvoreDireita = new Link("Arvore direita");
    arvoreDireita->addObject(troncoArvoreDireita);
    arvoreDireita->addObject(copa1ArvoreDireita);
    arvoreDireita->addObject(copa2ArvoreDireita);
    arvoreDireita->addObject(copa3ArvoreDireita);

    // ----------------------------------------

    // SANDMAN
    Sphere* corpoSandman = new Sphere(
        35, new Vector(0.941, 0.905, 0.780),
        new Vector(200, 35, 450), 1
    );
    Sphere* barrigaSandman = new Sphere(
        30, new Vector(0.941, 0.905, 0.780),
        new Vector(200, 80, 450), 1
    );
    Sphere* cabecaSandman = new Sphere(
        25, new Vector(0.941, 0.905, 0.780),
        new Vector(200, 120, 450), 1
    );
    Cone* narizSandman = new Cone(
        new Vector(220, 120, 450),
        new Vector(1, 0, 0),
        15, 5, new Vector(0.8, 0.5, 0.2)
    );
    Cylinder* oculosDireitoSandman = new Cylinder(
        new Vector(220, 130, 440),
        new Vector(1, 0, 0),
        5, 8, new Vector(0.1, 0.1, 0.1)
    );
    Cylinder* oculosEsquerdoSandman = new Cylinder(
        new Vector(220, 130, 460),
        new Vector(1, 0, 0),
        5, 8, new Vector(0.1, 0.1, 0.1)
    );
    Cylinder* oculosLigacaoSandman = new Cylinder(
        new Vector(222, 130, 435),
        new Vector(0, 0, 1),
        30, 2, new Vector(0.1, 0.1, 0.1)
    );
    Cylinder* baseGorroSandman = new Cylinder(
        new Vector(200, 140, 450),
        new Vector(0, 1, 0),
        8, 20, new Vector(1, 1, 1), 1
    );
    Cone* gorroSandman = new Cone(
        new Vector(200, 148, 450),
        new Vector(0, 1, 0),
        35, 19, new Vector(1, 0, 0), 1
    );
    Sphere* pontaGorroSandman = new Sphere(
        5, new Vector(1, 1, 1),
        new Vector(200, 178, 450), 1
    );
    Cylinder* bracoEsquerdoSandman = new Cylinder(
        new Vector(200, 80, 475),
        new Vector(0, 1, 1), 40, 5,
        new Vector(0.3, 0.3, 0.3), 1
    );
    Cylinder* bracoDireitoSandman = new Cylinder(
        new Vector(200, 80, 425),
        new Vector(0, 1, -1), 40, 5,
        new Vector(0.3, 0.3, 0.3), 1
    );

    Link* linkSandman = new Link("Sandman");
    linkSandman->addObject(corpoSandman);
    linkSandman->addObject(barrigaSandman);
    linkSandman->addObject(cabecaSandman);
    linkSandman->addObject(narizSandman);
    linkSandman->addObject(oculosDireitoSandman);
    linkSandman->addObject(oculosEsquerdoSandman);
    linkSandman->addObject(oculosLigacaoSandman);
    linkSandman->addObject(baseGorroSandman);
    linkSandman->addObject(gorroSandman);
    linkSandman->addObject(pontaGorroSandman);
    linkSandman->addObject(bracoEsquerdoSandman);
    linkSandman->addObject(bracoDireitoSandman);

    // ILUMINAÇÃO

    Light* luzPoste1 = new PointLight(
        new Vector(0.3, 0.3, 0.3),
        new Vector(375, 166, 200)
    );
    Light* luzPoste2 = new PointLight(
        new Vector(0.3, 0.3, 0.3),
        new Vector(375, 166, -200)
    );
    Light* sol = new DirectionalLight(
        new Vector(0.3, 0.3, 0.3),
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
        50,
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

    scene->addObject(baseMesa2);
    scene->addObject(topoMesa2);
    scene->addObject(bancoTronco1mesa2);
    scene->addObject(bancoTopo1mesa2);
    scene->addObject(bancoTronco2mesa2);
    scene->addObject(bancoTopo2mesa2);
    scene->addObject(bancoTronco3mesa2);
    scene->addObject(bancoTopo3mesa2);
    scene->addObject(bancoTronco4mesa2);
    scene->addObject(bancoTopo4mesa2);
    scene->addObject(troncoGuardaSolMesa2);
    scene->addObject(guardaSolMesa2);

    scene->addObject(baseMesa1);
    scene->addObject(topoMesa1);
    scene->addObject(bancoTronco1mesa1);
    scene->addObject(bancoTopo1mesa1);
    scene->addObject(bancoTronco2mesa1);
    scene->addObject(bancoTopo2mesa1);
    scene->addObject(bancoTronco3mesa1);
    scene->addObject(bancoTopo3mesa1);
    scene->addObject(bancoTronco4mesa1);
    scene->addObject(bancoTopo4mesa1);
    scene->addObject(troncoGuardaSolMesa1);
    scene->addObject(guardaSolMesa1);

    scene->addObject(baseMesa3);
    scene->addObject(topoMesa3);
    scene->addObject(bancoTronco1mesa3);
    scene->addObject(bancoTopo1mesa3);
    scene->addObject(bancoTronco2mesa3);
    scene->addObject(bancoTopo2mesa3);
    scene->addObject(bancoTronco3mesa3);
    scene->addObject(bancoTopo3mesa3);
    scene->addObject(bancoTronco4mesa3);
    scene->addObject(bancoTopo4mesa3);
    scene->addObject(troncoGuardaSolMesa3);
    scene->addObject(guardaSolMesa3);

    scene->addObject(troncoPoste1);
    scene->addObject(conePoste1);
    
    scene->addObject(troncoPoste2);
    scene->addObject(conePoste2);

    scene->addObject(troncoArvoreEsquerda);
    scene->addObject(copa1ArvoreEsquerda);
    scene->addObject(copa2ArvoreEsquerda);
    scene->addObject(copa3ArvoreEsquerda);

    scene->addObject(troncoArvoreDireita);
    scene->addObject(copa1ArvoreDireita);
    scene->addObject(copa2ArvoreDireita);
    scene->addObject(copa3ArvoreDireita);

    scene->addObject(corpoSandman);
    scene->addObject(barrigaSandman);
    scene->addObject(cabecaSandman);
    scene->addObject(narizSandman);
    scene->addObject(oculosDireitoSandman);
    scene->addObject(oculosEsquerdoSandman);
    scene->addObject(oculosLigacaoSandman);
    scene->addObject(baseGorroSandman);
    scene->addObject(gorroSandman);
    scene->addObject(pontaGorroSandman);
    scene->addObject(bracoEsquerdoSandman);
    scene->addObject(bracoDireitoSandman);

    scene->addLightSource(sol);
    scene->addLightSource(lampada);
    scene->addLightSource(luzPoste1);
    scene->addLightSource(luzPoste2);

    scene->addLink(linkBalcao);
    scene->addLink(linkFogao);
    scene->addLink(linkGarrafa);
    scene->addLink(linkPoste1);
    scene->addLink(linkPoste2);
    scene->addLink(mesa1);
    scene->addLink(mesa2);
    scene->addLink(mesa3);
    scene->addLink(bancoAzul);
    scene->addLink(bancoVerde);
    scene->addLink(bancoVermelho);
    scene->addLink(arvoreDireita);
    scene->addLink(arvoreEsquerda);
    scene->addLink(linkSandman);

    scene->setBackgroundImage(fundoCeu);
    scene->lookAt(
        new Vector(1500, 1500, 1500),
        new Vector(0, 0, 0),
        new Vector(1500, 1600, 1500)
    );

    scene->render();

    return 0;
}
