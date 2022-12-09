#include <cmath>
#include "../include/cylinderWithTextureOnTop.h"
#include "../include/utils.impl.h"

void CylinderWithTextureOnTop::setTexture(Image* texture) {
    this->texture = texture;
}

Image* CylinderWithTextureOnTop::getTexture() {
    return this->texture;
}

Color* CylinderWithTextureOnTop::getColorToBePainted(
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {

    if (intersectionResult->getObjectRegion() == ObjectRegion::CYLINDER_TOP) {

        if (!this->isActive()) {
            return this->calculateColorToBePainted (
                intersectionResult,
                lightsArray,
                objectsArray,
                line,
                environmentLight,
                this->getDirection (),
                this->getKd (),
                this->getKa (),
                this->getKe (),
                this->getShininess ()
            );
        }

        Vector planNormal = *this->getDirection();
        Vector intersectionPoint = *intersectionResult->getIntersectionPoint();
        Vector intersectionPointMinusPlanP0 = intersectionPoint - *this->getTopCenter();

        Vector planRotatedToNormalInYAxes = intersectionPointMinusPlanP0;

        if (planNormal[0] != 0 || planNormal[2] != 0) {
            Vector planNormalRotatedInY = rotateY (
                planNormal,
                -asin(planNormal[0] / (
                    sqrt(
                        pow(planNormal[0], 2.0) + pow (planNormal[2], 2.0)
                    )
                ))
            );

            Vector intersectionPointMinusPlanP0RotatedInY = rotateY (
                intersectionPointMinusPlanP0,
                -asin(planNormal[0] / (
                    sqrt(
                        pow(planNormal[0], 2.0) + pow (planNormal[2], 2.0)
                    )
                ))
            );

            planRotatedToNormalInYAxes = rotateX (
                intersectionPointMinusPlanP0RotatedInY,
                -acos(planNormalRotatedInY[1])  
            );
        }

        int x = planRotatedToNormalInYAxes[0];
        int z = planRotatedToNormalInYAxes[2];

        int imagePixelPositionX;
        int imagePixelPositionY;

        if (x < 0) {
            imagePixelPositionX = this->texture->getImageWidth() - (abs(x) % this->texture->getImageWidth()) - 1;
        } else {
            imagePixelPositionX = abs(x) % this->texture->getImageWidth();
        }

        if (z < 0) {
            imagePixelPositionY = this->texture->getImageHeight() - (abs(z) % this->texture->getImageHeight()) - 1;
        } else {
            imagePixelPositionY = abs(z) % this->texture->getImageHeight();
        }

        Pixel pixelToPaint = this->texture->getPixel(imagePixelPositionX, imagePixelPositionY);

        Sp<Vector> pixelReflectivity = new Vector(
            ((double) pixelToPaint.r) / 255.0,
            ((double) pixelToPaint.g) / 255.0,
            ((double) pixelToPaint.b) / 255.0
        );

        Vector resultColorRate = this->calculateResultColorRate(
            line,
            intersectionResult,
            lightsArray,
            objectsArray,
            this->getDirection(),
            pixelReflectivity.pointer,
            pixelReflectivity.pointer,
            this->getShininess()
        );

        if (environmentLight != nullptr) {
            resultColorRate = resultColorRate + ((*environmentLight) * (*pixelReflectivity));
        }

        return new Color(
            resultColorRate[0] * 255,
            resultColorRate[1] * 255,
            resultColorRate[2] * 255,
            255
        );

    } else if (intersectionResult->getObjectRegion() == ObjectRegion::CYLINDER_BASE) {

        Sp<Vector> normal = new Vector (*this->getDirection() * (-1));

        if (!this->isActive()) {
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

        Vector planNormal = *normal;
        Vector intersectionPoint = *intersectionResult->getIntersectionPoint();
        Vector intersectionPointMinusPlanP0 = intersectionPoint - *this->getBaseCenter();

        Vector planRotatedToNormalInYAxes = intersectionPointMinusPlanP0;

        if (planNormal[0] != 0 || planNormal[2] != 0) {
            Vector planNormalRotatedInY = rotateY (
                planNormal,
                -asin(planNormal[0] / (
                    sqrt(
                        pow(planNormal[0], 2.0) + pow (planNormal[2], 2.0)
                    )
                ))
            );

            Vector intersectionPointMinusPlanP0RotatedInY = rotateY (
                intersectionPointMinusPlanP0,
                -asin(planNormal[0] / (
                    sqrt(
                        pow(planNormal[0], 2.0) + pow (planNormal[2], 2.0)
                    )
                ))
            );

            planRotatedToNormalInYAxes = rotateX (
                intersectionPointMinusPlanP0RotatedInY,
                -acos(planNormalRotatedInY[1])  
            );
        }

        int x = planRotatedToNormalInYAxes[0];
        int z = planRotatedToNormalInYAxes[2];

        int imagePixelPositionX;
        int imagePixelPositionY;

        if (x < 0) {
            imagePixelPositionX = this->texture->getImageWidth() - (abs(x) % this->texture->getImageWidth()) - 1;
        } else {
            imagePixelPositionX = abs(x) % this->texture->getImageWidth();
        }

        if (z < 0) {
            imagePixelPositionY = this->texture->getImageHeight() - (abs(z) % this->texture->getImageHeight()) - 1;
        } else {
            imagePixelPositionY = abs(z) % this->texture->getImageHeight();
        }

        Pixel pixelToPaint = this->texture->getPixel(imagePixelPositionX, imagePixelPositionY);

        Sp<Vector> pixelReflectivity = new Vector(
            ((double) pixelToPaint.r) / 255.0,
            ((double) pixelToPaint.g) / 255.0,
            ((double) pixelToPaint.b) / 255.0
        );

        Vector resultColorRate = this->calculateResultColorRate(
            line,
            intersectionResult,
            lightsArray,
            objectsArray,
            normal.pointer,
            pixelReflectivity.pointer,
            pixelReflectivity.pointer,
            this->getShininess()
        );

        if (environmentLight != nullptr) {
            resultColorRate = resultColorRate + ((*environmentLight) * (*pixelReflectivity));
        }

        return new Color(
            resultColorRate[0] * 255,
            resultColorRate[1] * 255,
            resultColorRate[2] * 255,
            255
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
            this->getKd (),
            this->getKa (),
            this->getKe (),
            this->getShininess ()
        );

    }
}

bool CylinderWithTextureOnTop::isActive() {
    return this->active;
}

void CylinderWithTextureOnTop::setActive(bool active) {
    this->active = active;
}

ObjectType CylinderWithTextureOnTop::getObjectType() {
    return this->type;
}

CylinderWithTextureOnTop::CylinderWithTextureOnTop() {}

CylinderWithTextureOnTop::CylinderWithTextureOnTop(Image* texture, Vector* baseCenter, Vector* topCenter, double radius, Vector* reflectivity, double shininess) {
    this->setTexture(texture);
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

    this->initialBaseCenter = new Vector(*this->getBaseCenter());
    this->initialTopCenter = new Vector(*this->getTopCenter());
}

CylinderWithTextureOnTop::CylinderWithTextureOnTop(Image* texture, Vector* baseCenter, Vector* direction, double height, double radius, Vector* reflectivity, double shininess) {
    this->setTexture(texture);
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

    this->initialBaseCenter = new Vector(*this->getBaseCenter());
    this->initialTopCenter = new Vector(*this->getTopCenter());
}

CylinderWithTextureOnTop::~CylinderWithTextureOnTop() {
    delete this->getTexture();
}