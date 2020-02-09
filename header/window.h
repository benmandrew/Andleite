#ifndef __WINDOW_H_INCLUDED__
#define __WINDOW_H_INCLUDED__
#pragma once

#include <SDL2/SDL.h>
#include "gamemanager.h"
#include "maprenderer.h"

class Window {
private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SpriteIndex* spriteIndex;
    MapRenderer* mapRenderer;

    Vec2 worldPos;
    float winWorldWidth = 20.0f;
    float winWorldHeight = winWorldWidth / ASPECT_RATIO;
    float tileScreenSize = SCREEN_WIDTH / winWorldWidth;
    AABB mapBounds;

    AABB getVisibleMapBounds();

public:
    Window();
    ~Window();
    bool init(int screen_width, int screen_height);

    void draw(GameManager* g);

    void drawMap(Map* map);
    void drawEntities(std::vector<Creature*> entities);

    void blit(Sprite* sprite);
    void blit(SDL_Surface* surface, SDL_Rect* rect);
    void flip();
    void clear();

    SDL_PixelFormat* getPixelFormat();
};

#endif