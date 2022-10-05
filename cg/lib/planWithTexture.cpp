#include "../include/planWithTexture.h"

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

    // Vector resultColorRate = this->calculateResultColorRate(
    //     line,
    //     intersectionResult,
    //     lightsArray,
    //     objectsArray,
    //     this->getNormal(),
    //     Vector* reflectivity,
    //     double shininess
    // );

    // if (environmentLight != nullptr) {
    //     resultColorRate = resultColorRate + ((*environmentLight) * (*this->getReflectivity()));
    // }

    Vector intersectionPoint = *intersectionResult->getIntersectionPoint();
    int x = intersectionPoint[0];
    int z = intersectionPoint[2];

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

    return new Color(
        pixelToPaint.r,
        pixelToPaint.g,
        pixelToPaint.b,
        pixelToPaint.a
    );
};

PlanWithTexture::PlanWithTexture() {}

PlanWithTexture::PlanWithTexture(Image* texture, Vector* initialPoint, Vector* normal, Vector* reflectivity, double shininess) {
    this->setTexture(texture);
    this->setInitialPoint(initialPoint);
    this->setNormal(normal);
    this->setReflectivity(reflectivity);
    this->setShininess(shininess);
}

PlanWithTexture::~PlanWithTexture() {
    delete this->getTexture();
}