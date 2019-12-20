#pragma once

#include <string>

constexpr static int SCREEN_WIDTH = 1280;
constexpr static int SCREEN_HEIGHT = 960;
constexpr static float ASPECT_RATIO = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

constexpr static int TILE_NUM_X = 40;
constexpr static int TILE_NUM_Y = (int)(TILE_NUM_X / ASPECT_RATIO);

constexpr static int TILE_SIZE = SCREEN_WIDTH / TILE_NUM_X;

constexpr static int ROOM_ATTEMPT_NUM = 200;
constexpr static int ROOM_MIN_SIZE = 4;
constexpr static int ROOM_MAX_SIZE = 8;

const static std::string PLAYER_BMP_PATH = "./resources/player.bmp";
const static std::string SLIME_BMP_PATH = "./resources/slime.bmp";

const static std::string WALL_BMP_PATH = "./resources/wall.bmp";
const static std::string OPEN_BMP_PATH = "./resources/floor.bmp";