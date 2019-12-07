#include <SDL2/SDL.h>
#include "creature.h"

class Window {
private:
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

public:
    Window();
    ~Window();
    bool init(int screen_width, int screen_height);

    void blit(Creature* creature);
    void flip();

    SDL_PixelFormat* getPixelFormat();
};