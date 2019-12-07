#include <SDL2/SDL.h>

class Window {
private:
    SDL_Window* mWindow = NULL;
    SDL_Surface* mScreenSurface = NULL;

public:
    Window();
    ~Window();
    bool init(int screen_width, int screen_height);

    void blit(SDL_Surface* surface, SDL_Rect* stretchRect);
    void update();

    SDL_PixelFormat* getPixelFormat();
};