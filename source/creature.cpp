#include "creature.h"

Creature::Creature() {
    changedPos = true;
    x = 2;
    y = 2;
    sprite = new Sprite();
}

Creature::~Creature() {
    delete sprite;
}

void Creature::moveX(const int dx) {
    int new_x = (x + dx + TILE_NUM_X) % TILE_NUM_X;
    if (map->getTile({new_x, y}).type != TileType::open) {
        return;
    }
    x = new_x;
    changedPos = true;
}

void Creature::moveY(const int dy) {
    int new_y = (y + dy + TILE_NUM_Y) % TILE_NUM_Y;
    if (map->getTile({x, new_y}).type != TileType::open) {
        return;
    }
    y = new_y;
    changedPos = true;
}

void Creature::init(const std::string spritePath, Map* _map) {
    sprite->loadBMP(spritePath);
    map = _map;
}

Sprite* Creature::getSprite() {
    if (changedPos) {
        sprite->updatePos(x, y);
        changedPos = false;
    }
    return sprite;
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