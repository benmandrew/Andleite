#include <SDL2/SDL.h>
#include <string>

#include "input.h"

constexpr static int TILE_SIZE = 32;

class Creature : public Observer {
private:
    static SDL_PixelFormat* pixelFormat;

    bool changedPos;
    int x, y;
    SDL_Rect posRect;
    SDL_Surface* surface;

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