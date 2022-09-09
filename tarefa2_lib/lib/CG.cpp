#include <iostream>
#include <cmath>
#include <vector>
#include "../include/utils.impl.h"
#include "../include/CG.h"
#include "../include/pixels.h"

double min (double a, double b) {
    if (a < b) {
        return a;
    }

    return b;
}

double max (double a, double b) {
    if (a > b) {
        return a;
    }

    return b;
}

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

void Scene::raycast (SDL_Renderer* renderer) {
    const double nLin = this->getCanvasHeight ();
    const double nCol = this->getCanvasWidth ();

    const double hJanela = this->getWindowHeight ();
    const double wJanela = this->getWindowWidth ();

    const double dx = wJanela / nCol;
    const double dy = hJanela / nLin;

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
                Sp<Color> colorToPaint = this->objects[nearestObjectIndex]->getColorToBePainted (nearestResult.pointer, this->lights, line.pointer);

                setPaintColor (renderer, colorToPaint->r, colorToPaint->g, colorToPaint->b, colorToPaint->a);
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
    }

    setWindowBackground (
        renderer,
        this->backgroundColor->r,
        this->backgroundColor->g,
        this->backgroundColor->b,
        this->backgroundColor->a
    );

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

Vector::Vector () {}

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

double Vector::getMagnitude () {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += pow (this->positions[i], 2.0);
    }

    return sqrt (result);
}

double scalarProduct (Vector a, Vector b)  {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += a[i] * b[i];
    }

    return result;
}

double scalarProduct (Vector *a, Vector *b)  {
    double result = 0;

    for (int i = 0; i < 3; i++) {
        result += (*a)[i] * (*b)[i];
    }

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
    this->distanceFromP0 = result.distanceFromP0;
    this->hasIntersection = result.hasIntersection;
    
    if (this->intersectionPoint != nullptr && result.intersectionPoint != nullptr) {
        *this->intersectionPoint = *result.intersectionPoint;
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
    delete this->intersectionPoint;
}

ObjectType Sphere::getObjectType () {
    return this->type;
}

void Sphere::setRadius (double radius) {
    this->radius = radius;
}

double Sphere::getRadius () {
    return this->radius;
}

void Sphere::setReflectivity (Vector* reflectivity) {
    this->reflectivity = reflectivity;
}

Vector* Sphere::getReflectivity () {
    return this->reflectivity;
}

void Sphere::setCenter (Vector* center) {
    this->center = center;
}

Vector* Sphere::getCenter () {
    return this->center;
}

void Sphere::setShininess (double shininess) {
    this->shininess = shininess;
}

double Sphere::getShininess () {
    return this->shininess;
}

Sphere::Sphere () {}

Sphere::Sphere (double radius, Vector* reflectivity, Vector* center, double shininess) {
    this->setRadius (radius);
    this->setReflectivity (reflectivity);
    this->setCenter (center);
    this->setShininess (shininess);
}

Sphere::~Sphere () {
    delete this->reflectivity;
    delete this->center;
}

IntersectionResult* Sphere::getIntersectionResult (Line* line) {

    Vector w = *(line->P0) - *(this->center);

    double a = scalarProduct (line->dir, line->dir);
    double b = 2 * scalarProduct (w, *(line->dir));
    double c = scalarProduct (w, w) - pow (this->radius, 2.0);

    double discriminant = (pow (b, 2.0) - 4 * a * c);

    double t;
    IntersectionResult* result = new IntersectionResult ();
    result->setObjectRegion (ObjectRegion::SPHERE_SURFACE);

    if (discriminant == 0) {
        result->setHasIntersection (true);
        t = (-b + sqrt(discriminant)) / (2 * a);

        Vector* intersectionPoint = new Vector();
        *intersectionPoint = (*line->P0) + (*line->dir) * t;
        result->setIntersectionPoint (intersectionPoint);

        Vector distanceFromP0Vector = (*line->P0) - (*intersectionPoint);
        double distanceBetweenP0AndIntersection = distanceFromP0Vector.getMagnitude();
        result->setDistanceFromP0 (distanceBetweenP0AndIntersection);

    } else if (discriminant > 0) {
        result->setHasIntersection (true);

        double t1 = (-b + sqrt(discriminant)) / (2 * a);
        double t2 = (-b - sqrt(discriminant)) / (2 * a);

        Vector intersectionPoint1 = (*line->P0) + (*line->dir) * t1;
        Vector intersectionPoint2 = (*line->P0) + (*line->dir) * t2;

        double distanceP0toT1 = intersectionPoint1.getMagnitude ();
        double distanceP0toT2 = intersectionPoint2.getMagnitude ();

        Vector* intersectionPoint = new Vector ();

        if (distanceP0toT1 < distanceP0toT2) {

            *intersectionPoint = intersectionPoint1;
            result->setDistanceFromP0 (distanceP0toT1);

        } else {

            *intersectionPoint = intersectionPoint2;
            result->setDistanceFromP0 (distanceP0toT2);

        }

        result->setIntersectionPoint (intersectionPoint);

    } else {
        result->setHasIntersection (false);
    }

    return result;

}

Color* Sphere::getColorToBePainted (IntersectionResult* intersectionResult, LightsArray lightsArray, Line* line) {
    
    Vector resultColorRate (0, 0, 0);

    Vector n = (*intersectionResult->getIntersectionPoint() - *this->center) / this->radius;

    Vector v = ((*line->dir) * (-1)) / line->dir->getMagnitude();

    for (auto i = lightsArray.begin(); i != lightsArray.end(); i++) {

        Vector sourceMinusIntersection = *((*i)->getPosition()) - *intersectionResult->getIntersectionPoint();

        double sourceMinusIntersectionMagnitude = sourceMinusIntersection.getMagnitude();

        Vector l = sourceMinusIntersection / sourceMinusIntersectionMagnitude;

        double lScalarProductN = scalarProduct (l, n);

        Vector r = n * (2 * lScalarProductN) - l;

        double fDifusa = max (
            0.0,
            scalarProduct (l, n)
        );

        double fEspeculada = pow (
            max (
                0.0,
                scalarProduct (r, v)
            ),
            this->getShininess()
        );

        Vector iDifusa = (*(*i)->getIntensity()) * (*this->getReflectivity()) * fDifusa;

        Vector iEspeculada = (*(*i)->getIntensity()) * (*this->getReflectivity()) * fEspeculada;

        resultColorRate = resultColorRate + iDifusa + iEspeculada;
    }


    return new Color (
        resultColorRate[0] * 255,
        resultColorRate[1] * 255,
        resultColorRate[2] * 255,
        255
    );


}

ObjectType Plan::getObjectType () {
    return this->type;
}

void Plan::setInitialPoint (Vector* initialPoint) {
    this->initialPoint = initialPoint;
}

Vector* Plan::getInitialPoint () {
    return this->initialPoint;
} 

void Plan::setNormal (Vector* normal) {
    this->normal = normal;
}

Vector* Plan::getNormal () {
    return this->normal;
}

void Plan::setReflectivity (Vector* reflectivity) {
    this->reflectivity = reflectivity;
}

Vector* Plan::getReflectivity () {
    return this->reflectivity;
}

void Plan::setShininess (double shininess) {
    this->shininess = shininess;
}

double Plan::getShininess () {
    return this->shininess;
}

Plan::Plan () {}

Plan::Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess) {
    this->initialPoint = initialPoint;
    this->normal = normal;
    this->reflectivity = reflectivity;
    this->shininess = shininess;
}

Plan::~Plan () {
    delete this->initialPoint;
    delete this->normal;
    delete this->reflectivity;
}

IntersectionResult* Plan::getIntersectionResult (Line* line) {

    IntersectionResult* result = new IntersectionResult ();
    result->setObjectRegion (ObjectRegion::PLAN);
    result->setHasIntersection (true);

    Vector w = *(line->P0) - *this->initialPoint;

    double dirScalarN = scalarProduct (line->dir, this->normal);

    if (dirScalarN == 0) {
        result->setHasIntersection (false);
        return result;
    }

    double t = (-scalarProduct (w, *this->normal)) / dirScalarN;

    if (t < 0) {
        result->setHasIntersection (false);
        return result;
    }

    Vector* intersectionPoint = new Vector ();
    *intersectionPoint = *line->P0 + *line->dir * t;

    Vector distanceVector = (*intersectionPoint) - (*line->P0);
    double distanceFromP0 = distanceVector.getMagnitude ();

    result->setIntersectionPoint (intersectionPoint);
    result->setDistanceFromP0 (distanceFromP0);

    return result;

}

Color* Plan::getColorToBePainted (IntersectionResult* intersectionResult, LightsArray lightsArray, Line* line) {

    Vector resultColorRate (0, 0, 0);

    Vector v = ((*line->dir) * -1) / line->dir->getMagnitude();

    for (auto i = lightsArray.begin(); i != lightsArray.end(); i++) {
        
        Vector l = (*((*i)->getPosition()) - *intersectionResult->getIntersectionPoint()) / (*((*i)->getPosition()) - *intersectionResult->getIntersectionPoint()).getMagnitude();

        Vector r = (*this->normal) * (2 * scalarProduct (l, *this->normal)) -  l;

        double fDifusa = max (
            scalarProduct (l, *this->normal),
            0.0
        );

        double fEspeculada = pow (
            max (
                scalarProduct (r, v),
                0.0
            ),
            this->getShininess()
        );

        Vector iDifusa = (*(*i)->getIntensity()) * (*this->getReflectivity()) * fDifusa;

        Vector iEspeculada = (*(*i)->getIntensity()) * (*this->getReflectivity()) * fEspeculada;

        resultColorRate = resultColorRate + iDifusa + iEspeculada;

    }


    return new Color (
        resultColorRate[0] * 255,
        resultColorRate[1] * 255,
        resultColorRate[2] * 255,
        255
    );
}

// ADICIONAR ILUMINAÇÃO AMBIENTE!!!
