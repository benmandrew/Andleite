#include "map.h"

#include <string>
#include <iostream>

constexpr int nAdjOffsets = 9;
constexpr int nAdjOffsetsDir = 6;

struct Cardinal {
    Vec2 offset;
    Direction dir;
};

Vec2 adjOffsets[] = {
    {0, 0}, {0, 1}, {1, 1}, {1, 0}, {1, -1},
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};
Vec2 adjOffsetsNorth[] = {
    {0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}
};
Vec2 adjOffsetsEast[] = {
    {0, 0}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}
};
Vec2 adjOffsetsSouth[] = {
    {0, 0}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}
};
Vec2 adjOffsetsWest[] = {
    {0, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}
};

Cardinal moveDirections[] = {
    {{0, -1}, Direction::north},
    {{1, 0}, Direction::east},
    {{0, 1}, Direction::south},
    {{-1, 0}, Direction::west}
};

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
            if (x == 0 || y == 0 || x == TILE_NUM_X - 1
                    || y == TILE_NUM_Y - 1) {
                grid[x][y] = Tile(TileType::edge, nullptr);
            } else {
                grid[x][y] = Tile(TileType::wall, nullptr);
            }
        }
    }
    generateRooms();
    for (int x = 1; x < TILE_NUM_X - 1; x++) {
        for (int y = 1; y < TILE_NUM_Y - 1; y++) {
            Vec2 pos{x, y};
            if (!adjacentToOpen(pos)) {
                generateCorridor(pos);
            }
        }
    }
}

// Inclusive
inline int randomInt(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

void Map::generateRooms() {
    for (int i = 0; i < ROOM_ATTEMPT_NUM; i++) {
        int width = randomInt(
            ROOM_MIN_SIZE, ROOM_MAX_SIZE);
        int height = randomInt(
            ROOM_MIN_SIZE, ROOM_MAX_SIZE);
        int x0 = randomInt(2, TILE_NUM_X - width - 2);
        int y0 = randomInt(2, TILE_NUM_Y - height - 2);
        generateRoom(x0, y0, x0 + width, y0 + height);
    }
}

void Map::generateRoom(
        const int x0, const int y0,
        const int x1, const int y1) {
    Region candidateRoom;
    candidateRoom.setBounds({x0, y0}, {x1, y1});
    for (int i = 0; i < rooms.size(); i++) {
        if (candidateRoom.boundsCollide(rooms[i], true)) {
            return;
        }
    }
    rooms.push_back(candidateRoom);
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            grid[x][y] = Tile(TileType::open, nullptr);
        }
    }
}

// Fisher-Yates shuffle
void shuffleDirections() {
    for (int i = 3; i > 0; i--) {
        int j = randomInt(0, i);
        Cardinal temp = moveDirections[i];
        moveDirections[i] = moveDirections[j];
        moveDirections[j] = temp;
    }
}

void Map::generateCorridor(
        const Vec2 startPos) {
    grid[startPos.x][startPos.y] = Tile(TileType::open, nullptr);
    Vec2 currentPos = startPos;
    std::vector<Vec2> history;
    history.push_back(currentPos);
    do {
        if (extendCorridor(&currentPos)) {
            history.push_back(currentPos);
            grid[currentPos.x][currentPos.y] = Tile(
                TileType::open, nullptr);
        } else {
            currentPos = history.back();
            history.pop_back();
        }
    } while (history.size() > 0);
}

bool Map::extendCorridor(Vec2* currentPos) {
    shuffleDirections();
    for (Cardinal offset : moveDirections) {
        if (!adjacentToOpenInDirection(
                *currentPos, offset.offset, offset.dir)) {
            *currentPos += offset.offset;
            return true;
        }
    }
    return false;
}

Vec2* getOffsets(const Direction dir) {
    Vec2* offsets = &adjOffsets[0];
    if (dir != -1) {
        switch (dir) {
        case Direction::north:
            offsets = &adjOffsetsNorth[0];
            break;
        case Direction::east:
            offsets = &adjOffsetsEast[0];
            break;
        case Direction::south:
            offsets = &adjOffsetsSouth[0];
            break;
        case Direction::west:
            offsets = &adjOffsetsWest[0];
            break;
        }
    }
    return offsets;
}

bool Map::adjacentToOpen(const Vec2 pos) const {
    return adjacentToOpenInDirection(pos, {0, 0}, (Direction)(-1));
}

bool Map::adjacentToOpenInDirection(
        const Vec2 pos, const Vec2 offset, const Direction dir) const {
    int n = (dir == -1) ? nAdjOffsets : nAdjOffsetsDir;
    Vec2* offsets = getOffsets(dir);
    for (int i = 0; i < n; i++) {
        Vec2 p = pos + offset + offsets[i];
        Tile tile = grid[p.x][p.y];
        if (tile.type != TileType::wall) {
            return true;
        }
    }
    return false;
}

void Map::blitMap() {
    Sprite* currentTileSprite;
    SDL_Rect posRect = {0, 0, TILE_SIZE, TILE_SIZE};
    for (int x = 0; x < TILE_NUM_X; x++) {
        for (int y = 0; y < TILE_NUM_Y; y++) {
            if (grid[x][y].type == TileType::wall
                    || grid[x][y].type == TileType::edge) {
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

Tile Map::getTile(const Vec2 pos) const {
    return grid[pos.x][pos.y];
}

SDL_Rect* Map::getRect() {
    return &mapPosRect;
}

SDL_Surface* Map::getSurface() const {
    return mapSurface;
}