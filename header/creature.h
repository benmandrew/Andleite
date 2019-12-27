#ifndef __CREATURE_H_INCLUDED__
#define __CREATURE_H_INCLUDED__
#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "input.h"
#include "map.h"
#include "sprite.h"

class Creature : public Observer {
private:
    bool changedPos;
    int x, y;
    Sprite* sprite;
    Map* map;

    void moveX(const int dx);
    void moveY(const int dy);
public:
    Creature();
    ~Creature();

    void init(std::string spritePath, Map* _map);
    Sprite* getSprite();

    void onNotify(const int event);
};

#endif