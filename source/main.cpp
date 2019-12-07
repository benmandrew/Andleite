#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

bool init(SDL_Window** pWindow, SDL_Surface** screenSurface) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(
            "SDL could not initialise! SDL_Error: %s\n",
            SDL_GetError());
        success = false;
    } else {
        *pWindow = SDL_CreateWindow(
            "SDL",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (*pWindow == NULL) {
            printf(
                "Window could not be created! SDL_Error: %s\n",
                SDL_GetError());
                success = false;
        } else {
            *screenSurface = SDL_GetWindowSurface(*pWindow);
        }
    }
    return success;
}

bool loadMedia(
    std::string path, SDL_Surface** pSurface, SDL_Surface* screenSurface) {
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
            screenSurface->format,
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

void close(SDL_Window* window, SDL_Surface* player) {
    SDL_FreeSurface(player);
    player = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void mainLoop(
    SDL_Window* window,
    SDL_Surface* screenSurface,
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
        SDL_BlitScaled(player, NULL, screenSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Window** pWindow = &window;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface** pScreenSurface = &screenSurface;
    SDL_Surface* player = NULL;
    SDL_Surface** pPlayer = &player;
    if (!init(pWindow, pScreenSurface)) {
        printf("Failed to initialise!\n");
    } else {
        if (!loadMedia("./resources/slime.bmp", pPlayer, *pScreenSurface)) {
            printf("Failed to load media!\n");
        } else {
            mainLoop(*pWindow, *pScreenSurface, *pPlayer);
        }
    }
    close(*pWindow, *pPlayer);
    return 0;
}
