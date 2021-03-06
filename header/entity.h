#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__
#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "input.h"
#include "map.h"
#include "sprite.h"

class Entity : public Observer, public Subject {
private:
    IVec2 pos;
    SpriteEnum sprite;
    Map* map;

    void moveX(const int dx);
    void moveY(const int dy);
public:
    Entity();

    void init(SpriteEnum _sprite, Map* _map);

    SpriteEnum getSpriteEnum() const;
    IVec2 getPos() const;

    void onNotify(const int event);
};

#endif