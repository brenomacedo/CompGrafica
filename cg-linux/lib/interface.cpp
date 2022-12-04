#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/pixels.h"
#include "../include/interface.h"
#include "../include/CG.h"
#include "../include/utils.h"
#include "../include/cone.h"
#include "../include/cylinder.h"
#include "../include/plan.h"
#include "../include/mesh.h"
#include "../include/sphere.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

string Interface::lightStatus(Light* light) {
  return (light->isActive() ? "Ligada" : "Desligada");
}

void Interface::mouseEvent(SDL_MouseButtonEvent& event) {
  if (event.button == SDL_BUTTON_LEFT) {
    int c;
    int l;
    SDL_GetMouseState(&c, &l);

    const double nLin = this->scene->getCanvasHeight();
    const double nCol = this->scene->getCanvasWidth();

    const double hJanela = this->scene->getWindowHeight();
    const double wJanela = this->scene->getWindowWidth();

    const double dx = wJanela / nCol;
    const double dy = hJanela / nLin;

    int numberOfObjects = this->scene->getObjects().size();

    const double z = -this->scene->getWindowDistance();

    const double y = hJanela / 2.0 - dy / 2.0 - l * dy;
    const double x = -wJanela / 2.0 + dx / 2.0 + c * dx;

    bool isProjectionPerspective = this->scene->getProjectionType() == ProjectionType::PERSPECTIVE;
    Vector* P0 = new Vector(
        isProjectionPerspective ? Vector(0, 0, 0) : Vector(x, y, 0)
    );
    Vector* direction = new Vector(
        isProjectionPerspective ? Vector(x, y, z) : Vector(0, 0, -1)
    );
    Sp<Line> line = new Line(P0, direction);

    int nearestObjectIndex = 0;
    Sp<IntersectionResult> nearestResult = new IntersectionResult(false, nullptr, 0, ObjectRegion::UNKNOWN);

    for(int i = 0; i < numberOfObjects; i++) {

        Sp<IntersectionResult> result = this->scene->getObjects()[i]->getIntersectionResult(line.pointer);
        
        if(result->getHasIntersection() &&
    (!nearestResult->getHasIntersection() || result->getDistanceFromP0() < nearestResult->getDistanceFromP0())) {
            delete nearestResult.pointer;
            nearestResult.pointer = result.pointer;
            result.pointer = nullptr;

            nearestObjectIndex = i;
        }

    }

    Object* nearestObject = this->scene->getObjects()[nearestObjectIndex];

    ObjectType nearestObjectType = nearestObject->getObjectType();

    switch(nearestObjectType) {
      case ObjectType::CONE:
        Cone* selectedCone;
        selectedCone = (Cone*) nearestObject;
        cout << "====== Objeto selecionado: CONE ======" << endl;
        cout << "Topo: " << *selectedCone->initialTop << endl;
        cout << "Base: " << *selectedCone->initialBaseCenter << endl;
        cout << "1 - Mudar reflectividade (Kd, Ke, Ka)" << endl;
        cout << "2 - Mudar shininess" << endl;
        cout << "3 - Transladar" << endl;
        cout << "4 - Rotacionar no eixo X" << endl;
        cout << "5 - Rotacionar no eixo Y" << endl;
        cout << "6 - Rotacionar no eixo Z" << endl;
        cout << "7 - Refletir no plano XY" << endl;
        cout << "8 - Refletir no plano XZ" << endl;
        cout << "9 - Refletir no plano YZ" << endl;
        cout << "Digite a opcao desejada: ";

        int opcaoCone;
        cin >> opcaoCone;

        switch(opcaoCone) {
          case 1:
            double coneKd_R, coneKd_G, coneKd_B;
            double coneKe_R, coneKe_G, coneKe_B;
            double coneKa_R, coneKa_G, coneKa_B;
            cout << "Digite, separado por espacos, os valores do Kd do cone (0 a 1): ";
            cin >> coneKd_R >> coneKd_G >> coneKd_B;
            cout << "Digite, separado por espacos, os valores do Ke do cone (0 a 1): ";
            cin >> coneKe_R >> coneKe_G >> coneKe_B;
            cout << "Digite, separado por espacos, os valores do Ka do cone (0 a 1): ";
            cin >> coneKa_R >> coneKa_G >> coneKa_B;

            *selectedCone->getKd() = Vector(coneKd_R, coneKd_G, coneKd_B);
            *selectedCone->getKe() = Vector(coneKe_R, coneKe_G, coneKe_B);
            *selectedCone->getKa() = Vector(coneKa_R, coneKa_G, coneKa_B);
            break;
          case 2:
            double newShineness;
            cout << "Digite o novo valor do shininess: ";
            cin >> newShineness;
            selectedCone->setShininess(newShineness);
            break;
          case 3:
            double cone_Tx, cone_Ty, cone_Tz;
            cout << "Digite, separado por espacos, a translacao do cone Tx, Ty e Tz: ";
            cin >> cone_Tx >> cone_Ty >> cone_Tz;
            selectedCone->applyTranslate(cone_Tx, cone_Ty, cone_Tz);
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 4:
            double cone_Rx;
            cout << "Digite o angulo de rotacao em torno do eixo X: ";
            cin >> cone_Rx;
            selectedCone->applyRotateX(cone_Rx);
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 5:
            double cone_Ry;
            cout << "Digite o angulo de rotacao em torno do eixo Y: ";
            cin >> cone_Ry;
            selectedCone->applyRotateY(cone_Ry);
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 6:
            double cone_Rz;
            cout << "Digite o angulo de rotacao em torno do eixo Z: ";
            cin >> cone_Rz;
            selectedCone->applyRotateZ(cone_Rz);
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 7:
            selectedCone->applyReflectXY();
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 8:
            selectedCone->applyReflectXZ();
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 9:
            selectedCone->applyReflectYZ();
            selectedCone->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
        }
        break;

      case ObjectType::MESH:
        Mesh* selectedMesh;
        selectedMesh = (Mesh*) nearestObject;
        cout << "====== Objeto selecionado: MALHA ======" << endl;
        cout << "1 - Mudar reflectividade (Kd, Ke, Ka)" << endl;
        cout << "2 - Mudar shininess" << endl;
        cout << "3 - Transladar" << endl;
        cout << "4 - Rotacionar no eixo X" << endl;
        cout << "5 - Rotacionar no eixo Y" << endl;
        cout << "6 - Rotacionar no eixo Z" << endl;
        cout << "7 - Refletir no plano XY" << endl;
        cout << "8 - Refletir no plano XZ" << endl;
        cout << "9 - Refletir no plano YZ" << endl;
        cout << "10 - Escalar" << endl;
        cout << "Digite a opcao desejada: ";

        int opcaoMalha;
        cin >> opcaoMalha;

        switch(opcaoMalha) {
          case 1:
            double malhaKd_R, malhaKd_G, malhaKd_B;
            double malhaKe_R, malhaKe_G, malhaKe_B;
            double malhaKa_R, malhaKa_G, malhaKa_B;
            cout << "Digite, separado por espacos, os valores do Kd da malha (0 a 1): ";
            cin >> malhaKd_R >> malhaKd_G >> malhaKd_B;
            cout << "Digite, separado por espacos, os valores do Ke da malha (0 a 1): ";
            cin >> malhaKe_R >> malhaKe_G >> malhaKe_B;
            cout << "Digite, separado por espacos, os valores do Ka da malha (0 a 1): ";
            cin >> malhaKa_R >> malhaKa_G >> malhaKa_B;

            *selectedMesh->getKd() = Vector(malhaKd_R, malhaKd_G, malhaKd_B);
            *selectedMesh->getKe() = Vector(malhaKe_R, malhaKe_G, malhaKe_B);
            *selectedMesh->getKa() = Vector(malhaKa_R, malhaKa_G, malhaKa_B);
            break;
          case 2:
            double newShineness;
            cout << "Digite o novo valor do shininess: ";
            cin >> newShineness;
            selectedMesh->setShininess(newShineness);
            break;
          case 3:
            double malha_Tx, malha_Ty, malha_Tz;
            cout << "Digite, separado por espacos, a translacao da malha Tx, Ty e Tz: ";
            cin >> malha_Tx >> malha_Ty >> malha_Tz;
            selectedMesh->applyTranslate(malha_Tx, malha_Ty, malha_Tz);
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 4:
            double malha_Rx;
            cout << "Digite o angulo de rotacao em torno do eixo X: ";
            cin >> malha_Rx;
            selectedMesh->applyRotateX(malha_Rx);
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 5:
            double malha_Ry;
            cout << "Digite o angulo de rotacao em torno do eixo Y: ";
            cin >> malha_Ry;
            selectedMesh->applyRotateY(malha_Ry);
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 6:
            double malha_Rz;
            cout << "Digite o angulo de rotacao em torno do eixo Z: ";
            cin >> malha_Rz;
            selectedMesh->applyRotateZ(malha_Rz);
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 7:
            selectedMesh->applyReflectXY();
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 8:
            selectedMesh->applyReflectXZ();
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 9:
            selectedMesh->applyReflectYZ();
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 10:
            double malha_Sx, malha_Sy, malha_Sz;
            cout << "Digite, separado por espacos, as escalas da malha Sx, Sy e Sz: ";
            cin >> malha_Sx >> malha_Sy >> malha_Sz;
            selectedMesh->applyScale(malha_Sx, malha_Sy, malha_Sz);
            selectedMesh->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
        }
        break;
      case ObjectType::PLAN:
        Plan* selectedPlan;
        selectedPlan = (Plan*) nearestObject;
        cout << "====== Objeto selecionado: PLANO ======" << endl;
        cout << "Ponto inicial: " << *selectedPlan->initialInitialPoint << endl;
        cout << "Normal: " << *selectedPlan->initialNormal << endl;
        cout << "1 - Mudar reflectividade (Kd, Ke, Ka)" << endl;
        cout << "2 - Mudar shininess" << endl;
        cout << "3 - Transladar" << endl;
        cout << "4 - Rotacionar no eixo X" << endl;
        cout << "5 - Rotacionar no eixo Y" << endl;
        cout << "6 - Rotacionar no eixo Z" << endl;
        cout << "7 - Refletir no plano XY" << endl;
        cout << "8 - Refletir no plano XZ" << endl;
        cout << "9 - Refletir no plano YZ" << endl;
        cout << "Digite a opcao desejada: ";

        int opcaoPlano;
        cin >> opcaoPlano;

        switch(opcaoPlano) {
          case 1:
            double planoKd_R, planoKd_G, planoKd_B;
            double planoKe_R, planoKe_G, planoKe_B;
            double planoKa_R, planoKa_G, planoKa_B;
            cout << "Digite, separado por espacos, os valores do Kd do plano (0 a 1): ";
            cin >> planoKd_R >> planoKd_G >> planoKd_B;
            cout << "Digite, separado por espacos, os valores do Ke do plano (0 a 1): ";
            cin >> planoKe_R >> planoKe_G >> planoKe_B;
            cout << "Digite, separado por espacos, os valores do Ka do plano (0 a 1): ";
            cin >> planoKa_R >> planoKa_G >> planoKa_B;

            *selectedPlan->getKd() = Vector(planoKd_R, planoKd_G, planoKd_B);
            *selectedPlan->getKe() = Vector(planoKe_R, planoKe_G, planoKe_B);
            *selectedPlan->getKa() = Vector(planoKa_R, planoKa_G, planoKa_B);
            break;
          case 2:
            double newShineness;
            cout << "Digite o novo valor do shininess: ";
            cin >> newShineness;
            selectedPlan->setShininess(newShineness);
            break;
          case 3:
            double plano_Tx, plano_Ty, plano_Tz;
            cout << "Digite, separado por espacos, a translacao do plano Tx, Ty e Tz: ";
            cin >> plano_Tx >> plano_Ty >> plano_Tz;
            selectedPlan->applyTranslate(plano_Tx, plano_Ty, plano_Tz);
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 4:
            double plano_Rx;
            cout << "Digite o angulo de rotacao em torno do eixo X: ";
            cin >> plano_Rx;
            selectedPlan->applyRotateX(plano_Rx);
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 5:
            double plano_Ry;
            cout << "Digite o angulo de rotacao em torno do eixo Y: ";
            cin >> plano_Ry;
            selectedPlan->applyRotateY(plano_Ry);
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 6:
            double plano_Rz;
            cout << "Digite o angulo de rotacao em torno do eixo Z: ";
            cin >> plano_Rz;
            selectedPlan->applyRotateZ(plano_Rz);
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 7:
            selectedPlan->applyReflectXY();
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 8:
            selectedPlan->applyReflectXZ();
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 9:
            selectedPlan->applyReflectYZ();
            selectedPlan->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
        }
        break;
      case ObjectType::CYLINDER:
        Cylinder* selectedCylinder;
        selectedCylinder = (Cylinder*) nearestObject;
        cout << "====== Objeto selecionado: CILINDRO ======" << endl;
        cout << "Topo: " << *selectedCylinder->initialTopCenter << endl;
        cout << "Base: " << *selectedCylinder->initialBaseCenter << endl;
        cout << "1 - Mudar reflectividade (Kd, Ke, Ka)" << endl;
        cout << "2 - Mudar shininess" << endl;
        cout << "3 - Transladar" << endl;
        cout << "4 - Rotacionar no eixo X" << endl;
        cout << "5 - Rotacionar no eixo Y" << endl;
        cout << "6 - Rotacionar no eixo Z" << endl;
        cout << "7 - Refletir no plano XY" << endl;
        cout << "8 - Refletir no plano XZ" << endl;
        cout << "9 - Refletir no plano YZ" << endl;
        cout << "Digite a opcao desejada: ";

        int opcaoCilindro;
        cin >> opcaoCilindro;

        switch(opcaoCilindro) {
          case 1:
            double cilindroKd_R, cilindroKd_G, cilindroKd_B;
            double cilindroKe_R, cilindroKe_G, cilindroKe_B;
            double cilindroKa_R, cilindroKa_G, cilindroKa_B;
            cout << "Digite, separado por espacos, os valores do Kd do cilindro (0 a 1): ";
            cin >> cilindroKd_R >> cilindroKd_G >> cilindroKd_B;
            cout << "Digite, separado por espacos, os valores do Ke do cilindro (0 a 1): ";
            cin >> cilindroKe_R >> cilindroKe_G >> cilindroKe_B;
            cout << "Digite, separado por espacos, os valores do Ka do cilindro (0 a 1): ";
            cin >> cilindroKa_R >> cilindroKa_G >> cilindroKa_B;

            *selectedCylinder->getKd() = Vector(cilindroKd_R, cilindroKd_G, cilindroKd_B);
            *selectedCylinder->getKe() = Vector(cilindroKe_R, cilindroKe_G, cilindroKe_B);
            *selectedCylinder->getKa() = Vector(cilindroKa_R, cilindroKa_G, cilindroKa_B);
            break;
          case 2:
            double newShineness;
            cout << "Digite o novo valor do shininess: ";
            cin >> newShineness;
            selectedCylinder->setShininess(newShineness);
            break;
          case 3:
            double cilindro_Tx, cilindro_Ty, cilindro_Tz;
            cout << "Digite, separado por espacos, a translacao do cilindro Tx, Ty e Tz: ";
            cin >> cilindro_Tx >> cilindro_Ty >> cilindro_Tz;
            selectedCylinder->applyTranslate(cilindro_Tx, cilindro_Ty, cilindro_Tz);
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 4:
            double cilindro_Rx;
            cout << "Digite o angulo de rotacao em torno do eixo X: ";
            cin >> cilindro_Rx;
            selectedCylinder->applyRotateX(cilindro_Rx);
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 5:
            double cilindro_Ry;
            cout << "Digite o angulo de rotacao em torno do eixo Y: ";
            cin >> cilindro_Ry;
            selectedCylinder->applyRotateY(cilindro_Ry);
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 6:
            double cilindro_Rz;
            cout << "Digite o angulo de rotacao em torno do eixo Z: ";
            cin >> cilindro_Rz;
            selectedCylinder->applyRotateZ(cilindro_Rz);
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 7:
            selectedCylinder->applyReflectXY();
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 8:
            selectedCylinder->applyReflectXZ();
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 9:
            selectedCylinder->applyReflectYZ();
            selectedCylinder->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
        }
        break;
      case ObjectType::SPHERE:
        Sphere* selectedSphere;
        selectedSphere = (Sphere*) nearestObject;
        cout << "====== Objeto selecionado: ESFERA ======" << endl;
        cout << "Centro: " << *selectedSphere->initialCenter << endl;
        cout << "Raio: " << selectedSphere->getRadius() << endl;
        cout << "1 - Mudar reflectividade (Kd, Ke, Ka)" << endl;
        cout << "2 - Mudar shininess" << endl;
        cout << "3 - Transladar" << endl;
        cout << "4 - Rotacionar no eixo X" << endl;
        cout << "5 - Rotacionar no eixo Y" << endl;
        cout << "6 - Rotacionar no eixo Z" << endl;
        cout << "7 - Refletir no plano XY" << endl;
        cout << "8 - Refletir no plano XZ" << endl;
        cout << "9 - Refletir no plano YZ" << endl;
        cout << "Digite a opcao desejada: ";

        int opcaoEsfera;
        cin >> opcaoEsfera;

        switch(opcaoEsfera) {
          case 1:
            double esferaKd_R, esferaKd_G, esferaKd_B;
            double esferaKe_R, esferaKe_G, esferaKe_B;
            double esferaKa_R, esferaKa_G, esferaKa_B;
            cout << "Digite, separado por espacos, os valores do Kd da esfera (0 a 1): ";
            cin >> esferaKd_R >> esferaKd_G >> esferaKd_B;
            cout << "Digite, separado por espacos, os valores do Ke da esfera (0 a 1): ";
            cin >> esferaKe_R >> esferaKe_G >> esferaKe_B;
            cout << "Digite, separado por espacos, os valores do Ka da esfera (0 a 1): ";
            cin >> esferaKa_R >> esferaKa_G >> esferaKa_B;

            *selectedSphere->getKd() = Vector(esferaKd_R, esferaKd_G, esferaKd_B);
            *selectedSphere->getKe() = Vector(esferaKe_R, esferaKe_G, esferaKe_B);
            *selectedSphere->getKa() = Vector(esferaKa_R, esferaKa_G, esferaKa_B);
            break;
          case 2:
            double newShineness;
            cout << "Digite o novo valor do shininess: ";
            cin >> newShineness;
            selectedSphere->setShininess(newShineness);
            break;
          case 3:
            double esfera_Tx, esfera_Ty, esfera_Tz;
            cout << "Digite, separado por espacos, a translacao da esfera Tx, Ty e Tz: ";
            cin >> esfera_Tx >> esfera_Ty >> esfera_Tz;
            selectedSphere->applyTranslate(esfera_Tx, esfera_Ty, esfera_Tz);
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 4:
            double esfera_Rx;
            cout << "Digite o angulo de rotacao em torno do eixo X: ";
            cin >> esfera_Rx;
            selectedSphere->applyRotateX(esfera_Rx);
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 5:
            double esfera_Ry;
            cout << "Digite o angulo de rotacao em torno do eixo Y: ";
            cin >> esfera_Ry;
            selectedSphere->applyRotateY(esfera_Ry);
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 6:
            double esfera_Rz;
            cout << "Digite o angulo de rotacao em torno do eixo Z: ";
            cin >> esfera_Rz;
            selectedSphere->applyRotateZ(esfera_Rz);
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 7:
            selectedSphere->applyReflectXY();
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 8:
            selectedSphere->applyReflectXZ();
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
          case 9:
            selectedSphere->applyReflectYZ();
            selectedSphere->applyWorldToCanvasConversion(this->scene->eyeLookAt);
            break;
        }
        break;
    }

  }
}

void Interface::listenEvents() {
  bool isRunning = true;

  while (isRunning) {
    int opt = this->showMenu();

    if (opt == 0) {
      isRunning = false;
    } else {
      this->actionChosen(opt);
      this->scene->raycast();
      this->scene->update();
    }
  }

  SDL_DestroyWindow (this->scene->window);
  SDL_Quit ();
}

int Interface::showMenu() {
  int opcao;

  cout << "0 - Sair" << endl;
  cout << "1 - Modificar parametros da camera" << endl;
  cout << "2 - Modificar fontes luminosas" << endl;
  cout << "3 - Mudar tipo de projecao" << endl;
  cout << "4 - Picking" << endl;
  cout << "Escolha a opcao desejada: ";
  cin >> opcao;

  return opcao;
}

void Interface::actionChosen(int opcaoEscolhida) {
  switch(opcaoEscolhida) {
    case 1:
      this->changeCameraProperties();
      break;
    case 2:
      this->modifyLightFonts();
      break;
    case 3:
      this->changeProjectionType();
      break;
    case 4:
      this->picking();
      break;
  }
}

void Interface::changeCameraProperties() {
  int chosenOption;
  cout << "1 - Mudar observador" << endl;
  cout << "2 - Mudar tamanho da janela" << endl;
  cout << "3 - Mudar distancia focal" << endl;
  cout << "Digite a opção: ";
  cin >> chosenOption;
  
  switch(chosenOption) {
    case 1:
      double eyeX, eyeY, eyeZ;
      double atX, atY, atZ;
      double upX, upY, upZ;

      cout << "Digite, separado por espaços, os valores do vetor eye: ";
      cin >> eyeX >> eyeY >> eyeZ;

      cout << "Digite, separado por espaços, os valores do vetor at: ";
      cin >> atX >> atY >> atZ;

      cout << "Digite, separado por espaços, os valores do vetor up: ";
      cin >> upX >> upY >> upZ;

      this->scene->lookAt(
        new Vector(eyeX, eyeY, eyeZ),
        new Vector(atX, atY, atZ),
        new Vector(upX, upY, upZ)
      );
      break;
    case 2:
      double windowWidth;
      double windowHeight;

      cout << "Digite o tamanho da largura da janela: ";
      cin >> windowWidth;
      cout << "Digite o tamanho da altura da janela: ";
      cin >> windowHeight;

      this->scene->setWindowWidth(windowWidth);
      this->scene->setWindowHeight(windowHeight);
      this->scene->setCanvasHeight((windowHeight / 100) * 400);
      this->scene->setCanvasWidth((windowWidth / 100) * 400);

      SDL_DestroyRenderer(this->scene->renderer);
      SDL_DestroyWindow(this->scene->window);

      initializeSDLAndWindow(&this->scene->window, &this->scene->renderer, this->scene->getCanvasWidth(), this->scene->getCanvasHeight());
      break;
    case 3:
      double distance;
      cout << "Digite a nova distancia da janela: ";
      cin >> distance;

      this->scene->setWindowDistance(distance);
      break;
  }
}

void Interface::modifyLightFonts() {
  int i = 0;

  cout << endl << "==== LISTA DE LUZES ====" << endl;
  for (Light* light : this->scene->getLights()) {
    LightType type = light->getLightType();
    switch(type) {
      case LightType::POINT:
        cout << "[" << i << "] Luz Pontual em: " << *((PointLight*) light)->initialPosition << " [" << this->lightStatus(light) << "]" << endl;
        break;
      case LightType::SPOT:
        cout << "[" << i << "] Luz Spot em: " << *((SpotLight*) light)->initialPosition << " [" << this->lightStatus(light) << "]" << endl;
        break;
      case LightType::DIRECTIONAL:
        cout << "[" << i << "] Luz Direcional com direcao: " << *((DirectionalLight*) light)->initialDirection << " [" << this->lightStatus(light) << "]" << endl;
        break;
    }

    i++;
  }
  cout << "========================" << endl << endl;

  int luzId;
  cout << "Digite o id da luz que voce quer modificar: ";
  cin >> luzId;

  Light* lightToModify = this->scene->getLights()[luzId];

  switch (lightToModify->getLightType()) {
    case LightType::POINT:
      cout << "1 - Mudar intensidade" << endl;
      cout << "2 - Mudar posicao" << endl;
      cout << "3 - Ligar/Desligar" << endl;
      cout << "Digite a opcao: ";
      int opt;
      cin >> opt;

      switch (opt) {
        case 1:
          double r, g, b;
          cout << "Digite, separado por espacos, a nova intensidade (0 a 1): ";
          cin >> r >> g >> b;

          *((PointLight*) lightToModify)->getIntensity() = Vector(r, g, b);
          break;

        case 2:
          double x, y, z;
          cout << "Digite, separado por espacos, a nova posicao: ";
          cin >> x >> y >> z;
          *((PointLight*) lightToModify)->initialPosition = Vector(x, y, z);
          ((PointLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 3:
          (lightToModify->setActive(!lightToModify->isActive()));
      }
      break;

    case LightType::DIRECTIONAL:
      cout << "1 - Mudar intensidade" << endl;
      cout << "2 - Mudar direcao" << endl;
      cout << "3 - Ligar/Desligar - Status atual: " << (lightToModify->isActive() ? "Ligada" : "Desligada") << endl;
      cout << "Digite a opcao: ";

      int opt2;
      cin >> opt2;

      switch(opt2) {
        case 1:
          double r2, g2, b2;
          cout << "Digite, separado por espacos, a nova intensidade (0 a 1): ";
          cin >> r2 >> g2 >> b2;

          *((DirectionalLight*) lightToModify)->getIntensity() = Vector(r2, g2, b2);
          break;
        case 2:
          double x2, y2, z2;
          cout << "Digite, separado por espacos, a nova direcao: ";
          cin >> x2 >> y2 >> z2;
          *((DirectionalLight*) lightToModify)->initialDirection = Vector(x2, y2, z2);
          ((DirectionalLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 3:
          (lightToModify->setActive(!lightToModify->isActive()));
          break;
      }
      break;

    case LightType::SPOT:
      cout << "1 - Mudar intensidade" << endl;
      cout << "2 - Mudar a direcao" << endl;
      cout << "3 - Mudar o angulo" << endl;
      cout << "4 - Mudar a posicao" << endl;
      cout << "5 - Ligar/Desligar - Status atual: " << (lightToModify->isActive() ? "Ligada" : "Desligada") << endl;
      cout << "Digite a opcao: ";

      int opt3;
      cin >> opt3;

      switch(opt3) {
        case 1:
          double r2, g2, b2;
          cout << "Digite, separado por espacos, a nova intensidade (0 a 1): ";
          cin >> r2 >> g2 >> b2;

          *((SpotLight*) lightToModify)->getIntensity() = Vector(r2, g2, b2);
          break;
        case 2:
          double x3, y3, z3;
          cout << "Digite, separado por espacos, a nova direcao: ";
          cin >> x3 >> y3 >> z3;
          *((SpotLight*) lightToModify)->initialDirection = Vector(x3, y3, z3);
          ((SpotLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 3:
          double angle;
          cout << "Digite o novo angulo (em radianos): ";
          cin >> angle;
          ((SpotLight*) lightToModify)->setAngle(angle);
          break;
        case 4:
          double x4, y4, z4;
          cout << "Digite, separado por espacos, a nova posicao: ";
          cin >> x4 >> y4 >> z4;
          *((SpotLight*) lightToModify)->initialPosition = Vector(x4, y4, z4);
          ((SpotLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 5:
          (lightToModify->setActive(!lightToModify->isActive()));
          break;
      }
      break;
  }
}

void Interface::changeProjectionType() {
  cout << "1 - Projecao perspectiva" << endl;
  cout << "2 - Projecao paralela" << endl;
  cout << "Digite a opcao: ";
  
  int opt;
  cin >> opt;

  switch(opt) {
    case 1:
      this->scene->setProjectionType(ProjectionType::PERSPECTIVE);
      break;
    case 2:
      this->scene->setProjectionType(ProjectionType::PARALLEL);
      break;
  }
}

void Interface::picking() {
  bool isPicking = true;
  SDL_Event event;

  while (isPicking) {
    while (SDL_PollEvent (&event) != 0) {
      switch(event.type) {
        case SDL_MOUSEBUTTONDOWN:
          this->mouseEvent(event.button);
          isPicking = false;
          break;
      }
    }
  }
}