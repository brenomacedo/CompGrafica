#include <SDL2/SDL.h>
#include <iostream>
#include "../include/pixels.h"

void paintPixel (SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint (renderer, x, y);
}

void _update (SDL_Renderer* renderer) {
    SDL_RenderPresent (renderer);
}

void setPaintColor (SDL_Renderer* renderer, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor (renderer, r, g, b, a);
}

void setWindowBackground (SDL_Renderer* renderer, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor (renderer, r, g, b, a);
    SDL_RenderClear (renderer);
}

void initializeSDLAndWindow (
    SDL_Window** window,
    SDL_Renderer** renderer,
    int width,
    int height
) {
    SDL_Init (SDL_INIT_VIDEO);

    // SDL_CreateWindowAndRenderer (
    //     800*4, 600*4, 0, &window, &renderer
    // );
    // SDL_RenderSetScale(renderer, 4, 4);

    SDL_CreateWindowAndRenderer (
        width, height, 0, window, renderer
    );
}