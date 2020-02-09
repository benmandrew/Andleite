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
#include "ivec2.h"

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

    void updatePos(const IVec2 pos);
    void loadBMP(const std::string& path);
    SDL_Rect* getPosRect();
    SDL_Surface* getSurface();
};

class SpriteIndex {
private:
    std::map<SpriteEnum, Sprite*> sprites;

    void addSprite(const std::string& path);

public:
    bool init(const std::string& resourcesPath);
    Sprite* get(const SpriteEnum sprite) const;
};

#endif