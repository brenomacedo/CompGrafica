#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "pixels.h"
#include "matrix.h"

#define nCol 1000.0
#define nLin 1000.0


void renderSphere (SDL_Renderer* renderer) {

    // ========================== sphere data ========================

    double wJanela = 50.0;
    double hJanela = 50.0;
    double dJanela = 50.0;

    double windowCenter[3] = { 0.0, 0.0, -dJanela };

    double eyeCenter[3] = { 0.0, 0.0, 0.0 };

    double rEsfera = 10.0;

    double centroEsfera[3] = { 0.0, 0.0, -50.0 };

    // reflectivity of sphere (k) // red
    double reflectivity[3] = { 255, 0, 0 };

    double dx = wJanela / nCol;
    double dy = hJanela / nLin;

    double w[3] = {
        eyeCenter[0] - centroEsfera[0],
        eyeCenter[1] - centroEsfera[1],
        eyeCenter[2] - centroEsfera[2]
    };

    double fAmbiente[3] = {
        0.05, 0.05, 0.05
    };

    double iAmbiente [3] = {
        reflectivity[0] * fAmbiente[0],                
        reflectivity[1] * fAmbiente[1],                
        reflectivity[2] * fAmbiente[2]                
    };

    // ===============================================================

    // ==================== light source data ======================

    double lightSourcePosition[3] = { 0.0, 5.0, 0.0 };

    double lightSourceIntensity[3] = { 0.7, 0.7, 0.7 };

    // ===============================================================

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
                // paintPixel (renderer, c, l);

                double t = (-bx - sqrt(delta)) / (2*ax);

                // pi
                double intersectionPoint[3] = {
                    eyeCenter[0] + dir[0] * t,
                    eyeCenter[1] + dir[1] * t,
                    eyeCenter[2] + dir[2] * t
                };

                // pf - pi
                double sourceMinusIntersection[3] = {
                    lightSourcePosition[0] - intersectionPoint[0],
                    lightSourcePosition[1] - intersectionPoint[1],
                    lightSourcePosition[2] - intersectionPoint[2]
                };

                // || pf - pi ||
                double sourceMinusIntersectionMagnitude = magnitude (sourceMinusIntersection, 3); 

                // l = (pf - pi) / (|| pf - pi ||);
                double lx[3] = {
                    sourceMinusIntersection[0] / sourceMinusIntersectionMagnitude,
                    sourceMinusIntersection[1] / sourceMinusIntersectionMagnitude,
                    sourceMinusIntersection[2] / sourceMinusIntersectionMagnitude
                };

                // normal of sphere at intersection point
                double n[3] = {
                    (intersectionPoint[0] - centroEsfera[0]) / rEsfera,
                    (intersectionPoint[1] - centroEsfera[1]) / rEsfera,
                    (intersectionPoint[2] - centroEsfera[2]) / rEsfera
                };

                double directionMagnitude = magnitude (dir, 3);

                // vector with opposite direction of dr
                double v[3] = {
                    -dir[0] / directionMagnitude,
                    -dir[1] / directionMagnitude,
                    -dir[2] / directionMagnitude,
                };

                // l * n
                double lscalarProductN = scalarProduct(lx, n, 3);

                // r = 2 * (l * n) * n - l
                double r[3] = {
                    2 * lscalarProductN * n[0] - lx[0],
                    2 * lscalarProductN * n[1] - lx[1],
                    2 * lscalarProductN * n[2] - lx[2]
                };

                double fDifusa = max (
                    scalarProduct (lx, n, 3),
                    0.0
                );

                double fEspeculada = max (
                    scalarProduct (r, v, 3),
                    0.0
                );

                // (Ifonte @ k) * fdifusa
                double iDifusa[3] = {
                    lightSourceIntensity[0] * reflectivity[0] * fDifusa,
                    lightSourceIntensity[1] * reflectivity[1] * fDifusa,
                    lightSourceIntensity[2] * reflectivity[2] * fDifusa
                };

                // (Ifonte @ k) * fespeculada
                double iEspeculada[3] = {
                    lightSourceIntensity[0] * reflectivity[0] * fEspeculada,
                    lightSourceIntensity[1] * reflectivity[1] * fEspeculada,
                    lightSourceIntensity[2] * reflectivity[2] * fEspeculada
                };

                double colorRGBToPaint[3] = {
                    iDifusa[0] + iEspeculada[0] + iAmbiente[0],
                    iDifusa[1] + iEspeculada[1] + iAmbiente[1],
                    iDifusa[2] + iEspeculada[2] + iAmbiente[2]
                };

                setPaintColor (
                    renderer,
                    min  (colorRGBToPaint[0], 255),
                    min  (colorRGBToPaint[1], 255),
                    min  (colorRGBToPaint[2], 255),
                    255
                );

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
    
    // render graphics
    renderSphere (renderer);
    update (renderer);

    // listen to close window event
    listenEventQuit (window);
 
    return 0;
}