#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "../include/utils.impl.h"
#include "../include/CG.h"
#include "../include/pixels.h"
#include "../include/image.h"
#include "../include/interface.h"

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

Vector LookAt::convertWorldVectorToCanvas(Vector worldVector) {
    Vector K = *this->getEye() - *this->getAt();
    Vector Kc = K / K.getMagnitude();

    Vector Vup = *this->getUp() - *this->getEye();
    Vector I = vectorProduct(Vup, Kc);
    Vector Ic = I / I.getMagnitude();

    Vector Jc = vectorProduct(Kc, Ic);

    double minusIcPlusEye = -scalarProduct(Ic, *this->getEye());
    double minusJcPlusEye = -scalarProduct(Jc, *this->getEye());
    double minusKcPlusEye = -scalarProduct(Kc, *this->getEye());

    Vector result = Vector(
        minusIcPlusEye + Ic[2]*worldVector[2] + Ic[1]*worldVector[1] + Ic[0]*worldVector[0],
        minusJcPlusEye + Jc[2]*worldVector[2] + Jc[1]*worldVector[1] + Jc[0]*worldVector[0],
        minusKcPlusEye + Kc[2]*worldVector[2] + Kc[1]*worldVector[1] + Kc[0]*worldVector[0]
    );

    return result;
}

void Scene::setWindowHeight(double windowHeight) {
    this->windowHeight = windowHeight;
}

void Scene::setWindowWidth(double windowWidth) {
    this->windowWidth = windowWidth;
}

void Scene::setCanvasWidth(double canvasWidth) {
    this->canvasWidth = canvasWidth;
}

void Scene::setCanvasHeight(double canvasHeight) {
    this->canvasHeight = canvasHeight;
}

void Scene::setWindowDistance(double windowDistance) {
    this->windowDistance = windowDistance;
}

void Scene::setBackgroundColor(Color* color) {
    this->backgroundColor = color;
}

void Scene::setBackgroundImage(Image* image) {
    this->backgroundImage = image;
}

void Scene::setEnvironmentLight(Vector* environmentLight) {
    this->environmentLight = environmentLight;
}

void Scene::setProjectionType(ProjectionType projectionType) {
    this->projectionType = projectionType;
}

void Scene::addLightSource(Light* lightSource) {
    this->lights.push_back(lightSource);
}

void Scene::addObject(Object* object) {
    this->objects.push_back(object);
}

void Scene::addLink(Link* link) {
    this->links.push_back(link);
}

double Scene::getWindowHeight() {
    return this->windowHeight;
}

double Scene::getWindowWidth() {
    return this->windowWidth;
}

double Scene::getCanvasWidth() {
    return this->canvasWidth;
}

double Scene::getCanvasHeight() {
    return this->canvasHeight;
}

double Scene::getWindowDistance() {
    return this->windowDistance;
}

ProjectionType Scene::getProjectionType() {
    return this->projectionType;
}

Color* Scene::getBackgroundColor() {
    return this->backgroundColor;
}

Image* Scene::getBackgroundImage() {
    return this->backgroundImage;
}

Vector* Scene::getEnvironmentLight() {
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

    for(Object* object : this->getObjects()) {
        object->applyWorldToCanvasConversion(this->eyeLookAt);
    }

    for(Light* light : this->getLights()) {
        light->applyWorldToCanvasConversion(this->eyeLookAt);
    }
}

int raycastThread(void* threadData) {
    RaycastData* data = (RaycastData*) threadData;
    Scene* scene = data->scene;

    const double nLin = scene->getCanvasHeight();
    const double nCol = scene->getCanvasWidth();

    const double hJanela = scene->getWindowHeight();
    const double wJanela = scene->getWindowWidth();

    const double dx = wJanela / nCol;
    const double dy = hJanela / nLin;

    Image* sceneBackgroundImage = scene->getBackgroundImage();

    int numberOfObjects = scene->getObjects().size();

    const double z = -scene->getWindowDistance();

    for(int l = data->fromLin; l < data->toLin; l++) {
        const double y = hJanela / 2.0 - dy / 2.0 - l * dy;

        for(int c = data->fromCol; c < data->toCol; c++) {
            const double x = -wJanela / 2.0 + dx / 2.0 + c * dx;

            bool isProjectionPerspective = scene->getProjectionType() == ProjectionType::PERSPECTIVE;
            Vector* P0 = new Vector(
                isProjectionPerspective ? Vector(0, 0, 0) : Vector(x, y, 0)
            );
            Vector* direction = new Vector(
                isProjectionPerspective ? Vector(x, y, z) : Vector(0, 0, -1)
            );
            Sp<Line> line = new Line(P0, direction);

            int nearestObjectIndex = 0;
            Sp<IntersectionResult> nearestResult = new IntersectionResult(false, nullptr, 0, ObjectRegion::UNKNOWN);

            for(int i = 0; i < numberOfObjects; i++) {

                Sp<IntersectionResult> result = scene->getObjects()[i]->getIntersectionResult(line.pointer);
                
                if(result->getHasIntersection() &&
            (!nearestResult->getHasIntersection() || result->getDistanceFromP0() < nearestResult->getDistanceFromP0())) {
                    delete nearestResult.pointer;
                    nearestResult.pointer = result.pointer;
                    result.pointer = nullptr;

                    nearestObjectIndex = i;
                }

            }

            if(nearestResult->getHasIntersection()) {
                Sp<Color> colorToPaint = scene->getObjects()[nearestObjectIndex]->getColorToBePainted(
                    nearestResult.pointer,
                    scene->getLights(),
                    scene->getObjects(),
                    line.pointer,
                    scene->getEnvironmentLight()
                );

                scene->buffer[c][l][0] = colorToPaint->r;
                scene->buffer[c][l][1] = colorToPaint->g;
                scene->buffer[c][l][2] = colorToPaint->b;
            } else if(sceneBackgroundImage != nullptr) {
                // if there is no intersection, verify if there is an background image and paint
                // with the color of equivalent pixel in the image

                double x =(double(c) * double(sceneBackgroundImage->getImageWidth())) / scene->getCanvasWidth();
                double y =(double(l) * double(sceneBackgroundImage->getImageHeight())) / scene->getCanvasHeight();

                Pixel pixelToPaint = sceneBackgroundImage->getPixel(x, y);

                // setPaintColor(scene->renderer, pixelToPaint.r, pixelToPaint.g, pixelToPaint.b, pixelToPaint.a);
                // paintPixel(scene->renderer, c, l);

                scene->buffer[c][l][0] = pixelToPaint.r;
                scene->buffer[c][l][1] = pixelToPaint.g;
                scene->buffer[c][l][2] = pixelToPaint.b;
            }

        }
    }

    return 0;
}

void Scene::raycast() {

    const double nLin = this->getCanvasHeight();
    const double nCol = this->getCanvasWidth();

    RaycastData dataT1;
    RaycastData dataT2;
    RaycastData dataT3;
    RaycastData dataT4;
    
    dataT1.scene = this;
    dataT2.scene = this;
    dataT3.scene = this;
    dataT4.scene = this;

    dataT1.fromLin = 0;
    dataT1.toLin = nLin / 2;
    dataT1.fromCol = 0;
    dataT1.toCol = nCol / 2;

    dataT2.fromLin = 0;
    dataT2.toLin = nLin / 2;
    dataT2.fromCol = nCol / 2;
    dataT2.toCol = nCol;

    dataT3.fromLin = nLin / 2;
    dataT3.toLin = nLin;
    dataT3.fromCol = 0;
    dataT3.toCol = nCol / 2;

    dataT4.fromLin = nLin / 2;
    dataT4.toLin = nLin;
    dataT4.fromCol = nCol / 2;
    dataT4.toCol = nCol;

    SDL_Thread* t1 = SDL_CreateThread(raycastThread, "t1", &dataT1);
    SDL_Thread* t2 = SDL_CreateThread(raycastThread, "t2", &dataT2);
    SDL_Thread* t3 = SDL_CreateThread(raycastThread, "t3", &dataT3);
    SDL_Thread* t4 = SDL_CreateThread(raycastThread, "t4", &dataT4);

    int status1;
    int status2;
    int status3;
    int status4;
    SDL_WaitThread(t1, &status1);
    SDL_WaitThread(t2, &status2);
    SDL_WaitThread(t3, &status3);
    SDL_WaitThread(t4, &status4);

    for (int l = 0; l < nLin; l++) {
        for (int c = 0; c < nCol; c++) {
            setPaintColor(this->renderer, this->buffer[c][l][0], this->buffer[c][l][1], this->buffer[c][l][2], 255);
            paintPixel(this->renderer, c, l);
        }
    }

}

void Scene::update() {
    _update(this->renderer);
}

void Scene::render() {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    initializeSDLAndWindow(&window, &renderer, this->getCanvasWidth(), this->getCanvasHeight());
    // SDL_RenderSetScale(renderer, 4, 4);

    if(this->backgroundColor == nullptr) {
        std::cout << "backgroundColor is null" << std::endl;

        setWindowBackground(
            renderer,
            0, 0, 0, 255
        );
    } else {
        setWindowBackground(
            renderer,
            this->backgroundColor->r,
            this->backgroundColor->g,
            this->backgroundColor->b,
            this->backgroundColor->a
        );
    }

    this->window = window;
    this->renderer = renderer;

    this->raycast();

    this->update();
    this->interface->scene = this;
    this->interface->listenEvents();
}

LightsArray Scene::getLights() {
    return this->lights;
}

ObjectsArray Scene::getObjects() {
    return this->objects;
}

LinksArray Scene::getLinks() {
    return this->links;
}

Scene::Scene() {}

Scene::Scene(
    double windowHeight,
    double windowWidth,
    int canvasHeight,
    int canvasWidth,
    double windowDistance,
    Color* color
) {
    this->setWindowHeight(windowHeight);
    this->setWindowWidth(windowWidth);
    this->setCanvasHeight(canvasHeight);
    this->setCanvasWidth(canvasWidth);
    this->setWindowDistance(windowDistance);
    this->lookAt(
        new Vector(0, 0, 0),
        new Vector(0, 0, -1),
        new Vector(0, 1, 0)
    );
    this->interface = new Interface();
    
    if(color == nullptr) {
        this->setBackgroundColor(new Color(0, 0, 0, 255));
    } else {
        this->setBackgroundColor(color);
    }
}

Scene::~Scene() {
    delete this->getBackgroundImage();
    delete this->getEnvironmentLight();
    delete this->getBackgroundColor();
    delete this->eyeLookAt;
    delete this->interface;
    
    for(auto i = this->objects.begin(); i != this->objects.end(); i++) {
        delete(*i);
    }

    for(auto i = this->lights.begin(); i != this->lights.end(); i++) {
        delete(*i);
    }

    for(auto i = this->links.begin(); i != this->links.end(); i++) {
        delete(*i);
    }
}

Color::Color(int r, int g, int b, int a) {
    this->r = r > 255 ? 255 : r; // min(r, 255)
    this->g = g > 255 ? 255 : g; // min(g, 255);
    this->b = b > 255 ? 255 : b; // min(b, 255);
    this->a = a > 255 ? 255 : a; // min(a, 255);
}

void Light::setActive(bool active) {
    this->active = active;
}

bool Light::isActive() {
    return this->active;
}

void Light::setIntensity(Vector* intensity) {
    this->intensity = intensity;
}

Vector* Light::getIntensity() {
    return this->intensity;
}

Light::Light() {}

Light::Light(Vector* intensity) {
    this->setIntensity(intensity);
}

Light::~Light() {
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
    return(*this->getPosition() - point).getMagnitude();
}

void PointLight::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newPosition = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialPosition
        )
    );
    delete this->getPosition();
    this->setPosition(newPosition);
}

LightType PointLight::getLightType() {
    return this->type;
}

IlluminationInfo PointLight::getIlluminationInfo(Vector intersectionPoint) {
    Vector l =(*this->getPosition() - intersectionPoint) /(*this->getPosition()
        - intersectionPoint).getMagnitude();

    Vector intensity = *this->getIntensity();

    return IlluminationInfo(
        l, intensity
    );
}

PointLight::PointLight() {}

PointLight::PointLight(Vector* intensity, Vector* position) : Light::Light(intensity) {
    this->setPosition(position);
    this->initialPosition = new Vector(*position);
}

PointLight::~PointLight() {
    delete this->getPosition();
    delete this->initialPosition;
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

LightType DirectionalLight::getLightType() {
    return this->type;
}

void DirectionalLight::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector newDirectionNotNormal = lookAt->convertWorldVectorToCanvas(
        *this->initialDirection
    ) - lookAt->convertWorldVectorToCanvas(Vector(0, 0, 0));
    Vector* newDirection = new Vector(
        newDirectionNotNormal / newDirectionNotNormal.getMagnitude()
    );
    delete this->getDirection();
    this->setDirection(newDirection);
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
    this->initialDirection = new Vector(*direction);
}

DirectionalLight::~DirectionalLight() {
    delete this->getDirection();
    delete this->initialDirection;
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

LightType SpotLight::getLightType() {
    return this->type;
}

double SpotLight::getDistanceFromPoint(Vector point) {
    return(*this->getPosition() - point).getMagnitude();
}

void SpotLight::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newDirection = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialDirection
        ) - lookAt->convertWorldVectorToCanvas(Vector(0, 0, 0))
    );
    delete this->getDirection();
    this->setDirection(newDirection);

    Vector* newPosition = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialPosition
        )
    );
    delete this->getPosition();
    this->setPosition(newPosition);
}

IlluminationInfo SpotLight::getIlluminationInfo(Vector intersectionPoint) {
    Vector l =(*this->getPosition() - intersectionPoint) /(*this->getPosition()
        - intersectionPoint).getMagnitude();
    double clds = scalarProduct(l,(*this->getDirection() * -1));

    Vector spotIntensity = *this->getIntensity();

    Vector intensity;

    if(clds < cos(angle)) {
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

    this->initialDirection = new Vector(*direction);
    this->initialPosition = new Vector(*position);
}

SpotLight::~SpotLight() {
    delete this->getDirection();
    delete this->getPosition();
    delete this->initialDirection;
    delete this->initialPosition;
}

Line::Line(Vector* P0, Vector* dir) {
    this->P0 = P0;
    this->dir = dir;
}

Line::~Line() {
    delete this->P0;
    delete this->dir;
}

void IntersectionResult::setHasIntersection(bool hasIntersection) {
    this->hasIntersection = hasIntersection;
}

bool IntersectionResult::getHasIntersection() {
    return this->hasIntersection;
}

void IntersectionResult::setIntersectionPoint(Vector* intersectionPoint) {
    this->intersectionPoint = intersectionPoint;
}

Vector* IntersectionResult::getIntersectionPoint() {
    return this->intersectionPoint;
}

void IntersectionResult::setDistanceFromP0(double distanceFromP0) {
    this->distanceFromP0 = distanceFromP0;
}

double IntersectionResult::getDistanceFromP0() {
    return this->distanceFromP0;
}

void IntersectionResult::setObjectRegion(ObjectRegion region) {
    this->region = region;
}

ObjectRegion IntersectionResult::getObjectRegion() {
    return this->region;
}

IntersectionResult IntersectionResult::operator =(const IntersectionResult& result) {
    this->setDistanceFromP0(result.distanceFromP0);
    this->setHasIntersection(result.hasIntersection);
    
    if(this->getIntersectionPoint() != nullptr && result.intersectionPoint != nullptr) {
        *this->getIntersectionPoint() = *result.intersectionPoint;
    }

    return *this;
}

IntersectionResult::IntersectionResult() {}

IntersectionResult::IntersectionResult(bool hasIntersection, Vector* intersectionPoint, double distanceFromP0, ObjectRegion region) {
    this->setHasIntersection(hasIntersection);
    this->setIntersectionPoint(intersectionPoint);
    this->setDistanceFromP0(distanceFromP0);
    this->setObjectRegion(region);
}

IntersectionResult::IntersectionResult(const IntersectionResult& result) {
    this->distanceFromP0 = result.distanceFromP0;
    this->hasIntersection = result.hasIntersection;
    
    if(result.intersectionPoint != nullptr) {
        this->intersectionPoint = new Vector(*result.intersectionPoint);
    }
}

IntersectionResult::~IntersectionResult() {
    delete this->getIntersectionPoint();
}

void Object::setReflectivity(Vector* reflectivity) {
    delete this->getKa();
    delete this->getKd();
    delete this->getKe();

    this->setKa(reflectivity);
    this->setKd(new Vector(*reflectivity));
    this->setKe(new Vector(*reflectivity));
}

void Object::setShininess(double shininess) {
    this->shininess = shininess;
}

double Object::getShininess() {
    return this->shininess;
}

bool Object::isInside(Vector*) {
    return false;
}

void Object::setKa(Vector* ka) {
    delete this->getKa();
    this->ka = ka;
}

void Object::setKd(Vector* kd) {
    delete this->getKd();
    this->kd = kd;
}

void Object::setKe(Vector* ke) {
    delete this->getKe();
    this->ke = ke;
}

Vector* Object::getKa() {
    return this->ka;
}

Vector* Object::getKd() {
    return this->kd;
}

Vector* Object::getKe() {
    return this->ke;
}

Object::Object() {}

Object::Object(Vector* reflectivity) {
    this->setKa(reflectivity);
    this->setKd(new Vector(*reflectivity));
    this->setKe(new Vector(*reflectivity));
}

Object::~Object() {
    delete this->getKd();
    delete this->getKa();
    delete this->getKe();
}

Color* Object::calculateColorToBePainted(
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight,
    Vector* normal,
    Vector* kd,
    Vector* ka,
    Vector* ke,
    double shininess
) {

    Vector resultColorRate = this->calculateResultColorRate(
        line,
        intersectionResult,
        lightsArray,
        objectsArray,
        normal,
        kd,
        ke,
        shininess
    );

    if(environmentLight != nullptr) {
        resultColorRate = resultColorRate +((*environmentLight) *(*ka));
    }

    return new Color(
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
    Vector* kd,
    Vector* ke,
    double shininess
) {

    Vector resultColorRate(0, 0, 0);

    Vector v =((*line->dir) * -1) / line->dir->getMagnitude();

    Vector* intersectionPoint = intersectionResult->getIntersectionPoint();

    // verify if the lights intercepts any other object

    for(auto i = lightsArray.begin(); i != lightsArray.end(); i++) {
        if ((*i)->isActive()) {
            IlluminationInfo illuminationInfo =(*i)->getIlluminationInfo(*intersectionPoint);
            Vector l = illuminationInfo.l;
            Vector intensity = illuminationInfo.intensity;
            
            bool hasIntersectionWithOtherObjects = this->hasIntersectionWithOtherObjects(
                objectsArray, intersectionPoint, new Vector(l), *i
            );

            // calculate the color to be painted
            if(!hasIntersectionWithOtherObjects) {    
                Vector r =(*normal) *(2 * scalarProduct(l, *normal)) -  l;

                double fDifusa = max(
                    scalarProduct(l, *normal),
                    0.0
                );

                double fEspeculada = pow(
                    max(
                        scalarProduct(r, v),
                        0.0
                    ),
                    shininess
                );

                Vector iDifusa = intensity *(*kd) * fDifusa;

                Vector iEspeculada = intensity *(*ke) * fEspeculada;

                resultColorRate = resultColorRate + iDifusa + iEspeculada;
            }
        }
    }

    return resultColorRate;
}

bool Object::hasIntersectionWithOtherObjects(ObjectsArray objectsArray, Vector* intersectionPoint, Vector* l, Light* light) {

    Sp<Line> verifyShadowLine = new Line(
        new Vector(
        (*intersectionPoint)
        ),
        l
    );

    bool hasIntersectionWithOtherObjects = false;

    for(auto j = objectsArray.begin();(j != objectsArray.end() && !hasIntersectionWithOtherObjects); j++) {
        
        if((*j) != this) {
            Sp<IntersectionResult> intersectionShadow =(*j)->getIntersectionResult(verifyShadowLine.pointer);

            hasIntersectionWithOtherObjects =
                intersectionShadow->getHasIntersection() &&
            (intersectionShadow->getDistanceFromP0() <(light->getDistanceFromPoint(*intersectionPoint)));
        }

    }

    return hasIntersectionWithOtherObjects;
}

void Link::addObject(Object* object) {
    this->objects.push_back(object);
}

void Link::applyTranslate(double x, double y, double z, LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyTranslate(x, y, z);
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyReflectXY(LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyReflectXY();
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyReflectXZ(LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyReflectXZ();
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyReflectYZ(LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyReflectYZ();
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyRotateX(double angle, LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyRotateX(angle);
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyRotateY(double angle, LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyRotateY(angle);
        object->applyWorldToCanvasConversion(lookAt);
    }
}

void Link::applyRotateZ(double angle, LookAt* lookAt) {
    for (Object* object : this->objects) {
        object->applyRotateZ(angle);
        object->applyWorldToCanvasConversion(lookAt);
    }
}

Link::Link(string name) {
    this->name = name;
}
