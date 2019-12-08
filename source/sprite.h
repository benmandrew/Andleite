#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "constants.h"

class Sprite {
private:
    static SDL_PixelFormat* pixelFormat;

    bool changedPos;
    SDL_Rect posRect;
    SDL_Surface* surface;
public:
    Sprite();
    ~Sprite();

    static void setPixelFormat(SDL_PixelFormat* fmt);
    static SDL_PixelFormat* getPixelFormat();

    void updatePos(int tileX, int tileY);
    void loadBMP(std::string path);
    SDL_Rect* getPosRect();
    SDL_Surface* getSurface();
};
