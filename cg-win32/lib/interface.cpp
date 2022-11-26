#include <SDL2/SDL.h>
#include <iostream>
#include "../include/interface.h"

void Interface::mouseEvent(SDL_MouseButtonEvent& event, Scene*) {
  if (event.button == SDL_BUTTON_LEFT) {
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    std::cout << "x: " << x << " y: " << y << std::endl;
  }
}

void Interface::listenEvents(SDL_Window* window, Scene* scene) {
  SDL_Event event;
  bool isRunning = true;


  while (isRunning) {
      while (SDL_PollEvent (&event) != 0) {
          switch(event.type) {
              case SDL_QUIT:
                  isRunning = false;
                  break;
              case SDL_MOUSEBUTTONDOWN:
                  this->mouseEvent(event.button, scene);
                  break;
          }
      }

      SDL_UpdateWindowSurface (window);
  }

  SDL_DestroyWindow (window);
  SDL_Quit ();
}