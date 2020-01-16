#include "window.h"


Window::Window() {
}

Window::~Window() {
    delete spriteIndex;
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
            Sprite::setPixelFormat(getPixelFormat());
            mapBounds = getVisibleMapBounds();
            spriteIndex = new SpriteIndex();
        }
    }
    return success;
}

AABB Window::getVisibleMapBounds() {
    int minX = std::floor(worldPos.x + 0.5f - (winWorldWidth / 2.0f));
    int maxX = std::ceil(worldPos.x + 0.5f + (winWorldWidth / 2.0f));
    int minY = std::floor(worldPos.y + 0.5f - (winWorldHeight / 2.0f));
    int maxY = std::ceil(worldPos.y + 0.5f + (winWorldHeight / 2.0f));
    return {{minX, minY}, {maxX, maxY}};
}

void Window::draw(GameManager* g) {
    clear();
    drawMap(g->map);
    drawEntities(g->entities);
    flip();
}

void Window::drawMap(Map* map) {
    SDL_Rect posRect = {0, 0, tileScreenSize, tileScreenSize};
    for (int x = mapBounds.topLeft.x; x <= mapBounds.bottomRight.x; x++) {
        for (int y = mapBounds.topLeft.y; y <= mapBounds.bottomRight.y; y++) {
            Sprite* sprite = map->getSpriteForPos({x, y});
            if (sprite == nullptr) {
                continue;
            }
            posRect.x = (x - mapBounds.topLeft.x) * tileScreenSize;
            posRect.y = (y - mapBounds.topLeft.y) * tileScreenSize;
            SDL_BlitScaled(
                sprite->getSurface(),
                NULL,
                screenSurface,
                &posRect
            );
        }
    }
}

void Window::drawEntities(std::vector<Creature*> entities) {
    SDL_Rect posRect = {0, 0, tileScreenSize, tileScreenSize};
    for (Creature* entity : entities) {
        Vec2 p = entity->getPos();
        posRect.x = (p.x - mapBounds.topLeft.x) * tileScreenSize;
        posRect.y = (p.y - mapBounds.topLeft.y) * tileScreenSize;
        SDL_BlitScaled(
            spriteIndex->get(entity->getSpriteEnum());
            NULL,
            screenSurface,
            &posRect
        );
    }
}

void Window::blit(Sprite* sprite) {
    SDL_BlitScaled(
        sprite->getSurface(),
        NULL,
        screenSurface,
        sprite->getPosRect());
}

void Window::blit(SDL_Surface* surface, SDL_Rect* rect) {
    SDL_BlitScaled(
        surface,
        NULL,
        screenSurface,
        rect);
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