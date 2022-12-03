#pragma once

#include <SDL2/SDL.h>

class Scene;

class Interface {
  private:
    void mouseEvent(SDL_MouseButtonEvent& event, Scene* renderer);
  public:
    void listenEvents(Scene* renderer);
    int showMenu();
    void actionChosen(int optionChosen, Scene* scene);
    void changeCameraProperties(Scene* scene);
};