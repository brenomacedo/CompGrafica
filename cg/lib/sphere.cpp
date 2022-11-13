#include "../include/sphere.h"
#include "../include/utils.impl.h"
#include "../include/CG.h"

ObjectType Sphere::getObjectType () {
    return this->type;
}

void Sphere::setRadius (double radius) {
    this->radius = radius;
}

double Sphere::getRadius () {
    return this->radius;
}

void Sphere::setCenter (Vector* center) {
    this->center = center;
}

Vector* Sphere::getCenter () {
    return this->center;
}

Sphere::Sphere () {}

Sphere::Sphere (double radius, Vector* reflectivity, Vector* center, double shininess) {
    this->setRadius (radius);
    this->setReflectivity (reflectivity);
    this->setCenter (center);
    this->setShininess (shininess);
}

Sphere::~Sphere () {
    delete this->getCenter();
}

void Sphere::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newCenter = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->getCenter()
        )
    );
    delete this->getCenter();
    this->setCenter(newCenter);
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
        double t2 = (-b - sqrt(discriminant)) / (2 * a);

        // verify if dir is forward (to remove, just remove this condition)
        if (t1 < 0 && t2 < 0) {
            result->setHasIntersection (false);
            return result;
        }

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

    Vector* intersectionPoint = intersectionResult->getIntersectionPoint();
    Sp<Vector> normal = new Vector ((*intersectionPoint - *this->getCenter()) / this->getRadius());

    return this->calculateColorToBePainted (
        intersectionResult,
        lightsArray,
        objectsArray,
        line,
        environmentLight,
        normal.pointer,
        this->getReflectivity(),
        this->getShininess()
    );

}