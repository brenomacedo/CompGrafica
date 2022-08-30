#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "pixels.h"
#include "matrix.h"

#define nCol 800.0
#define nLin 800.0


void renderSphere (SDL_Renderer* renderer) {

    double wJanela = 100.0;
    double hJanela = 100.0;
    double dJanela = 50.0;

    double windowCenter[3] = { 0.0, 0.0, -dJanela };

    double eyeCenter[3] = { 0.0, 0.0, 0.0 };

    double rEsfera = 10.0;

    double centroEsfera[3] = { 0.0, 0.0, -80.0 };

    double dx = wJanela / nCol;
    double dy = hJanela / nLin;

    double w[3] = {
        eyeCenter[0] - centroEsfera[0],
        eyeCenter[1] - centroEsfera[1],
        eyeCenter[2] - centroEsfera[2]
    };

    double z = -dJanela;
    for (int l = 0; l < nLin; l++) {
        double y = hJanela / 2.0 -  dy / 2.0  - l * dy; 

        for (int c = 0; c < nCol; c++) {
            double x = -wJanela / 2.0 + dx / 2.0  + c*dx;

            double dir[3] = { x, y, z };

            double ax = scalarProduct (dir, dir , 3);
            double bx = 2 * scalarProduct (w, dir, 3);
            double cx = scalarProduct(w, w, 3) - pow (rEsfera, 2.0);

            double delta = pow (bx, 2.0) - 4*ax*cx;

            if (delta >= 0) {
                paintPixel (renderer, c, l);
            }
        }
    }
} 

int main(int argc, char *argv[]) {
    // setup SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    initializeSDLAndWindow (&window, &renderer, nCol, nLin);

    setWindowBackground (renderer, 100, 100, 100, 255);
    setPaintColor (renderer, 255, 0, 0, 255);
    
    // render graphics
    renderSphere (renderer);
    update (renderer);

    // listen to close window event
    listenEventQuit (window);
 
    return 0;
}