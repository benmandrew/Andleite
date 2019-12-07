#include "creature.h"

SDL_PixelFormat* Creature::pixelFormat = NULL;

Creature::Creature() {
    changedPos = false;
    x = 0;
    y = 0;
    posRect.x = 0;
    posRect.y = 0;
    posRect.w = TILE_SIZE;
    posRect.h = TILE_SIZE;
}

Creature::~Creature() {
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Creature::updateTilePos() {
    posRect.x = x * TILE_SIZE;
    posRect.y = y * TILE_SIZE;
}

void Creature::loadBMP(std::string path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf(
            "Unable to load image %s! SDL Error: %s\n",
            path.c_str(),
            SDL_GetError());
    } else {
        surface = SDL_ConvertSurface(
            loadedSurface,
            pixelFormat,
            0);
        if (surface == NULL) {
            printf(
                "Unable to optimize image %s! SDL Error: %s\n",
                path.c_str(),
                SDL_GetError());
		}
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
}

void Creature::setPixelFormat(SDL_PixelFormat* fmt) {
    pixelFormat = fmt;
}

SDL_Rect* Creature::getPosRect() {
    if (changedPos) {
        updateTilePos();
        changedPos = false;
    }
    return &posRect;
}

SDL_Surface* Creature::getSurface() {
    return surface;
}

void Creature::onNotify(int event) {
    switch (event) {
        case KEY_UP:
            printf("Up\n");
            break;
        case KEY_DOWN:
            printf("Down\n");
            break;
        case KEY_LEFT:
            printf("Left\n");
            break;
        case KEY_RIGHT:
            printf("Right\n");
            break;
    }
}