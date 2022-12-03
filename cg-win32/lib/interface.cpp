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

void Interface::mouseEvent(SDL_MouseButtonEvent& event, Scene*) {
  if (event.button == SDL_BUTTON_LEFT) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    cout << "x: " << x << " y: " << y << endl;
  }
}

void Interface::listenEvents(Scene* scene) {
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

  while (isRunning) {
      while (SDL_PollEvent (&event) != 0) {
        if (isPicking) {
          switch(event.type) {
              case SDL_QUIT:
                  isRunning = false;
                  break;
              case SDL_MOUSEBUTTONDOWN:
                  this->mouseEvent(event.button, scene);
                  break;
          }
        } else {
          int opcaoEscolhida = this->showMenu();
          this->actionChosen(opcaoEscolhida, scene);
        }
      }

      SDL_UpdateWindowSurface (scene->window);
  }

  SDL_DestroyWindow (scene->window);
  SDL_Quit ();
}

int Interface::showMenu() {
  int opcao;

  cout << "1 - Modificar parametros da camera" << endl;
  cout << "Escolha a opcao desejada: ";
  cin >> opcao;

  return opcao;
}

void Interface::actionChosen(int opcaoEscolhida, Scene* scene) {
  switch(opcaoEscolhida) {
    case 1:
      this->changeCameraProperties(scene);
      break;
  }
}

void Interface::changeCameraProperties(Scene* scene) {
  int chosenOption;
  cout << "1 - Mudar observador" << endl;
  cout << "2 - Mudar tamanho da janela" << endl;
  cout << "3 - Mudar distancia focal" << endl;
  cout << "Digite a opção: ";
  cin >> chosenOption;
  double eyeX, eyeY, eyeZ;
  double atX, atY, atZ;
  double upX, upY, upZ;

  // cout << "Digite, separado por espaços, os valores do vetor eye: ";
  // cin >> eyeX >> eyeY >> eyeZ;

  // cout << "Digite, separado por espaços, os valores do vetor at: ";
  // cin >> atX >> atY >> atZ;

  // cout << "Digite, separado por espaços, os valores do vetor up: ";
  // cin >> upX >> upY >> upZ;

  // // scene->lookAt(
  // //   new Vector(eyeX, eyeY, eyeZ),
  // //   new Vector(atX, atY, atZ),
  // //   new Vector(upX, upY, upZ)
  // // );

  scene->lookAt(
    new Vector(100, 100, 100),
    new Vector(0, 25, 0),
    new Vector(100, 400, 100)
  );
  scene->raycast();
  scene->update();
}