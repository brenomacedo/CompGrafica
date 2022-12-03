#pragma once

#include <SDL2/SDL.h>

class Scene;

class Interface {
  private:
    void mouseEvent(SDL_MouseButtonEvent& event);
  public:
    Scene* scene = nullptr;
    void listenEvents();
    int showMenu();
    void actionChosen(int optionChosen);
    void changeCameraProperties();
};