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
        cout << "mesh" << endl;
        break;
      case ObjectType::PLAN:
        cout << "plan" << endl;
        break;
      case ObjectType::CYLINDER:
        cout << "cylinder" << endl;
        break;
      case ObjectType::SPHERE:
        cout << "sphere" << endl;
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
      cout << "1 - Mudar a direcao" << endl;
      cout << "2 - Mudar o angulo" << endl;
      cout << "3 - Mudar a posicao" << endl;
      cout << "4 - Ligar/Desligar - Status atual: " << (lightToModify->isActive() ? "Ligada" : "Desligada") << endl;
      cout << "Digite a opcao: ";

      int opt3;
      cin >> opt3;

      switch(opt3) {
        case 1:
          double x3, y3, z3;
          cout << "Digite, separado por espacos, a nova direcao: ";
          cin >> x3 >> y3 >> z3;
          *((SpotLight*) lightToModify)->initialDirection = Vector(x3, y3, z3);
          ((SpotLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 2:
          double angle;
          cout << "Digite o novo angulo (em radianos): ";
          cin >> angle;
          ((SpotLight*) lightToModify)->setAngle(angle);
          break;
        case 3:
          double x4, y4, z4;
          cout << "Digite, separado por espacos, a nova posicao: ";
          cin >> x4 >> y4 >> z4;
          *((SpotLight*) lightToModify)->initialPosition = Vector(x4, y4, z4);
          ((SpotLight*) lightToModify)->applyWorldToCanvasConversion(this->scene->eyeLookAt);
          break;
        case 4:
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