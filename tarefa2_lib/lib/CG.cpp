#include <iostream>
#include "../include/CG.h"

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
    delete this->eyeCenter;
    
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

Vector::Vector (double x, double y, double z) {
    this->positions[0] = x;
    this->positions[1] = y;
    this->positions[2] = z;
}

double& Vector::operator [] (int idx) {
    return this->positions[idx % 3];
}

Vector Vector::operator + (const Vector& operand) {
    Vector result (
        this->positions[0] + operand.positions[0],
        this->positions[1] + operand.positions[1],
        this->positions[2] + operand.positions[2]
    );

    return result;
}

Vector Vector::operator + (const double& operand) {
    Vector result (
        this->positions[0] + operand,
        this->positions[1] + operand,
        this->positions[2] + operand
    );

    return result;
}

Vector Vector::operator - (const Vector& operand) {
    Vector result (
        this->positions[0] - operand.positions[0],
        this->positions[1] - operand.positions[1],
        this->positions[2] - operand.positions[2]
    );

    return result;
}

Vector Vector::operator - (const double& operand) {
    Vector result (
        this->positions[0] - operand,
        this->positions[1] - operand,
        this->positions[2] - operand
    );

    return result;
}

Vector Vector::operator * (const Vector& operand) {
    Vector result (
        this->positions[0] * operand.positions[0],
        this->positions[1] * operand.positions[1],
        this->positions[2] * operand.positions[2]
    );

    return result;
}

Vector Vector::operator * (const double& operand) {
    Vector result (
        this->positions[0] * operand,
        this->positions[1] * operand,
        this->positions[2] * operand
    );

    return result;
}

Vector Vector::operator / (const Vector& operand) {
    Vector result (
        this->positions[0] / operand.positions[0],
        this->positions[1] / operand.positions[1],
        this->positions[2] / operand.positions[2]
    );

    return result;
}

Vector Vector::operator / (const double& operand) {
    Vector result (
        this->positions[0] / operand,
        this->positions[1] / operand,
        this->positions[2] / operand
    );

    return result;
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
    delete this->position;
    delete this->intensity;
}

Line::Line (double P0, Vector* dir) {
    this->P0 = P0;
    this->dir = dir;
}

Line::~Line () {
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

IntersectionResult::IntersectionResult () {}

IntersectionResult::IntersectionResult (bool hasIntersection, Vector* intersectionPoint) {
    this->setHasIntersection (hasIntersection);
    this->setIntersectionPoint (intersectionPoint);
}

IntersectionResult::~IntersectionResult () {
    delete this->intersectionPoint;
}
