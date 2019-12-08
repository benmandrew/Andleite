#include <string>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 960;
constexpr float ASPECT_RATIO = SCREEN_WIDTH / (float)SCREEN_HEIGHT;

constexpr static int TILE_NUM_X = 40;
constexpr static int TILE_NUM_Y = (int)(TILE_NUM_X / ASPECT_RATIO);

constexpr static int TILE_SIZE = SCREEN_WIDTH / TILE_NUM_X;

const std::string PLAYER_BMP_PATH = "./resources/player.bmp";
const std::string SLIME_BMP_PATH = "./resources/slime.bmp";

const std::string WALL_BMP_PATH = "./resources/player.bmp";
const std::string OPEN_BMP_PATH = "./resources/slime.bmp";