#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__
#pragma once

#include <SDL2/SDL.h>
#include "gamemanager.h"
#include "maprenderer.h"

class Window {
private:
    SDL_Rect mapRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SpriteIndex* spriteIndex;
    MapRenderer* mapRenderer;

    

public:
    Window();
    ~Window();
    bool init(int screen_width, int screen_height);

    void draw(GameManager* g);

    void blit(SDL_Surface* surface, SDL_Rect* rect);
    void flip();
    void clear();

    SDL_PixelFormat* getPixelFormat();
};

#endif