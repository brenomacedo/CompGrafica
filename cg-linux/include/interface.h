#pragma once

#include <SDL2/SDL.h>
#include <string>

class Scene;
class Light;

class Interface {
  private:
    void mouseEvent(SDL_MouseButtonEvent& event);
    std::string lightStatus(Light* light);
  public:
    Scene* scene = nullptr;
    void listenEvents();
    int showMenu();
    void actionChosen(int optionChosen);
    void changeCameraProperties();
    void modifyLightFonts();
    void changeProjectionType();
    void picking();
    void transformLinks();
};