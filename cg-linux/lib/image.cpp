#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../include/image.h"

using std::string;

Pixel::Pixel () {}

Pixel::Pixel (int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Image::loadImage (const string path) {

    SDL_Surface* image = IMG_Load(path.c_str());

    if (image == nullptr) {
        std::cout << "error on load the image" << std::endl;
        return;
    }

    int lockSurfaceResult = SDL_LockSurface (image);

    if (lockSurfaceResult != 0) {
        std::cout << "error on lock the texture bytes" << std::endl;
        SDL_FreeSurface (image);
        return;
    }

    if (this->image != nullptr) SDL_FreeSurface (this->image);

    this->image = image;

}

Pixel Image::getPixel (int x, int y) {

    int selectedPixel;

    int bytesPerPixel = this->image->format->BytesPerPixel;
    // pixel address
    Uint8* pixel = (Uint8*) this->image->pixels + y * this->image->pitch + x * bytesPerPixel;

    switch (bytesPerPixel) {
        case 1:
            selectedPixel = *pixel;
            break;
        case 2:
            selectedPixel = *((Uint16*) pixel);
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                selectedPixel = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
            } else {
                selectedPixel = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            }
            break;
        case 4:
            selectedPixel = *((Uint32*)pixel);
            break;
        default:
            selectedPixel = 0;
    }

    SDL_Color rgb;
    SDL_GetRGB(selectedPixel, this->image->format, &rgb.r, &rgb.g, &rgb.b);

    return Pixel (rgb.r, rgb.g, rgb.b);

}

int Image::getImageWidth () {
    return this->image->w;
}

int Image::getImageHeight () {
    return this->image->h;
}

Image::Image () {}

Image::Image (string path) {
    this->loadImage (path);
}

Image::~Image () {
    SDL_UnlockSurface (this->image);
    SDL_FreeSurface (this->image);
}
