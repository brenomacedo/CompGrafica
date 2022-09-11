#include <iostream>
#include <cmath>
#include <vector>
#include "../include/utils.impl.h"
#include "../include/CG.h"
#include "../include/pixels.h"
#include "../include/image.h"

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
    delete this->getReflectivity();
    delete this->getCenter();
}

IntersectionResult* Sphere::getIntersectionResult (Line* line) {

    Vector w = *(line->P0) - *(this->getCenter());

    double a = scalarProduct (line->dir, line->dir);
    double b = 2 * scalarProduct (w, *(line->dir));
    double c = scalarProduct (w, w) - pow (this->getRadius(), 2.0);

    double discriminant = (pow (b, 2.0) - 4 * a * c);

    double t;
    IntersectionResult* result = new IntersectionResult ();
    result->setObjectRegion (ObjectRegion::SPHERE_SURFACE);

    if (discriminant == 0) {
        result->setHasIntersection (true);
        t = (-b + sqrt(discriminant)) / (2 * a);

        // verify if dir is forward (to remove, just remove this condition)
        if (t < 0) {
            result->setHasIntersection (false);
            return result;
        }

        Vector* intersectionPoint = new Vector();
        *intersectionPoint = (*line->P0) + (*line->dir) * t;
        result->setIntersectionPoint (intersectionPoint);

        Vector distanceFromP0Vector = (*line->P0) - (*intersectionPoint);
        double distanceBetweenP0AndIntersection = distanceFromP0Vector.getMagnitude();
        result->setDistanceFromP0 (distanceBetweenP0AndIntersection);

    } else if (discriminant > 0) {
        result->setHasIntersection (true);

        double t1 = (-b + sqrt(discriminant)) / (2 * a);

        // verify if dir is forward (to remove, just remove this condition)
        if (t1 < 0) {
            result->setHasIntersection (false);
            return result;
        }

        double t2 = (-b - sqrt(discriminant)) / (2 * a);

        Vector intersectionPoint1 = (*line->P0) + (*line->dir) * t1;
        Vector intersectionPoint2 = (*line->P0) + (*line->dir) * t2;

        double distanceP0toT1 = (intersectionPoint1 - *line->P0).getMagnitude ();
        double distanceP0toT2 = (intersectionPoint2 - *line->P0).getMagnitude ();

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

Color* Sphere::getColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {
    
    Vector resultColorRate (0, 0, 0);

    Vector* intersectionPoint = intersectionResult->getIntersectionPoint();

    Vector n = (*intersectionPoint - *this->getCenter()) / this->getRadius();

    Vector v = ((*line->dir) * (-1)) / line->dir->getMagnitude();

    for (auto i = lightsArray.begin(); i != lightsArray.end(); i++) {

        Vector sourceMinusIntersection = *((*i)->getPosition()) - *intersectionPoint;

        double sourceMinusIntersectionMagnitude = sourceMinusIntersection.getMagnitude();

        Vector l = sourceMinusIntersection / sourceMinusIntersectionMagnitude;
        
        // verify if the lights intercepts any other object
        Sp<Line> verifyShadowLine = new Line (
            new Vector (
                (*intersectionPoint)
            ),
            new Vector (l)
        );

        bool hasIntersectionWithOtherObjects = false;

        for (auto j = objectsArray.begin(); (j != objectsArray.end() && !hasIntersectionWithOtherObjects); j++) {
            
            if ((*j) != this) {
                Sp<IntersectionResult> intersectionShadow = (*j)->getIntersectionResult (verifyShadowLine.pointer);

                hasIntersectionWithOtherObjects =
                    intersectionShadow->getHasIntersection() &&
                    (intersectionShadow->getDistanceFromP0() < intersectionResult->getDistanceFromP0());
            }

        }

        // calculate the color to be painted
        if (!hasIntersectionWithOtherObjects) {
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
    }

    if (environmentLight != nullptr) {
        resultColorRate = resultColorRate + ((*environmentLight) * (*this->getReflectivity()));
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
    this->setInitialPoint (initialPoint);
    this->setNormal (normal);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
}

Plan::~Plan () {
    delete this->getInitialPoint();
    delete this->getNormal();
    delete this->getReflectivity();
}

IntersectionResult* Plan::getIntersectionResult (Line* line) {

    IntersectionResult* result = new IntersectionResult ();
    result->setObjectRegion (ObjectRegion::PLAN);
    result->setHasIntersection (true);

    Vector w = *(line->P0) - *this->getInitialPoint();

    double dirScalarN = scalarProduct (line->dir, this->getNormal());

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

Color* Plan::getColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
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
            
            if ((*j) != this) {
                Sp<IntersectionResult> intersectionShadow = (*j)->getIntersectionResult (verifyShadowLine.pointer);

                hasIntersectionWithOtherObjects =
                    intersectionShadow->getHasIntersection() &&
                    (intersectionShadow->getDistanceFromP0() < intersectionResult->getDistanceFromP0());
            }

        }

        // calculate the color to be painted
        if (!hasIntersectionWithOtherObjects) {    
            Vector r = (*this->getNormal()) * (2 * scalarProduct (l, *this->getNormal())) -  l;

            double fDifusa = max (
                scalarProduct (l, *this->getNormal()),
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


    }

    if (environmentLight != nullptr) {
        resultColorRate = resultColorRate + ((*environmentLight) * (*this->getReflectivity()));
    }

    return new Color (
        resultColorRate[0] * 255,
        resultColorRate[1] * 255,
        resultColorRate[2] * 255,
        255
    );
}

ObjectType Cylinder::getObjectType () {
    return this->type;
}

void Cylinder::setBaseCenter (Vector* baseCenter) {
    this->baseCenter = baseCenter;
}

Vector* Cylinder::getBaseCenter () {
    return this->baseCenter;
}

void Cylinder::setTopCenter (Vector* topCenter) {
    this->topCenter = topCenter;
}

Vector* Cylinder::getTopCenter () {
    return this->topCenter;
}

void Cylinder::setRadius (double radius) {
    this->radius = radius;
}

double Cylinder::getRadius () {
    return this->radius;
}

void Cylinder::setReflectivity (Vector* reflectivity) {
    this->reflectivity = reflectivity;
}

Vector* Cylinder::getReflectivity () {
    return this->reflectivity;
}

void Cylinder::setShininess (double shininess) {
    this->shininess = shininess;
}

double Cylinder::getShininess () {
    return this->shininess;
}

void Cylinder::setHeight (double height) {
    this->height = height;
}

double Cylinder::getHeight () {
    return this->height;
}

IntersectionResult* Cylinder::getIntersectionResult (Line* line) {

    IntersectionResult* intersectionResult = new IntersectionResult ();
    intersectionResult->setHasIntersection (false);

    bool interceptsBase = false;
    bool interceptsTop = false;

    Vector dirT (
        (*line->dir)[0],
        (*line->dir)[1],
        (*line->dir)[2]
    );

    Vector cylinderDirection = (*this->getTopCenter() - *this->getBaseCenter()) /
                               (*this->getTopCenter() - *this->getBaseCenter()).getMagnitude();

    Vector cylinderDirectionT (
        cylinderDirection[0],
        cylinderDirection[1],
        cylinderDirection[2]
    );

    Vector w = *line->P0 - *this->getBaseCenter();

    Vector wT (
        w[0],
        w[1],
        w[2]
    );

    Vector Identity[3] = {
        Vector (
            1, 0, 0            
        ),
        Vector (
            0, 1, 0
        ),
        Vector (
            0, 0, 1
        )
    };

    // M = Identity - cylinderDirection * cylinderDirectionT
    Vector M[3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            M[i][j] = Identity[i][j] - cylinderDirection[i] * cylinderDirectionT[j];

        }
    }

    // ==================== verify intersection with the cylinder cover =======================

    // dr * dc
    double drPlusDc = scalarProduct (*line->dir, cylinderDirection);
    double t1;
    double t2;

    Vector intersectionPointT1;
    Vector intersectionPointT2;

    double distanceP0ToT1;
    double distanceP0ToT2;

    if (drPlusDc != 0) {

        // base plan
        t1 = (scalarProduct ((*line->P0 - *this->getBaseCenter()), cylinderDirection) / drPlusDc) * (-1);
        
        // top plan
        t2 = (scalarProduct ((*line->P0 - *this->getTopCenter()), cylinderDirection) / drPlusDc) * (-1);

        intersectionPointT1 = (*line->P0 + *line->dir * t1);
        intersectionPointT2 = (*line->P0 + *line->dir * t2);

        distanceP0ToT1 = (intersectionPointT1 - *this->getBaseCenter()).getMagnitude();
        distanceP0ToT2 = (intersectionPointT2 - *this->getTopCenter()).getMagnitude();

        if ( (intersectionPointT1 - *this->getBaseCenter()).getMagnitude() <= this->getRadius() ) {
            interceptsBase = true;
        }

        if ( (intersectionPointT2 - *this->getTopCenter()).getMagnitude() <= this->getRadius() ) {
            interceptsTop = true;
        }
        
    }

    if (interceptsBase && interceptsTop) {

        intersectionResult->setHasIntersection(true);
        intersectionResult->setObjectRegion(ObjectRegion::CYLINDER_COVER);
        
        if (distanceP0ToT1 < distanceP0ToT2) {
            intersectionResult->setDistanceFromP0 (distanceP0ToT1);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));
        } else {
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));
        }

        return intersectionResult;

    }

    if (interceptsBase) {
        intersectionResult->setDistanceFromP0 (distanceP0ToT1);
        intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));
    }

    if (interceptsTop) {
        intersectionResult->setDistanceFromP0 (distanceP0ToT2);
        intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));
    }

    // // ========================================================================================

    
    // // ==================== verify intersection with the cylinder surface =====================

    // dr * M
    Vector drTPlusM;

    for (int i = 0; i < 3; i++) {
        drTPlusM[i] = (*line->dir)[0] * M[0][i] + (*line->dir)[1] * M[1][i] + (*line->dir)[2] * M[2][i];
    }

    // (dr * M)[1x3] * dir[3x1]
    double a = drTPlusM[0] * (*line->dir)[0] + drTPlusM[1] * (*line->dir)[1] + drTPlusM[2] * (*line->dir)[2];

    // wT * M
    Vector wTPlusM;

    for (int i = 0; i < 3; i++) {
        wTPlusM[i] = wT[0] * M[0][i] + wT[1] * M[1][i] + wT[2] * M[2][i];
    }

    double b = 2 * (wTPlusM[0] * (*line->dir)[0] + wTPlusM[1] * (*line->dir)[1] + wTPlusM[2] * (*line->dir)[2]);

    double c = (wTPlusM[0] * w[0] + wTPlusM[1] * w[1] + wTPlusM[2] * w[2]) - pow (this->getRadius(), 2.0);


    double discriminant = (pow (b, 2.0) - 4 * a * c);

    // if (discriminant > 0) {
    //     intersectionResult->setHasIntersection (true);
    //     return intersectionResult;
    // }
    // return intersectionResult;

    if (discriminant == 0) {

        double t3 = (-b + sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT3  = *line->P0 + *line->dir * t3;

        // size of projection of intersection point on cylinder direction
        double CbAT3byDir = scalarProduct ((intersectionPointT3 - *this->getBaseCenter()), cylinderDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT3 = cylinderDirection * CbAT3byDir;

        double distanceP0ToT3 = (intersectionPointT3 - *line->P0).getMagnitude();

        if (CbAT3byDir > 0 && CbAT3.getMagnitude() <= this->getHeight ()) {

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT3);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

            return intersectionResult;

        }

        return intersectionResult;

    } else if (discriminant > 0) {

        double t3 = (-b + sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT3  = *line->P0 + *line->dir * t3;

        double distanceP0ToT3 = (intersectionPointT3 - *line->P0).getMagnitude();

        double t4 = (-b - sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT4  = *line->P0 + *line->dir * t4;

        double distanceP0ToT4 = (intersectionPointT4 - *line->P0).getMagnitude();

        // size of projection of intersection point on cylinder direction
        double CbAT3ByDir = scalarProduct ((intersectionPointT3 - *this->getBaseCenter()), cylinderDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT3 = cylinderDirection * CbAT3ByDir;

        // size of projection of intersection point on cylinder direction
        double CbAT4ByDir = scalarProduct ((intersectionPointT4 - *this->getBaseCenter()), cylinderDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT4 = cylinderDirection * CbAT4ByDir;

        if (CbAT3ByDir > 0 && CbAT3.getMagnitude () < this->getHeight () && CbAT4ByDir > 0 && CbAT4.getMagnitude () < this->getHeight ()) {
            if (distanceP0ToT3 < distanceP0ToT4) {
                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT4);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT4));

            return intersectionResult;
            
        }

        if (CbAT3ByDir > 0 && CbAT3.getMagnitude () < this->getHeight ()) {
            
            if (interceptsBase) {

                if (distanceP0ToT3 < distanceP0ToT1) {

                    intersectionResult->setHasIntersection (true);
                    intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                    intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                    intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                    return intersectionResult;

                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_COVER);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            if (distanceP0ToT3 < distanceP0ToT2) {

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                return intersectionResult;

            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        if (CbAT4ByDir > 0 && CbAT4.getMagnitude () < this->getHeight ()) {

            if (interceptsBase) {

                if (distanceP0ToT4 < distanceP0ToT1) {

                    intersectionResult->setHasIntersection (true);
                    intersectionResult->setDistanceFromP0 (distanceP0ToT4);
                    intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                    intersectionResult->setIntersectionPoint (new Vector (intersectionPointT4));

                    return intersectionResult;

                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_COVER);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            if (distanceP0ToT4 < distanceP0ToT2) {

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT4);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT4));

                return intersectionResult;

            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        return intersectionResult;
        

    }

    return intersectionResult;
    
    // ================================================================

}

Color* Cylinder::getColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {
    return new Color (255, 0, 0, 255); // TODO: make cylinder getColorToBePainted
};

Cylinder::Cylinder () {}

Cylinder::Cylinder (Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess) {
    this->setBaseCenter (baseCenter);
    this->setTopCenter (topCenter);
    this->setRadius (radius);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
    this->setHeight ((*this->getTopCenter() - *this->getBaseCenter()).getMagnitude());
}

Cylinder::~Cylinder () {
    delete this->getBaseCenter ();
    delete this->getTopCenter ();
    delete this->getReflectivity ();
}