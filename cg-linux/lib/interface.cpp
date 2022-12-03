#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "../include/pixels.h"
#include "../include/interface.h"
#include "../include/CG.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

string Interface::lightStatus(Light* light) {
  return (light->isActive() ? "Ligada" : "Desligada");
}

void Interface::mouseEvent(SDL_MouseButtonEvent& event) {
  if (event.button == SDL_BUTTON_LEFT) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    cout << "x: " << x << " y: " << y << endl;
  }
}

void Interface::listenEvents() {
  SDL_Event event;
  bool isRunning = true;
  bool isPicking = false;

  // scene->lookAt(
  //       new Vector(100, 100, 100),
  //       new Vector(0, 25, 0),
  //       new Vector(100, 400, 100)
  //     );
  // scene->raycast();
  // scene->update();

  // SDL_AtomicSet(&active, 1);
  // SDL_CreateThread(inputThread, "InputThread", this);

  // while (SDL_AtomicGet(&active)) {
  //     while (SDL_PollEvent (&event) != 0) {
  //       switch(event.type) {
  //         case SDL_QUIT:
  //           isRunning = false;
  //           break;
  //         case SDL_MOUSEBUTTONDOWN:
  //           this->mouseEvent(event.button);
  //           break;
  //         }
  //     }

  //     SDL_UpdateWindowSurface (this->scene->window);
  // }

  while (isRunning) {
    int opt = this->showMenu();

    if (opt == 0) {
      isRunning = false;
    } else {
      this->actionChosen(opt);
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

      cout << this->scene->getCanvasWidth() << endl;
      cout << this->scene->getCanvasHeight() << endl;

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

  this->scene->raycast();
  this->scene->update();
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

  this->scene->raycast();
  this->scene->update();
}