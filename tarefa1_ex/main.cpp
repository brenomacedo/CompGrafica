#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "pixels"

#define nLin 800.0
#define nCol 800.0

double scalarProduct (double *a, double *b, int n) {
    double result = 0;

    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    return result;
}

void renderSphere (SDL_Renderer* renderer) {

    double wJanela = 100.0;
    double hJanela = 100.0;
    double dJanela = 10.0;

    double windowCenter[3] = { 0.0, 0.0, -dJanela };

    double eyeCenter[3] = { 0.0, 0.0, 0.0 };

    double rEsfera = 30.0;

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
        double y = hJanela / 2.0 - dy / 2.0 - l * dy;

        for (int c = 0; c < nCol; c++) {
            double x = -wJanela / 2.0 + dx / 2.0 + c * dx;

            double dir[3] = { x, y, z };

            double ax = scalarProduct(dir, dir, 3);
            double bx = 2 * scalarProduct (w, dir, 3);
            double cx = scalarProduct (w, w, 3) - pow (rEsfera, 2.0);

            double delta = pow (bx, 2.0) - 4*ax*cx;

            if (delta >= 0) {
                paintPixel (renderer, c, l);
            }
        }
    }

}

int main () {

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    initializeSDLAndWindow (&window, &renderer, nLin, nCol);
    // SDL_RenderSetScale(renderer, 4, 4);
    
    setWindowBackground (renderer, 100, 100, 100, 255);
    // update (renderer);

    // SDL_Delay (1000);

    setPaintColor (renderer, 255, 0, 0, 255);
    renderSphere (renderer);

    update (renderer);
    listenEventQuit (window);
    
    return 0;
}