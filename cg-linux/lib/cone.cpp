#include <cmath>
#include "../include/cone.h"
#include "../include/CG.h"
#include "../include/utils.impl.h"

ObjectType Cone::getObjectType () {
    return this->type;
}

Vector* Cone::getBaseCenter () {
    return this->baseCenter;
}

void Cone::setBaseCenter (Vector* baseCenter) {
    this->baseCenter = baseCenter;
}

Vector* Cone::getTop () {
    return this->top;
}

void Cone::setTop (Vector* top) {
    this->top = top;
}

double Cone::getRadius () {
    return this->radius;
}

void Cone::setRadius (double radius) {
    this->radius = radius;
}

double Cone::getHeight () {
    return this->height;
}

void Cone::setHeight (double height) {
    this->height = height;
    this->setCos2Angle (pow (this->getHeight (), 2.0) / (pow (this->getRadius (), 2.0) + pow (this->getHeight (), 2.0)));
}

Vector* Cone::getDirection () {
    return this->direction;
}

void Cone::setDirection (Vector* direction) {
    this->direction = direction;
    this->setCos2Angle (pow (this->getHeight (), 2.0) / (pow (this->getRadius (), 2.0) + pow (this->getHeight (), 2.0)));
}

double Cone::getCos2Angle () {
    return this->cos2angle;
}

void Cone::setCos2Angle (double cos2angle) {
    this->cos2angle = cos2angle;
}

void Cone::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newBaseCenter = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialBaseCenter
        )
    );
    delete this->getBaseCenter();
    this->setBaseCenter(newBaseCenter);

    Vector* newTop = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->initialTop
        )
    );
    delete this->getTop();
    this->setTop(newTop);
    
    Vector* newDirection = new Vector(
        (*this->getTop() - *this->getBaseCenter()) / (*this->getTop() - *this->getBaseCenter()).getMagnitude()
    );
    delete this->getDirection();
    this->setDirection(newDirection);
}

IntersectionResult* Cone::getIntersectionResult (Line* line) {

    IntersectionResult* intersectionResult = new IntersectionResult ();
    intersectionResult->setHasIntersection (false);

    bool interceptsBase = false;

    double t1;

    Vector intersectionPointT1;

    double distanceP0ToT1;

    double cosin2angle = this->getCos2Angle ();

    Vector coneDirection = *this->getDirection ();

    Vector w = *this->getTop () - *line->P0;

    double drPlusDc = scalarProduct (*line->dir, coneDirection);

    if (drPlusDc != 0) {
        t1 = (scalarProduct ((*line->P0 - *this->getBaseCenter ()), coneDirection) / drPlusDc) * (-1);

        intersectionPointT1 = (*line->P0 + *line->dir * t1);

        distanceP0ToT1 = (intersectionPointT1 - *line->P0).getMagnitude();

        if ( (intersectionPointT1 - *this->getBaseCenter()).getMagnitude() <= this->getRadius() ) {
            interceptsBase = true;
        }
    }

    double a = pow (scalarProduct (*line->dir, coneDirection), 2.0) -
               scalarProduct (line->dir, line->dir) * cosin2angle;

    double b = 2 * (
        scalarProduct (w, *line->dir) * cosin2angle - scalarProduct (w, coneDirection) * scalarProduct (*line->dir, coneDirection)
    );

    double c = pow (scalarProduct (w, coneDirection), 2.0) - scalarProduct (w, w) * cosin2angle;

    if (a == 0) {
        double t2 = (-c) / (2*b);

        Vector intersectionPointT2  = *line->P0 + *line->dir * t2;

        double distanceP0ToT2 = (intersectionPointT2 - *line->P0).getMagnitude();

        // size of projection of intersection point on cylinder direction
        double CbAT2ByDir = scalarProduct ((intersectionPointT2 - *this->getBaseCenter()), coneDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT2 = coneDirection * CbAT2ByDir;

        if (CbAT2ByDir > 0 && CbAT2.getMagnitude () < this->getHeight ()) {
            
            if (interceptsBase && distanceP0ToT1 < distanceP0ToT2) {

                // VERIFYING IF T IS POSITIVE
                if (t1 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CONE_BASE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        return intersectionResult;
    }

    double discriminant = pow (b, 2.0) - 4 * a * c;

    if (discriminant == 0) {

        double t2 = (-b + sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT2  = *line->P0 + *line->dir * t2;

        double distanceP0ToT2 = (intersectionPointT2 - *line->P0).getMagnitude();

        // size of projection of intersection point on cylinder direction
        double CbAT2ByDir = scalarProduct ((intersectionPointT2 - *this->getBaseCenter()), coneDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT2 = coneDirection * CbAT2ByDir;

        if (CbAT2ByDir > 0 && CbAT2.getMagnitude() <= this->getHeight ()) {

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        return intersectionResult;

    } else if (discriminant > 0) {

        double t2 = (-b + sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT2  = *line->P0 + *line->dir * t2;

        double distanceP0ToT2 = (intersectionPointT2 - *line->P0).getMagnitude();

        double t3 = (-b - sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT3  = *line->P0 + *line->dir * t3;

        double distanceP0ToT3 = (intersectionPointT3 - *line->P0).getMagnitude();

        // size of projection of intersection point on cylinder direction
        double CbAT2ByDir = scalarProduct ((intersectionPointT2 - *this->getBaseCenter()), coneDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT2 = coneDirection * CbAT2ByDir;

        // size of projection of intersection point on cylinder direction
        double CbAT3ByDir = scalarProduct ((intersectionPointT3 - *this->getBaseCenter()), coneDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT3 = coneDirection * CbAT3ByDir;

        if (CbAT2ByDir > 0 && CbAT2.getMagnitude () <= this->getHeight () && CbAT3ByDir > 0 && CbAT3.getMagnitude () <= this->getHeight ()) {
            if (distanceP0ToT2 < distanceP0ToT3) {

                // VERIFYING IF T IS POSITIVE
                if (t2 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT2);
                intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

                return intersectionResult;
            }

            // VERIFYING IF T IS POSITIVE
            if (t3 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT3);
            intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

            return intersectionResult;
        }

        if (CbAT2ByDir > 0 && CbAT2.getMagnitude () < this->getHeight ()) {
            
            if (interceptsBase && distanceP0ToT1 < distanceP0ToT2) {

                // VERIFYING IF T IS POSITIVE
                if (t1 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CONE_BASE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        if (CbAT3ByDir > 0 && CbAT3.getMagnitude () < this->getHeight ()) {

            if (interceptsBase && distanceP0ToT1 < distanceP0ToT3) {

                // VERIFYING IF T IS POSITIVE
                if (t1 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CONE_BASE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            // VERIFYING IF T IS POSITIVE
            if (t3 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT3);
            intersectionResult->setObjectRegion (ObjectRegion::CONE_SURFACE);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

            return intersectionResult;

        }

        return intersectionResult;

    }
    
    return intersectionResult;

}

Color* Cone::getColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {

    if (intersectionResult->getObjectRegion () == ObjectRegion::CONE_BASE) {

        Sp<Vector> normal = new Vector (*this->getDirection () * (-1));

        return this->calculateColorToBePainted (
            intersectionResult,
            lightsArray,
            objectsArray,
            line,
            environmentLight,
            normal.pointer,
            this->getKd(),
            this->getKa(),
            this->getKe(),
            this->getShininess ()
        );

    }

    // Pi
    Vector intersectionPoint = *intersectionResult->getIntersectionPoint ();

    // V - Pi
    Vector vMinusPi = (*this->getTop () - intersectionPoint);

    Vector nBar = vectorProduct (
        vMinusPi,
        *this->getDirection ()
    );

    Vector normalNotUnitary = vectorProduct (nBar, vMinusPi);

    Sp<Vector> normal = new Vector (normalNotUnitary / normalNotUnitary.getMagnitude ());

    return Object::calculateColorToBePainted (
        intersectionResult,
        lightsArray,
        objectsArray,
        line,
        environmentLight,
        normal.pointer,
        this->getKd (),
        this->getKa (),
        this->getKe (),
        this->getShininess ()
    );
}

void Cone::updateDirection() {
    Vector directionNotNormal = *this->initialTop - *this->initialBaseCenter;
    Vector directionNormal = directionNotNormal / directionNotNormal.getMagnitude();
    *this->direction = directionNormal;
}

void Cone::applyScale(double sx, double sy, double sz) {
    *this->initialBaseCenter = scale((*this->initialBaseCenter), sx, sy, sz);
    *this->initialTop = scale((*this->initialTop), sx, sy, sz);
    this->updateDirection();
    this->setRadius(Vector(sx, sy, sz).getMagnitude() * this->getRadius());
}

void Cone::applyTranslate(double x, double y, double z) {
    *this->initialBaseCenter = translate((*this->initialBaseCenter), x, y, z);
    *this->initialTop = translate((*this->initialTop), x, y, z);
}

void Cone::applyRotateX(double angle) {
    *this->initialBaseCenter = rotateX((*this->initialBaseCenter), angle);
    *this->initialTop = rotateX((*this->initialTop), angle);
    this->updateDirection();
}

void Cone::applyRotateY(double angle) {
    *this->initialBaseCenter = rotateY((*this->initialBaseCenter), angle);
    *this->initialTop = rotateY((*this->initialTop), angle);
    this->updateDirection();
}

void Cone::applyRotateZ(double angle) {
    *this->initialBaseCenter = rotateZ((*this->initialBaseCenter), angle);
    *this->initialTop = rotateZ((*this->initialTop), angle);
    this->updateDirection();
}

void Cone::applyReflectXY() {
    *this->initialBaseCenter = reflectXY((*this->initialBaseCenter));
    *this->initialTop = reflectXY((*this->initialTop));
    this->updateDirection();
}

void Cone::applyReflectXZ() {
    *this->initialBaseCenter = reflectXZ((*this->initialBaseCenter));
    *this->initialTop = reflectXZ((*this->initialTop));
    this->updateDirection();
}

void Cone::applyReflectYZ() {
    *this->initialBaseCenter = reflectYZ((*this->initialBaseCenter));
    *this->initialTop = reflectYZ((*this->initialTop));
    this->updateDirection();
}

Cone::Cone () {}

Cone::Cone (Vector* baseCenter, Vector* top, double radius, Vector* reflectivity, double shininess) {
    this->setBaseCenter (baseCenter);
    this->setTop (top);
    this->setRadius (radius);
    this->setHeight (
        (*this->getTop () - *this->getBaseCenter ()).getMagnitude () 
    );
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
    this->setDirection (
        new Vector (
            (*this->getTop () - *this->getBaseCenter ())
            / (*this->getTop () - *this->getBaseCenter ()).getMagnitude()
        )
    );

    this->initialBaseCenter = new Vector(*this->getBaseCenter());
    this->initialTop = new Vector(*this->getTop());
}

Cone::Cone (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess) {
    this->setBaseCenter (baseCenter);
    this->setRadius (radius);
    this->setHeight (height);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
    *direction = *direction / (*direction).getMagnitude ();
    this->setDirection (direction);
    this->setTop (
        new Vector (
            *this->getBaseCenter () + *this->getDirection () * this->getHeight()
        )
    );

    this->initialBaseCenter = new Vector(*this->getBaseCenter());
    this->initialTop = new Vector(*this->getTop());
}

Cone::~Cone () {
    delete this->getBaseCenter ();
    delete this->getTop ();
    delete this->getDirection ();

    delete this->initialBaseCenter;
    delete this->initialTop;
}
