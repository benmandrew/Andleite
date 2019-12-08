#include "map.h"

Sprite* Map::wallSprite = new Sprite();
Sprite* Map::openSprite = new Sprite();

Map::Map() {

}

Map::~Map() {

}

void Map::init() {
    
    wallSprite->loadBMP(WALL_BMP_PATH);
    openSprite->loadBMP(OPEN_BMP_PATH);

    mapSurface = SDL_CreateRGBSurface(
        0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
}

void Map::generateMap() {
    for (int x = 0; x < TILE_NUM_X; x++) {
        for (int y = 0; y < TILE_NUM_Y; y++) {
            grid[x][y] = wall;
        }
    }
}

void Map::blitMap() {
    Sprite* currentTileSprite;
    SDL_Rect posRect;
    posRect.x = 0;
    posRect.y = 0;
    posRect.w = TILE_SIZE;
    posRect.h = TILE_SIZE;
    for (int x = 0; x < TILE_NUM_X; x++) {
        for (int y = 0; y < TILE_NUM_Y; y++) {
            if (grid[x][y] == wall) {
                currentTileSprite = wallSprite;
            } else {
                currentTileSprite = openSprite;
            }
            posRect.x = x * TILE_SIZE;
            posRect.y = y * TILE_SIZE;
            SDL_BlitScaled(
                currentTileSprite->getSurface(),
                NULL,
                mapSurface,
                &posRect
            );

        }
    }
}
