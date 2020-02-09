
#include "maprenderer.h"

MapRenderer::MapRenderer(AABB _bounds)
        : bounds(_bounds) {
    surface = new SDL_Surface();
}

MapRenderer::~MapRenderer() {
    delete surface;
}

SDL_Surface* MapRenderer::drawToSurface(Map* map) {
    SDL_Rect posRect = {0, 0, tileScreenSize, tileScreenSize};
    for (int x = mapBounds.topLeft.x; x <= mapBounds.bottomRight.x; x++) {
        for (int y = mapBounds.topLeft.y; y <= mapBounds.bottomRight.y; y++) {
            Sprite* sprite = map->getSpriteForPos({x, y});
            if (sprite == nullptr) {
                continue;
            }
            posRect.x = (x - mapBounds.topLeft.x) * tileScreenSize;
            posRect.y = (y - mapBounds.topLeft.y) * tileScreenSize;
            SDL_BlitScaled(
                sprite->getSurface(),
                NULL,
                surface,
                &posRect
            );
        }
    }
    return surface;
}
