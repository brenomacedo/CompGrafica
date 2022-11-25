#include <cmath>
#include "../include/planWithTexture.h"
#include "../include/utils.impl.h"

void PlanWithTexture::setTexture(Image* texture) {
    this->texture = texture;
}

Image* PlanWithTexture::getTexture() {
    return this->texture;
}

Color* PlanWithTexture::getColorToBePainted(
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {

    Vector planNormal = *this->getNormal();
    Vector intersectionPoint = *intersectionResult->getIntersectionPoint();
    Vector intersectionPointMinusPlanP0 = intersectionPoint - *this->getInitialPoint();

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
        imagePixelPositionX = this->texture->getImageWidth() - (abs(x) % this->texture->getImageWidth());
    } else {
        imagePixelPositionX = abs(x) % this->texture->getImageWidth();
    }

    if (z < 0) {
        imagePixelPositionY = this->texture->getImageHeight() - (abs(z) % this->texture->getImageHeight());
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
        this->getNormal(),
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
}

PlanWithTexture::PlanWithTexture() {}

PlanWithTexture::PlanWithTexture(Image* texture, Vector* initialPoint, Vector* normal, double shininess) {
    this->setTexture(texture);
    this->setInitialPoint(initialPoint);
    this->setNormal(normal);
    this->setShininess(shininess);
}

PlanWithTexture::~PlanWithTexture() {
    delete this->getTexture();
}