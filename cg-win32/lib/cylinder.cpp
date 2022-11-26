#include <cmath>
#include "../include/cylinder.h"
#include "../include/CG.h"
#include "../include/utils.impl.h"

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

void Cylinder::setHeight (double height) {
    this->height = height;
}

double Cylinder::getHeight () {
    return this->height;
}

void Cylinder::setDirection (Vector* direction) {
    this->direction = direction;
}

Vector* Cylinder::getDirection () {
    return this->direction;
}

void Cylinder::applyWorldToCanvasConversion(LookAt* lookAt) {
    Vector* newBaseCenter = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->getBaseCenter()
        )
    );
    delete this->getBaseCenter();
    this->setBaseCenter(newBaseCenter);

    Vector* newTopCenter = new Vector(
        lookAt->convertWorldVectorToCanvas(
            *this->getTopCenter()
        )
    );
    delete this->getTopCenter();
    this->setTopCenter(newTopCenter);

    Vector* newDirection = new Vector(
        (*this->getTopCenter() - *this->getBaseCenter()) / (*this->getTopCenter() - *this->getBaseCenter()).getMagnitude()
    );
    delete this->getDirection();
    this->setDirection(newDirection);
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

    Vector cylinderDirection = *this->getDirection ();

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

        distanceP0ToT1 = (intersectionPointT1 - *line->P0).getMagnitude();
        distanceP0ToT2 = (intersectionPointT2 - *line->P0).getMagnitude();

        if ( (intersectionPointT1 - *this->getBaseCenter()).getMagnitude() <= this->getRadius() ) {
            interceptsBase = true;
        }

        if ( (intersectionPointT2 - *this->getTopCenter()).getMagnitude() <= this->getRadius() ) {
            interceptsTop = true;
        }
        
    }

    if (interceptsBase && interceptsTop) {

        intersectionResult->setHasIntersection(true);
        
        if (distanceP0ToT1 < distanceP0ToT2) {

            // VERIFYING IF T IS POSITIVE
            if (t1 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setObjectRegion(ObjectRegion::CYLINDER_BASE);
            intersectionResult->setDistanceFromP0 (distanceP0ToT1);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

        } else {

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setObjectRegion(ObjectRegion::CYLINDER_TOP);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

        }

        return intersectionResult;

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

    if (discriminant == 0) {

        double t3 = (-b + sqrt (discriminant)) / (2 * a);

        Vector intersectionPointT3  = *line->P0 + *line->dir * t3;

        // size of projection of intersection point on cylinder direction
        double CbAT3byDir = scalarProduct ((intersectionPointT3 - *this->getBaseCenter()), cylinderDirection);
        // projection of intersection point on cylinder direction (CbA)
        Vector CbAT3 = cylinderDirection * CbAT3byDir;

        double distanceP0ToT3 = (intersectionPointT3 - *line->P0).getMagnitude();

        if (CbAT3byDir > 0 && CbAT3.getMagnitude() <= this->getHeight ()) {

            // VERIFYING IF T IS POSITIVE
            if (t3 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

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

                // VERIFYING IF T IS POSITIVE
                if (t3 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                return intersectionResult;
            }

            // VERIFYING IF T IS POSITIVE
            if (t4 < 0) {
                intersectionResult->setHasIntersection (false);
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

                    // VERIFYING IF T IS POSITIVE
                    if (t3 < 0) {
                        intersectionResult->setHasIntersection (false);
                        return intersectionResult;
                    }

                    intersectionResult->setHasIntersection (true);
                    intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                    intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                    intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                    return intersectionResult;

                }

                // VERIFYING IF T IS POSITIVE
                if (t1 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_BASE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            if (distanceP0ToT3 < distanceP0ToT2) {

                // VERIFYING IF T IS POSITIVE
                if (t3 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT3);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT3));

                return intersectionResult;

            }

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_TOP);
            intersectionResult->setIntersectionPoint (new Vector (intersectionPointT2));

            return intersectionResult;

        }

        if (CbAT4ByDir > 0 && CbAT4.getMagnitude () < this->getHeight ()) {

            if (interceptsBase) {

                if (distanceP0ToT4 < distanceP0ToT1) {

                    // VERIFYING IF T IS POSITIVE
                    if (t4 < 0) {
                        intersectionResult->setHasIntersection (false);
                        return intersectionResult;
                    }

                    intersectionResult->setHasIntersection (true);
                    intersectionResult->setDistanceFromP0 (distanceP0ToT4);
                    intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                    intersectionResult->setIntersectionPoint (new Vector (intersectionPointT4));

                    return intersectionResult;

                }

                // VERIFYING IF T IS POSITIVE
                if (t1 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT1);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_BASE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT1));

                return intersectionResult;

            }

            if (distanceP0ToT4 < distanceP0ToT2) {

                // VERIFYING IF T IS POSITIVE
                if (t4 < 0) {
                    intersectionResult->setHasIntersection (false);
                    return intersectionResult;
                }

                intersectionResult->setHasIntersection (true);
                intersectionResult->setDistanceFromP0 (distanceP0ToT4);
                intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_SURFACE);
                intersectionResult->setIntersectionPoint (new Vector (intersectionPointT4));

                return intersectionResult;

            }

            // VERIFYING IF T IS POSITIVE
            if (t2 < 0) {
                intersectionResult->setHasIntersection (false);
                return intersectionResult;
            }

            intersectionResult->setHasIntersection (true);
            intersectionResult->setDistanceFromP0 (distanceP0ToT2);
            intersectionResult->setObjectRegion (ObjectRegion::CYLINDER_TOP);
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

    if (intersectionResult->getObjectRegion() == ObjectRegion::CYLINDER_TOP) {

        return this->calculateColorToBePainted (
            intersectionResult,
            lightsArray,
            objectsArray,
            line,
            environmentLight,
            this->getDirection (),
            this->getReflectivity (),
            this->getShininess ()
        );

    } else if (intersectionResult->getObjectRegion() == ObjectRegion::CYLINDER_BASE) {

        Sp<Vector> normal = new Vector (*this->getDirection() * (-1));

        return Object::calculateColorToBePainted (
            intersectionResult,
            lightsArray,
            objectsArray,
            line,
            environmentLight,
            normal.pointer,
            this->getReflectivity (),
            this->getShininess ()
        );

    } else {

        Vector pIMinusCb = *intersectionResult->getIntersectionPoint() - *this->getBaseCenter();

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

                M[i][j] = Identity[i][j] - (*this->getDirection())[i] * (*this->getDirection())[j];

            }
        }

        // normal to surface not unitary
        Vector N;

        for (int i = 0; i < 3; i++) {
            N[i] = M[i][0] * pIMinusCb[0] + M[i][1] * pIMinusCb[1] + M[i][2] * pIMinusCb[2];
        }

        // normal to surface unitary
        Sp<Vector> normal = new Vector (N / (N.getMagnitude()));

        return Object::calculateColorToBePainted (
            intersectionResult,
            lightsArray,
            objectsArray,
            line,
            environmentLight,
            normal.pointer,
            this->getReflectivity (),
            this->getShininess ()
        );

    }

}

void Cylinder::updateDirection() {
    Vector directionNotNormal = *this->topCenter - *this->baseCenter;
    Vector directionNormal = directionNotNormal / directionNotNormal.getMagnitude();
    *this->direction = directionNormal;
}

void Cylinder::applyScale(double sx, double sy, double sz) {
    *this->baseCenter = scale((*this->baseCenter), sx, sy, sz);
    *this->topCenter = scale((*this->topCenter), sx, sy, sz);
    this->updateDirection();
    this->setRadius(Vector(sx, sy, sz).getMagnitude() * this->getRadius());
}

void Cylinder::applyTranslate(double x, double y, double z) {
    *this->baseCenter = translate((*this->baseCenter), x, y, z);
    *this->topCenter = translate((*this->topCenter), x, y, z);
}

void Cylinder::applyRotateX(double angle) {
    *this->baseCenter = rotateX((*this->baseCenter), angle);
    *this->topCenter = rotateX((*this->topCenter), angle);
    this->updateDirection();
}

void Cylinder::applyRotateY(double angle) {
    *this->baseCenter = rotateY((*this->baseCenter), angle);
    *this->topCenter = rotateY((*this->topCenter), angle);
    this->updateDirection();
}

void Cylinder::applyRotateZ(double angle) {
    *this->baseCenter = rotateZ((*this->baseCenter), angle);
    *this->topCenter = rotateZ((*this->topCenter), angle);
    this->updateDirection();
}

void Cylinder::applyReflectXY() {
    *this->baseCenter = reflectXY((*this->baseCenter));
    *this->topCenter = reflectXY((*this->topCenter));
    this->updateDirection();
}

void Cylinder::applyReflectXZ() {
    *this->baseCenter = reflectXZ((*this->baseCenter));
    *this->topCenter = reflectXZ((*this->topCenter));
    this->updateDirection();
}

void Cylinder::applyReflectYZ() {
    *this->baseCenter = reflectYZ((*this->baseCenter));
    *this->topCenter = reflectYZ((*this->topCenter));
    this->updateDirection();
}

Cylinder::Cylinder () {}

Cylinder::Cylinder (Vector* baseCenter, Vector* direction, double height, double radius) {
    this->setBaseCenter (baseCenter);
    this->setRadius (radius);
    this->setHeight (height);
    *direction = *direction / (*direction).getMagnitude ();
    this->setDirection (direction);
    this->setTopCenter (
        new Vector (*this->getBaseCenter() + *this->getDirection () * this->getHeight ())
    );
}

Cylinder::Cylinder (Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess) {
    this->setBaseCenter (baseCenter);
    this->setTopCenter (topCenter);
    this->setRadius (radius);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
    this->setHeight ((*this->getTopCenter() - *this->getBaseCenter()).getMagnitude());
    this->setDirection (
        new Vector (
            (*this->getTopCenter() - *this->getBaseCenter()) /
            (*this->getTopCenter() - *this->getBaseCenter()).getMagnitude()
        )
    );
}

Cylinder::Cylinder (Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess) {
    this->setBaseCenter (baseCenter);
    this->setRadius (radius);
    this->setReflectivity (reflectivity);
    this->setShininess (shininess);
    this->setHeight (height);
    *direction = *direction / (*direction).getMagnitude ();
    this->setDirection (direction);
    this->setTopCenter (
        new Vector (*this->getBaseCenter() + *this->getDirection () * this->getHeight ())
    );
}

Cylinder::~Cylinder () {
    delete this->getBaseCenter ();
    delete this->getTopCenter ();
    delete this->getDirection ();
}