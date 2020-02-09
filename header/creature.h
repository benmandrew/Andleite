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
    IVec2 pos;
    SpriteEnum sprite;
    Map* map;

    void moveX(const int dx);
    void moveY(const int dy);
public:
    Creature();

    void init(SpriteEnum _sprite, Map* _map);

    SpriteEnum getSpriteEnum() const;
    IVec2 getPos() const;

    void onNotify(const int event);
};

#endif