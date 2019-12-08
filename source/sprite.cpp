#include "sprite.h"

SDL_PixelFormat* Sprite::pixelFormat = NULL;

Sprite::Sprite() {
    posRect = {0, 0, TILE_SIZE, TILE_SIZE};
}

Sprite::~Sprite() {
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Sprite::updatePos(int tileX, int tileY) {
    posRect.x = tileX * TILE_SIZE;
    posRect.y = tileY * TILE_SIZE;
}

void Sprite::loadBMP(std::string path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf(
            "Unable to load Sprite %s! SDL Error: %s\n",
            path.c_str(),
            SDL_GetError());
    } else {
        surface = SDL_ConvertSurface(
            loadedSurface,
            pixelFormat,
            0);
        if (surface == NULL) {
            printf(
                "Unable to optimize Sprite %s! SDL Error: %s\n",
                path.c_str(),
                SDL_GetError());
		}
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
}

void Sprite::setPixelFormat(SDL_PixelFormat* fmt) {
    pixelFormat = fmt;
}

SDL_PixelFormat* Sprite::getPixelFormat() {
    return pixelFormat;
}

SDL_Rect* Sprite::getPosRect() {
    return &posRect;
}

SDL_Surface* Sprite::getSurface() {
    return surface;
}