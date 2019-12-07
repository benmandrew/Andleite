#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

#include "window.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

bool loadMedia(
    std::string path, SDL_Surface** pSurface, SDL_PixelFormat* fmt) {
    bool success = true;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf(
            "Unable to load image %s! SDL Error: %s\n",
            "player.bmp",
            SDL_GetError());
        success = false;
    } else {
        *pSurface = SDL_ConvertSurface(
            loadedSurface,
            fmt,
            0);
        if (*pSurface == NULL) {
            printf(
                "Unable to optimize image %s! SDL Error: %s\n",
                path.c_str(),
                SDL_GetError() );
            success = false;
		}
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
    return success;
}

void close(SDL_Surface* player) {
    SDL_FreeSurface(player);
    player = NULL;
}

void mainLoop(
    Window window,
    SDL_Surface* player) {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        window.blit(player, &stretchRect);
        window.update();
    }
}

int main(int argc, char* args[]) {

    SDL_Surface* player = NULL;
    SDL_Surface** pPlayer = &player;

    Window window;
    if (!window.init(SCREEN_WIDTH, SCREEN_HEIGHT)) {
        printf("Failed to initialise!\n");
    } else {
        if (!loadMedia("./resources/slime.bmp", pPlayer, window.getPixelFormat())) {
            printf("Failed to load media!\n");
        } else {
            mainLoop(window, *pPlayer);
        }
    }
    close(*pPlayer);
    return 0;
}
