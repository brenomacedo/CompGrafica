#pragma once

#include <SDL2/SDL.h>

class Scene;

class Interface {
  private:
    void mouseEvent(SDL_MouseButtonEvent& event, Scene* renderer);
  public:
    void listenEvents (SDL_Window* window, Scene* renderer);
};