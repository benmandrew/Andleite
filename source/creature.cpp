#include "creature.h"

Creature::Creature() {
    changedPos = true;
    pos = {2, 2};
    sprite = new Sprite();
}

Creature::~Creature() {
    delete sprite;
}

void Creature::moveX(const int dx) {
    int new_x = (pos.x + dx + TILE_NUM_X) % TILE_NUM_X;
    if (map->getTile({new_x, pos.y}).type != TileType::open) {
        return;
    }
    pos.x = new_x;
    changedPos = true;
}

void Creature::moveY(const int dy) {
    int new_y = (pos.y + dy + TILE_NUM_Y) % TILE_NUM_Y;
    if (map->getTile({pos.x, new_y}).type != TileType::open) {
        return;
    }
    pos.y = new_y;
    changedPos = true;
}

void Creature::init(const std::string spritePath, Map* _map) {
    sprite->loadBMP(spritePath);
    map = _map;
}

Sprite* Creature::getSprite() {
    if (changedPos) {
        sprite->updatePos(pos);
        changedPos = false;
    }
    return sprite;
}

Vec2 Creature::getPos() {
    return pos;
}

void Creature::onNotify(int event) {
    switch (event) {
        case KEY_UP:
            moveY(-1);
            break;
        case KEY_DOWN:
            moveY(1);
            break;
        case KEY_LEFT:
            moveX(-1);
            break;
        case KEY_RIGHT:
            moveX(1);
            break;
    }
}