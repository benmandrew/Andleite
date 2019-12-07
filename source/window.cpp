#include "window.h"


Window::Window() {
}

Window::~Window() {
    SDL_DestroyWindow(window);
    window = NULL;
}

bool Window::init(int screen_width, int screen_height) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(
            "SDL could not initialise! SDL_Error: %s\n",
            SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow(
            "SDL",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screen_width,
            screen_height,
            SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf(
                "Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
            success = false;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            Creature::setPixelFormat(getPixelFormat());
        }
    }
    return success;
}

void Window::blit(Creature* creature) {
    SDL_BlitScaled(
        creature->getSurface(),
        NULL,
        screenSurface,
        creature->getPosRect());
}

void Window::flip() {
    SDL_UpdateWindowSurface(window);
}

void Window::clear() {
    SDL_FillRect(screenSurface, NULL, 0x000000);
}

SDL_PixelFormat* Window::getPixelFormat() {
    return screenSurface->format;
}