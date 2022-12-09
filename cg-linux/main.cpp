#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

int main (int, char**) {

    Image* fundoMar = new Image("./assets/mar.jpg");
    Image* texturaAreia = new Image("./assets/areia.jpg");

    // OBJETOS

    PlanWithTexture* chao = new PlanWithTexture(
        texturaAreia,
        new Vector(0, 0, 0),
        new Vector(0, 1, 0),
        1
    );

    // ILUMINAÇÃO

    Light* sol = new DirectionalLight(
        new Vector(0.5, 0.5, 0.5),
        new Vector(1, -1, 1)
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
    scene->setBackgroundImage(fundoMar);

    scene->addObject(chao);
    scene->addLightSource(sol);

    scene->lookAt(
        new Vector(400, 400, 400),
        new Vector(0, 200, 0),
        new Vector(0, 500, 0)
    );

    scene->render();

    return 0;
}
