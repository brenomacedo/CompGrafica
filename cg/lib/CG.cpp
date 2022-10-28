#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "../include/utils.impl.h"
#include "../include/CG.h"
#include "../include/pixels.h"
#include "../include/image.h"

void LookAt::setAt(Vector* at) {
    this->at = at;
}

Vector* LookAt::getAt() {
    return this->at;
}

void LookAt::setEye(Vector* eye) {
    this->eye = eye;
}

Vector* LookAt::getEye() {
    return this->eye;
}

void LookAt::setUp(Vector* up) {
    this->up = up;
}

Vector* LookAt::getUp() {
    return this->up;
}

LookAt::LookAt() {}

LookAt::LookAt(
    Vector* eye,
    Vector* at,
    Vector* up
) {
    this->setEye(eye);
    this->setAt(at);
    this->setUp(up);
}

LookAt::~LookAt() {
    delete this->getAt();
    delete this->getEye();
    delete this->getUp();
}

Vector LookAt::convertWorldLineToCanvas(Vector worldLine) {
    Vector K = *this->getEye() - *this->getAt();
    Vector Kc = K / K.getMagnitude();
    
    Vector Vup = *this->getUp() - *this->getEye();
    Vector I = vectorProduct(Vup, Kc);
    Vector Ic = I / I.getMagnitude();

    Vector Jc = vectorProduct(Kc, Ic);

    double minusIcPlusEye = 0;
    double minusJcPlusEye = 0;
    double minusKcPlusEye = 0;

    return Vector(
        minusIcPlusEye + Ic[2]*worldLine[2] + Ic[1]*worldLine[1] + Ic[0]*worldLine[0],
        minusJcPlusEye + Jc[2]*worldLine[2] + Jc[1]*worldLine[1] + Jc[0]*worldLine[0],
        minusKcPlusEye + Kc[2]*worldLine[2] + Kc[1]*worldLine[1] + Kc[0]*worldLine[0]
    );
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

void Scene::lookAt(
    Vector* eye,
    Vector* at,
    Vector* up
) {
    delete this->eyeLookAt;
    this->eyeLookAt = new LookAt(
        eye, at, up
    );
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

            Vector* direction = new Vector(
                this->eyeLookAt->convertWorldLineToCanvas(Vector (x, y, z))
            );


            Vector* P0 = new Vector(
                *this->eyeLookAt->getEye()
            );

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
    double windowHeight,
    double windowWidth,
    int canvasHeight,
    int canvasWidth,
    double windowDistance,
    Color* color
) {
    this->setWindowHeight (windowHeight);
    this->setWindowWidth (windowWidth);
    this->setCanvasHeight (canvasHeight);
    this->setCanvasWidth (canvasWidth);
    this->setWindowDistance (windowDistance);
    this->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 0, -1),
        new Vector(0, 1, 0)
    );
    
    if (color == nullptr) {
        this->setBackgroundColor (new Color (0, 0, 0, 255));
    } else {
        this->setBackgroundColor (color);
    }
}

Scene::~Scene () {
    delete this->getBackgroundImage();
    delete this->getEnvironmentLight();
    delete this->getBackgroundColor();
    delete this->eyeLookAt;
    
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

Vector* Light::getIntensity () {
    return this->intensity;
}

Light::Light () {}

Light::Light (Vector* intensity) {
    this->setIntensity(intensity);
}

Light::~Light () {
    delete this->getIntensity();
}

IlluminationInfo::IlluminationInfo() {}

IlluminationInfo::IlluminationInfo(Vector l, Vector intensity) {
    this->l = l;
    this->intensity = intensity;
}

void PointLight::setPosition(Vector* position) {
    this->position = position;
}

Vector* PointLight::getPosition() {
    return this->position;
}

double PointLight::getDistanceFromPoint(Vector point) {
    return (*this->getPosition() - point).getMagnitude();
}

IlluminationInfo PointLight::getIlluminationInfo(Vector intersectionPoint) {
    Vector l = (*this->getPosition() - intersectionPoint) / (*this->getPosition()
        - intersectionPoint).getMagnitude();

    Vector intensity = *this->getIntensity();

    return IlluminationInfo(
        l, intensity
    );
}

PointLight::PointLight() {}

PointLight::PointLight(Vector* intensity, Vector* position) : Light::Light(intensity) {
    this->setPosition(position);
}

PointLight::~PointLight() {
    delete this->getPosition();
}

void DirectionalLight::setDirection(Vector* direction) {
    this->direction = direction;
}

Vector* DirectionalLight::getDirection() {
    return this->direction;
}

double DirectionalLight::getDistanceFromPoint(Vector) {
    return std::numeric_limits<double>::infinity();
}

IlluminationInfo DirectionalLight::getIlluminationInfo(Vector) {
    Vector lNotNormalized = *this->getDirection() * -1;
    Vector l = lNotNormalized / lNotNormalized.getMagnitude();
    Vector intensity = *this->getIntensity();

    return IlluminationInfo(
        l, intensity
    );
}

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(Vector* intensity, Vector* direction) : Light::Light(intensity) {
    this->setDirection(direction);
}

DirectionalLight::~DirectionalLight() {
    delete this->getDirection();
}

void SpotLight::setDirection(Vector* direction) {
    this->direction = new Vector(*direction / direction->getMagnitude());
}

Vector* SpotLight::getDirection() {
    return this->direction;
}

void SpotLight::setPosition(Vector* position) {
    this->position = position;
}

Vector* SpotLight::getPosition() {
    return this->position;
}

void SpotLight::setAngle(double angle) {
    this->angle = angle;
}

double SpotLight::getAngle() {
    return this->angle;
}

double SpotLight::getDistanceFromPoint(Vector point) {
    return (*this->getPosition() - point).getMagnitude();
}

IlluminationInfo SpotLight::getIlluminationInfo(Vector intersectionPoint) {
    Vector l = (*this->getPosition() - intersectionPoint) / (*this->getPosition()
        - intersectionPoint).getMagnitude();
    double clds = scalarProduct(l, (*this->getDirection() * -1));

    Vector spotIntensity = *this->getIntensity();

    Vector intensity;

    if (clds < cos(angle)) {
        intensity = Vector(0, 0, 0);
    } else {
        intensity = spotIntensity * clds;
    }

    return IlluminationInfo(
        l, intensity
    );
}

SpotLight::SpotLight() {}

SpotLight::SpotLight(Vector* intensity, Vector* direction, Vector* position, double angle) {
    this->setIntensity(intensity);
    this->setDirection(direction);
    this->setPosition(position);
    this->setAngle(angle);
}

SpotLight::~SpotLight() {
    delete this->getDirection();
    delete this->getPosition();
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

void Object::setReflectivity (Vector* reflectivity) {
    this->reflectivity = reflectivity;
}

Vector* Object::getReflectivity () {
    return this->reflectivity;
}

void Object::setShininess (double shininess) {
    this->shininess = shininess;
}

double Object::getShininess () {
    return this->shininess;
}

Object::Object () {}

Object::Object (Vector* reflectivity) {
    this->reflectivity = reflectivity;
}

Object::~Object () {
    delete this->getReflectivity();
}

Color* Object::calculateColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight,
    Vector* normal,
    Vector* reflectivity,
    double shininess
) {

    Vector resultColorRate = this->calculateResultColorRate(
        line,
        intersectionResult,
        lightsArray,
        objectsArray,
        normal,
        reflectivity,
        shininess
    );

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

Vector Object::calculateResultColorRate(
    Line* line,
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Vector* normal,
    Vector* reflectivity,
    double shininess
) {

    Vector resultColorRate (0, 0, 0);

    Vector v = ((*line->dir) * -1) / line->dir->getMagnitude();

    Vector* intersectionPoint = intersectionResult->getIntersectionPoint();

    // verify if the lights intercepts any other object

    for (auto i = lightsArray.begin(); i != lightsArray.end(); i++) {

        IlluminationInfo illuminationInfo = (*i)->getIlluminationInfo(*intersectionPoint);
        Vector l = illuminationInfo.l;
        Vector intensity = illuminationInfo.intensity;
        
        bool hasIntersectionWithOtherObjects = this->hasIntersectionWithOtherObjects(
            objectsArray, intersectionPoint, new Vector(l), *i
        );

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

            Vector iDifusa = intensity * (*reflectivity) * fDifusa;

            Vector iEspeculada = intensity * (*reflectivity) * fEspeculada;

            resultColorRate = resultColorRate + iDifusa + iEspeculada;
        }
    }

    return resultColorRate;
}

bool Object::hasIntersectionWithOtherObjects(ObjectsArray objectsArray, Vector* intersectionPoint, Vector* l, Light* light) {

    Sp<Line> verifyShadowLine = new Line (
        new Vector (
            (*intersectionPoint)
        ),
        l
    );

    bool hasIntersectionWithOtherObjects = false;

    for (auto j = objectsArray.begin(); (j != objectsArray.end() && !hasIntersectionWithOtherObjects); j++) {
        
        if ((*j) != this) {
            Sp<IntersectionResult> intersectionShadow = (*j)->getIntersectionResult (verifyShadowLine.pointer);

            hasIntersectionWithOtherObjects =
                intersectionShadow->getHasIntersection() &&
                (intersectionShadow->getDistanceFromP0() < (light->getDistanceFromPoint(*intersectionPoint)));
        }

    }

    return hasIntersectionWithOtherObjects;
}
