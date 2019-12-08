#include "creature.h"

Creature::Creature() {
    changedPos = false;
    x = 0;
    y = 0;
    sprite = new Sprite();
}

Creature::~Creature() {
    delete sprite;
}

void Creature::moveX(int dx) {
    x = (x + dx + TILE_NUM_X) % TILE_NUM_X;
    changedPos = true;
}

void Creature::moveY(int dy) {
    y = (y + dy + TILE_NUM_Y) % TILE_NUM_Y;
    changedPos = true;
}

void Creature::init(std::string spritePath) {
    sprite->loadBMP(spritePath);
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