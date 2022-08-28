#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "pixels.h"

void renderSphere (SDL_Renderer* renderer) {
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

        for (int c = 0; c < 600; c++) {
            double radiusXZDir = FOV * ( (599.0 - (c << 1)) / 1198.0 );
            
            // unitary vector  with the current eye radius direction
            double dirXZandXY[3] = {
                dirXY[0] * cos (radiusXZDir),
                dirXY[1],
                dirXY[0] * sin (radiusXZDir)
            };

            

        }
    }
} 

int main(int argc, char *argv[]) {
    // setup SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // initializeSDLAndWindow (&window, &renderer, 800, 600);

    // setWindowBackground (renderer, 0, 0, 0, 255);
    // setPaintColor (renderer, 0, 0, 255, 255);
    
    // render graphics
    renderSphere(renderer);

    // listen to close window event
    // listenEventQuit (window);
 
    return 0;
}