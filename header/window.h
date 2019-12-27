#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__
#pragma once

#include <SDL2/SDL.h>
#include "creature.h"

class Window {
private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

public:
    Window();
    ~Window();
    bool init(int screen_width, int screen_height);

    void blit(Sprite* sprite);
    void blit(SDL_Surface* surface, SDL_Rect* rect);
    void flip();
    void clear();

    SDL_PixelFormat* getPixelFormat();
};

#endif