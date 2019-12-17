#include "map.h"

constexpr int nAdjOffsets = 8;
constexpr int nAdjOffsetsDir = 3;

int adjOffsets[][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1},
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
};
int adjOffsetsNorth[][2] = {
    {-1, -1}, {0, -1}, {1, -1}
};
int adjOffsetsEast[][2] = {
    {1, -1}, {1, 0}, {1, 1}
};
int adjOffsetsSouth[][2] = {
    {-1, 1}, {0, 1}, {1, 1}
};
int adjOffsetsWest[][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}
};

static int moveDirections[][2] = {
    {0, -1}, {1, 0}, {0, 1}, {-1, 0}
};

bool Room::collidesWith(const Room other) const {
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
            grid[x][y] = Tile::wall;
        }
    }
    generateRooms();
    for (int x = 0; x < TILE_NUM_X; x++) {
        for (int y = 0; y < TILE_NUM_Y; y++) {
            generateCorridor(x, y);
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
        int x0 = randomInt(1, TILE_NUM_X - width - 1);
        int y0 = randomInt(1, TILE_NUM_Y - height - 1);
        generateRoom(x0, y0, x0 + width, y0 + height);
    }
}

void Map::generateRoom(
        const int x0, const int y0,
        const int x1, const int y1) {
    Room candidateRoom = {x0, y0, x1, y1};
    for (int i = 0; i < rooms.size(); i++) {
        if (candidateRoom.collidesWith(rooms[i])) {
            return;
        }
    }
    rooms.push_back(candidateRoom);
    for (int y = y0; y < y1; y++) {
        for (int x = x0; x < x1; x++) {
            grid[x][y] = Tile::open;
        }
    }
}

// Fisher-Yates shuffle
void shuffleDirections() {
    for (int i = 3; i > 0; i--) {
        int j = randomInt(0, i);
        for (int p = 0; p < 1; p++) {
            int temp = moveDirections[i][p];
            moveDirections[i][p] = moveDirections[j][p];
            moveDirections[j][p] = temp;
        }
    }
}

void Map::generateCorridor(
        const int startX, const int startY) {

}

int* getOffsets(const Direction dir) {
    int* offsets = &adjOffsets[0][0];
    if (dir != -1) {
        switch (dir) {
        case Direction::north:
            offsets = &adjOffsetsNorth[0][0];
            break;
        case Direction::east:
            offsets = &adjOffsetsEast[0][0];
            break;
        case Direction::south:
            offsets = &adjOffsetsSouth[0][0];
            break;
        case Direction::west:
            offsets = &adjOffsetsWest[0][0];
            break;
        }
    }
    return offsets;
}

bool Map::adjacentToOpen(
        const int x, const int y,
        const Direction dir = (Direction)(-1)) const {
    int n = (dir == -1) ? nAdjOffsets : nAdjOffsetsDir;
    int* offsets = getOffsets(dir);
    for (int i = 0; i < n; i++) {
        Tile tile = grid
            [x + offsets[i * 2 + 0]]
            [y + offsets[i * 2 + 1]];
        if (tile == Tile::open) {
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

SDL_Surface* Map::getSurface() const {
    return mapSurface;
}