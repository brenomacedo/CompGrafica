#pragma once

#include <SDL2/SDL.h>

void paintPixel (SDL_Renderer* renderer, int x, int y);
void _update (SDL_Renderer* renderer);
void setPaintColor (SDL_Renderer* renderer, int r, int g, int b, int a);
void setWindowBackground (SDL_Renderer* renderer, int r, int g, int b, int a);
void initializeSDLAndWindow (
    SDL_Window** window,
    SDL_Renderer** renderer,
    int width,
    int height
);