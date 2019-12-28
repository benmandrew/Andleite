#ifndef __SPRITE_H_INCLUDED__
#define __SPRITE_H_INCLUDED__
#pragma once

#include <string>
#include <iostream>
#include <map>
#include <assert.h>
#include <dirent.h>
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

class SpriteIndex {
private:
    static std::map<std::string, Sprite*> sprites;

public:
    static void init(const std::string resourcesPath);
    static Sprite* get(const std::string id);
};

#endif