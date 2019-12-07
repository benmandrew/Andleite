#include <SDL2/SDL.h>
#include <string>

constexpr static int TILE_SIZE = 16;
constexpr static int HALF_TILE_SIZE = TILE_SIZE / 2;

class Creature {
private:
    static SDL_PixelFormat* pixelFormat;

    bool changedPos;
    int x, y;
    SDL_Rect posRect;
    SDL_Surface* surface;

    void updateTilePos();
    void loadBMP(std::string path);
public:
    Creature();
    ~Creature();

    static void setPixelFormat(SDL_PixelFormat* fmt);

    SDL_Rect* getPosRect();
    SDL_Surface* getSurface();
};