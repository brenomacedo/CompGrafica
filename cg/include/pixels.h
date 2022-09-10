#pragma once

#include <SDL2/SDL.h>

void paintPixel (SDL_Renderer* renderer, int x, int y);
void update (SDL_Renderer* renderer);
void setPaintColor (SDL_Renderer* renderer, int r, int g, int b, int a);
void setWindowBackground (SDL_Renderer* renderer, int r, int g, int b, int a);
void listenEventQuit (SDL_Window* window);
void initializeSDLAndWindow (
    SDL_Window** window,
    SDL_Renderer** renderer,
    int width,
    int height
);