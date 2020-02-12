#include "entity.h"

Entity::Entity()
    : pos({2, 2}) {
}

void Entity::moveX(const int dx) {
    int new_x = (pos.x + dx + TILE_NUM_X) % TILE_NUM_X;
    if (map->getTile({new_x, pos.y})->type != TileType::open) {
        return;
    }
    pos.x = new_x;
}

void Entity::moveY(const int dy) {
    int new_y = (pos.y + dy + TILE_NUM_Y) % TILE_NUM_Y;
    if (map->getTile({pos.x, new_y})->type != TileType::open) {
        return;
    }
    pos.y = new_y;
}

void Entity::init(SpriteEnum _sprite, Map* _map) {
    sprite = _sprite;
    map = _map;
}

SpriteEnum Entity::getSpriteEnum() const {
    return sprite;
}

IVec2 Entity::getPos() const {
    return pos;
}

void Entity::onNotify(int event) {
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