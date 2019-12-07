#include <SDL2/SDL.h>
#include <string>

#include "input.h"

constexpr static int TILE_SIZE = 32;
constexpr static int TILE_NUM_X = 20;
constexpr static int TILE_NUM_Y = 15;

class Creature : public Observer {
private:
    static SDL_PixelFormat* pixelFormat;

    bool changedPos;
    int x, y;
    SDL_Rect posRect;
    SDL_Surface* surface;

    void moveX(int dx);
    void moveY(int dy);

    void updateTilePos();
public:
    Creature();
    ~Creature();

    static void setPixelFormat(SDL_PixelFormat* fmt);

    void loadBMP(std::string path);
    SDL_Rect* getPosRect();
    SDL_Surface* getSurface();

    void onNotify(int event);
};