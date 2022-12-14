#include "../include/plan.h"
#include "../include/CG.h"

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

Plan::Plan () {}

Plan::Plan (Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess) {
    this->setInitialPoint (initialPoint);
    this->setNormal (normal);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);

    this->initialInitialPoint = new Vector(*this->getInitialPoint());
    this->initialNormal = new Vector(*this->getNormal());
}

void Plan::applyScale(double, double, double) {}
void Plan::applyTranslate(double x, double y, double z) {
    *this->initialInitialPoint = translate(*this->initialInitialPoint, x, y, z);
}
void Plan::applyRotateX(double angle) {
    *this->initialNormal = rotateX(*this->initialNormal, angle);
    *this->initialInitialPoint = rotateX(*this->initialInitialPoint, angle);
}
void Plan::applyRotateY(double angle) {
    *this->initialNormal = rotateY(*this->initialNormal, angle);
    *this->initialInitialPoint = rotateY(*this->initialInitialPoint, angle);
}
void Plan::applyRotateZ(double angle) {
    *this->initialNormal = rotateZ(*this->initialNormal, angle);
    *this->initialInitialPoint = rotateZ(*this->initialInitialPoint, angle);
}
void Plan::applyReflectXY() {
    *this->initialNormal = reflectXY(*this->initialNormal);
    *this->initialInitialPoint = reflectXY(*this->initialInitialPoint);
}
void Plan::applyReflectXZ() {
    *this->initialNormal = reflectXZ(*this->initialNormal);
    *this->initialInitialPoint = reflectXZ(*this->initialInitialPoint);
}
void Plan::applyReflectYZ() {
    *this->initialNormal = reflectYZ(*this->initialNormal);
    *this->initialInitialPoint = reflectYZ(*this->initialInitialPoint);
}

Plan::~Plan () {
    delete this->getInitialPoint();
    delete this->getNormal();

    delete this->initialInitialPoint;
    delete this->initialNormal;
}

void Plan::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newInitialPoint = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialInitialPoint
        )
    );
    delete this->getInitialPoint();
    this->setInitialPoint(
        newInitialPoint
    );

    Vector newNormalNotUnitary = lookAt->convertWorldVectorToCanvas(
        *this->initialNormal
    ) - lookAt->convertWorldVectorToCanvas(Vector(0, 0, 0));
    Vector* newNormal = new Vector(
        newNormalNotUnitary / newNormalNotUnitary.getMagnitude()
    );
    delete this->getNormal();
    this->setNormal(newNormal);
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
    Vector* environmentLight,
    bool isEnvironmentLightActive
) {

    return this->calculateColorToBePainted (
        intersectionResult,
        lightsArray,
        objectsArray,
        line,
        environmentLight,
        isEnvironmentLightActive,
        this->getNormal (),
        this->getKd (),
        this->getKa (),
        this->getKe (),
        this->getShininess ()
    );
    
}