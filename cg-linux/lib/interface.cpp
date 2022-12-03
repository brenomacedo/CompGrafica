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
  cout << "Escolha a opcao desejada: ";
  cin >> opcao;

  return opcao;
}

void Interface::actionChosen(int opcaoEscolhida) {
  switch(opcaoEscolhida) {
    case 1:
      this->changeCameraProperties();
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