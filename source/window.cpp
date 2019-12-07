#include "window.h"

Window::Window() {

}

Window::~Window() {
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    SDL_Quit();
}

bool Window::init(int screen_width, int screen_height) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(
            "SDL could not initialise! SDL_Error: %s\n",
            SDL_GetError());
        success = false;
    } else {
        mWindow = SDL_CreateWindow(
            "SDL",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screen_width,
            screen_height,
            SDL_WINDOW_SHOWN);
        if (mWindow == NULL) {
            printf(
                "Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
            success = false;
        } else {
            mScreenSurface = SDL_GetWindowSurface(mWindow);
        }
    }
    return success;
}

void Window::blit(SDL_Surface* surface, SDL_Rect* stretchRect) {
    SDL_BlitScaled(surface, NULL, mScreenSurface, stretchRect);
}

void Window::update() {
    SDL_UpdateWindowSurface(mWindow);
}

SDL_PixelFormat* Window::getPixelFormat() {
    return mScreenSurface->format;
}