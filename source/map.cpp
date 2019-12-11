#include "map.h"

bool Room::collidesWith(Room other) {
    return (
        x0 - 1 < other.x1 &&
        x1 + 1 > other.x0 &&
        y0 - 1 < other.y1 &&
        y1 + 1 > other.y0);
}

Sprite* Map::wallSprite = new Sprite();
Sprite* Map::openSprite = new Sprite();

Map::Map() {
    srand(time(NULL));
    mapPosRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

Map::~Map() {

}

void Map::init() {
    wallSprite->loadBMP(WALL_BMP_PATH);
    openSprite->loadBMP(OPEN_BMP_PATH);
    mapSurface = SDL_CreateRGBSurface(
        0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    generateMap();
    blitMap();
}

void Map::generateMap() {
    for (int x = 0; x < TILE_NUM_X; x++) {
        for (int y = 0; y < TILE_NUM_Y; y++) {
            grid[x][y] = wall;
        }
    }
    generateRooms();
}

inline int randomInt(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

void Map::generateRooms() {
    for (int i = 0; i < ROOM_ATTEMPT_NUM; i++) {
        int width = randomInt(
            ROOM_MIN_SIZE, ROOM_MAX_SIZE);
        int height = randomInt(
            ROOM_MIN_SIZE, ROOM_MAX_SIZE);
        int x0 = randomInt(1, TILE_NUM_X - width - 1);
        int y0 = randomInt(1, TILE_NUM_Y - height - 1);
        generateRoom(x0, y0, x0 + width, y0 + height);
    }
}

void Map::generateRoom(int x0, int y0, int x1, int y1) {
    Room candidateRoom = {x0, y0, x1, y1};
    for (int i = 0; i < rooms.size(); i++) {
        if (candidateRoom.collidesWith(rooms[i])) {
            return;
        }
    }
    rooms.push_back(candidateRoom);
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            grid[x][y] = open;
        }
    }
}

void Map::blitMap() {
    Sprite* currentTileSprite;
    SDL_Rect posRect = {0, 0, TILE_SIZE, TILE_SIZE};
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

SDL_Rect* Map::getRect() {
    return &mapPosRect;
}

SDL_Surface* Map::getSurface() {
    return mapSurface;
}