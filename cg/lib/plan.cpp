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
}

Plan::~Plan () {
    delete this->getInitialPoint();
    delete this->getNormal();
}

void Plan::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newInitialPoint = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->getInitialPoint()
        )
    );
    delete this->getInitialPoint();
    this->setInitialPoint(
        newInitialPoint
    );

    Vector newNormalNotUnitary = lookAt->convertWorldVectorToCanvas(
        *this->getNormal()
    );
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
    Vector* environmentLight
) {

    return this->calculateColorToBePainted (
        intersectionResult,
        lightsArray,
        objectsArray,
        line,
        environmentLight,
        this->getNormal (),
        this->getReflectivity (),
        this->getShininess ()
    );
    
}