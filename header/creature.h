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
    Vec2 pos;
    Sprite* sprite;
    Map* map;

    void moveX(const int dx);
    void moveY(const int dy);
public:
    Creature();

    void init(Sprite* _sprite, Map* _map);

    Sprite* getSprite();
    Vec2 getPos();

    void onNotify(const int event);
};

#endif