#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "pixels.h"
#include "matrix.h"

void renderSphere (SDL_Renderer* renderer) {

    double sphereCenter[3] = { 10, 0, 0 };
    double sphereRadius = 2;

    // 90 degrees FOV
    double FOV = M_PI / 2;

    // eye position
    double eye[3] = { 0, 0, 0 };

    // eye direction
    double eyeDirection[3] = { 1, 0, 0 };

    for (int l = 0; l < 800; l++) {
        double radiusXYDir = FOV * ( (799.0 - (l << 1)) / 1598.0 );

        // unitary vector with the current XY plan directions
        double dirXY[3] = {
            eyeDirection[0] * cos (radiusXYDir),
            eyeDirection[0] * sin (radiusXYDir),
            0
        };

        for (int c = 0; c < 800; c++) {
            double radiusXZDir = FOV * ( (799.0 - (c << 1)) / 1598.0 );
            
            // unitary vector  with the current eye radius direction
            double dirXZandXY[3] = {
                dirXY[0] * cos (radiusXZDir),
                dirXY[1],
                dirXY[0] * sin (radiusXZDir)
            };

            double w[3] = {
                eye[0] - sphereCenter[0],
                eye[1] - sphereCenter[1],
                eye[2] - sphereCenter[2]
            };

            double ax = scalarProduct (dirXZandXY, dirXZandXY, 3);
            double bx = 2 * scalarProduct (w, dirXZandXY, 3);
            double cx = scalarProduct(w, w, 3) - pow (sphereRadius, 2.0);

            double delta = pow (bx, 2.0) - 4*ax*cx;

            if (delta >= 0) {
                paintPixel (renderer, l, c);
            }

            std::cout << delta << std::endl;;

        }
    }
} 

int main(int argc, char *argv[]) {
    // setup SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    initializeSDLAndWindow (&window, &renderer, 800, 800);

    setWindowBackground (renderer, 0, 0, 0, 255);
    setPaintColor (renderer, 0, 0, 255, 255);
    
    // render graphics
    renderSphere (renderer);
    update (renderer);

    // listen to close window event
    listenEventQuit (window);
 
    return 0;
}