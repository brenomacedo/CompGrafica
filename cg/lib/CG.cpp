#include <iostream>
#include <cmath>
#include <vector>
#include "../include/utils.impl.h"
#include "../include/CG.h"
#include "../include/pixels.h"
#include "../include/image.h"

void Scene::setEyeCenter (Vector* eyeCenter) {
    this->eyeCenter = eyeCenter;
}

void Scene::setWindowHeight (double windowHeight) {
    this->windowHeight = windowHeight;
}

void Scene::setWindowWidth (double windowWidth) {
    this->windowWidth = windowWidth;
}

void Scene::setCanvasWidth (double canvasWidth) {
    this->canvasWidth = canvasWidth;
}

void Scene::setCanvasHeight (double canvasHeight) {
    this->canvasHeight = canvasHeight;
}

void Scene::setWindowDistance (double windowDistance) {
    this->windowDistance = windowDistance;
}

void Scene::setBackgroundColor (Color* color) {
    this->backgroundColor = color;
}

void Scene::setBackgroundImage (Image* image) {
    this->backgroundImage = image;
}

void Scene::setEnvironmentLight (Vector* environmentLight) {
    this->environmentLight = environmentLight;
}

void Scene::addLightSource (Light* lightSource) {
    this->lights.push_back (lightSource);
}

void Scene::addObject (Object* object) {
    this->objects.push_back (object);
}

Vector* Scene::getEyeCenter () {
    return this->eyeCenter;
}

double Scene::getWindowHeight () {
    return this->windowHeight;
}

double Scene::getWindowWidth () {
    return this->windowWidth;
}

double Scene::getCanvasWidth () {
    return this->canvasWidth;
}

double Scene::getCanvasHeight () {
    return this->canvasHeight;
}

double Scene::getWindowDistance () {
    return this->windowDistance;
}

Color* Scene::getBackgroundColor () {
    return this->backgroundColor;
}

Image* Scene::getBackgroundImage () {
    return this->backgroundImage;
}

Vector* Scene::getEnvironmentLight () {
    return this->environmentLight;
}

void Scene::raycast (SDL_Renderer* renderer) {
    const double nLin = this->getCanvasHeight ();
    const double nCol = this->getCanvasWidth ();

    const double hJanela = this->getWindowHeight ();
    const double wJanela = this->getWindowWidth ();

    const double dx = wJanela / nCol;
    const double dy = hJanela / nLin;

    Image* sceneBackgroundImage = this->getBackgroundImage ();

    int numberOfObjects = this->objects.size();

    const double z = -this->getWindowDistance();

    for (int l = 0; l < nLin; l++) {
        const double y = hJanela / 2.0 - dy / 2.0 - l * dy;

        for (int c = 0; c < nCol; c++) {
            const double x = -wJanela / 2.0 + dx / 2.0 + c * dx;

            Vector* P0 = new Vector (*this->getEyeCenter());
            Vector* direction = new Vector (x, y, z);
            Sp<Line> line = new Line (P0, direction);

            int nearestObjectIndex = 0;
            Sp<IntersectionResult> nearestResult = new IntersectionResult (false, nullptr, 0, ObjectRegion::UNKNOWN);

            for (int i = 0; i < numberOfObjects; i++) {

                Sp<IntersectionResult> result = this->objects[i]->getIntersectionResult (line.pointer);
                
                if (result->getHasIntersection() &&
                (!nearestResult->getHasIntersection() || result->getDistanceFromP0() < nearestResult->getDistanceFromP0())) {
                    delete nearestResult.pointer;
                    nearestResult.pointer = result.pointer;
                    result.pointer = nullptr;

                    nearestObjectIndex = i;
                }

            }

            if (nearestResult->getHasIntersection()) {
                Sp<Color> colorToPaint = this->objects[nearestObjectIndex]->getColorToBePainted (
                    nearestResult.pointer,
                    this->lights,
                    this->objects,
                    line.pointer,
                    this->environmentLight
                );

                setPaintColor (renderer, colorToPaint->r, colorToPaint->g, colorToPaint->b, colorToPaint->a);
                paintPixel (renderer, c, l);
            } else if (sceneBackgroundImage != nullptr) {
                // if there is no intersection, verify if there is an background image and paint
                // with the color of equivalent pixel in the image

                double x = (double (c) * double (sceneBackgroundImage->getImageWidth())) / this->getCanvasWidth ();
                double y = (double (l) * double (sceneBackgroundImage->getImageHeight())) / this->getCanvasHeight ();

                Pixel pixelToPaint = sceneBackgroundImage->getPixel (x, y);

                setPaintColor (renderer, pixelToPaint.r, pixelToPaint.g, pixelToPaint.b, pixelToPaint.a);
                paintPixel (renderer, c, l);

            }

        }
    }

}

void Scene::render () {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    initializeSDLAndWindow (&window, &renderer, this->getCanvasHeight(), this->getCanvasWidth());
    // SDL_RenderSetScale(renderer, 4, 4);

    if (this->backgroundColor == nullptr) {
        std::cout << "backgroundColor is null" << std::endl;

        setWindowBackground (
            renderer,
            0, 0, 0, 255
        );
    } else {
        setWindowBackground (
            renderer,
            this->backgroundColor->r,
            this->backgroundColor->g,
            this->backgroundColor->b,
            this->backgroundColor->a
        );
    }

    this->raycast(renderer);

    update (renderer);
    listenEventQuit (window);
}

LightsArray Scene::getLights () {
    return this->lights;
}

ObjectsArray Scene::getObjects () {
    return this->objects;
}

Scene::Scene () {}

Scene::Scene (
    Vector* eyeCenter,
    double windowHeight,
    double windowWidth,
    int canvasHeight,
    int canvasWidth,
    double windowDistance,
    Color* color
) {
    this->setEyeCenter (eyeCenter);
    this->setWindowHeight (windowHeight);
    this->setWindowWidth (windowWidth);
    this->setCanvasHeight (canvasHeight);
    this->setCanvasWidth (canvasWidth);
    this->setWindowDistance (windowDistance);
    
    if (color == nullptr) {
        this->setBackgroundColor (new Color (0, 0, 0, 255));
    } else {
        this->setBackgroundColor (color);
    }
}

Scene::~Scene () {
    delete this->getEyeCenter();
    delete this->getBackgroundImage();
    delete this->getEnvironmentLight();
    delete this->getBackgroundColor();
    
    for (auto i = this->objects.begin(); i != this->objects.end(); i++) {
        delete (*i);
    }

    for (auto i = this->lights.begin(); i != this->lights.end(); i++) {
        delete (*i);
    }
}

Color::Color (int r, int g, int b, int a) {
    this->r = r > 255 ? 255 : r; // min (r, 255)
    this->g = g > 255 ? 255 : g; // min (g, 255);
    this->b = b > 255 ? 255 : b; // min (b, 255);
    this->a = a > 255 ? 255 : a; // min (a, 255);
}

void Light::setIntensity (Vector* intensity) {
    this->intensity = intensity;
}

void Light::setPosition (Vector* position) {
    this->position = position;
}

Vector* Light::getIntensity () {
    return this->intensity;
}

Vector* Light::getPosition () {
    return this->position;
}

Light::Light () {}

Light::Light (Vector* intensity, Vector* position) {
    this->setIntensity(intensity);
    this->setPosition(position);
}

Light::~Light () {
    delete this->getPosition();
    delete this->getIntensity();
}

Line::Line (Vector* P0, Vector* dir) {
    this->P0 = P0;
    this->dir = dir;
}

Line::~Line () {
    delete this->P0;
    delete this->dir;
}

void IntersectionResult::setHasIntersection (bool hasIntersection) {
    this->hasIntersection = hasIntersection;
}

bool IntersectionResult::getHasIntersection () {
    return this->hasIntersection;
}

void IntersectionResult::setIntersectionPoint (Vector* intersectionPoint) {
    this->intersectionPoint = intersectionPoint;
}

Vector* IntersectionResult::getIntersectionPoint () {
    return this->intersectionPoint;
}

void IntersectionResult::setDistanceFromP0 (double distanceFromP0) {
    this->distanceFromP0 = distanceFromP0;
}

double IntersectionResult::getDistanceFromP0 () {
    return this->distanceFromP0;
}

void IntersectionResult::setObjectRegion (ObjectRegion region) {
    this->region = region;
}

ObjectRegion IntersectionResult::getObjectRegion () {
    return this->region;
}

IntersectionResult IntersectionResult::operator = (const IntersectionResult& result) {
    this->setDistanceFromP0(result.distanceFromP0);
    this->setHasIntersection(result.hasIntersection);
    
    if (this->getIntersectionPoint() != nullptr && result.intersectionPoint != nullptr) {
        *this->getIntersectionPoint() = *result.intersectionPoint;
    }

    return *this;
}

IntersectionResult::IntersectionResult () {}

IntersectionResult::IntersectionResult (bool hasIntersection, Vector* intersectionPoint, double distanceFromP0, ObjectRegion region) {
    this->setHasIntersection (hasIntersection);
    this->setIntersectionPoint (intersectionPoint);
    this->setDistanceFromP0 (distanceFromP0);
    this->setObjectRegion (region);
}

IntersectionResult::IntersectionResult (const IntersectionResult& result) {
    this->distanceFromP0 = result.distanceFromP0;
    this->hasIntersection = result.hasIntersection;
    
    if (result.intersectionPoint != nullptr) {
        this->intersectionPoint = new Vector (*result.intersectionPoint);
    }
}

IntersectionResult::~IntersectionResult () {
    delete this->getIntersectionPoint();
}

Object::~Object () {}

Color* Object::calculateColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight,
    Vector* normal,
    Vector* reflectivity,
    double shininess,
    Object* objAddr
) {

    Vector resultColorRate (0, 0, 0);

    Vector v = ((*line->dir) * -1) / line->dir->getMagnitude();

    for (auto i = lightsArray.begin(); i != lightsArray.end(); i++) {

        Vector* intersectionPoint = intersectionResult->getIntersectionPoint();
        
        Vector l = (*((*i)->getPosition()) - *intersectionPoint) / (*((*i)->getPosition()) - *intersectionResult->getIntersectionPoint()).getMagnitude();
        // verify if the lights intercepts any other object

        Sp<Line> verifyShadowLine = new Line (
            new Vector (
                (*intersectionPoint)
            ),
            new Vector (l)
        );

        bool hasIntersectionWithOtherObjects = false;

        for (auto j = objectsArray.begin(); (j != objectsArray.end() && !hasIntersectionWithOtherObjects); j++) {
            
            if ((*j) != objAddr) {
                Sp<IntersectionResult> intersectionShadow = (*j)->getIntersectionResult (verifyShadowLine.pointer);

                hasIntersectionWithOtherObjects =
                    intersectionShadow->getHasIntersection() &&
                    (intersectionShadow->getDistanceFromP0() < intersectionResult->getDistanceFromP0());
            }

        }

        // calculate the color to be painted
        if (!hasIntersectionWithOtherObjects) {    
            Vector r = (*normal) * (2 * scalarProduct (l, *normal)) -  l;

            double fDifusa = max (
                scalarProduct (l, *normal),
                0.0
            );

            double fEspeculada = pow (
                max (
                    scalarProduct (r, v),
                    0.0
                ),
                shininess
            );

            Vector iDifusa = (*(*i)->getIntensity()) * (*reflectivity) * fDifusa;

            Vector iEspeculada = (*(*i)->getIntensity()) * (*reflectivity) * fEspeculada;

            resultColorRate = resultColorRate + iDifusa + iEspeculada;
        }


    }

    if (environmentLight != nullptr) {
        resultColorRate = resultColorRate + ((*environmentLight) * (*reflectivity));
    }

    return new Color (
        resultColorRate[0] * 255,
        resultColorRate[1] * 255,
        resultColorRate[2] * 255,
        255
    );

}
