#include "creature.h"

Creature::Creature() {
    changedPos = false;
    x, y = 0;
    posRect.x, posRect.y = 0;
    posRect.w, posRect.h = TILE_SIZE;
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
            "player.bmp",
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
                SDL_GetError() );
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

