#include "sprite.h"

SDL_PixelFormat* Sprite::pixelFormat = NULL;

Sprite::Sprite() {
    posRect = {0, 0, TILE_SIZE, TILE_SIZE};
}

Sprite::~Sprite() {
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Sprite::updatePos(const Vec2 pos) {
    posRect.x = pos.x * TILE_SIZE;
    posRect.y = pos.y * TILE_SIZE;
}

void Sprite::loadBMP(const std::string& path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf(
            "Unable to load Sprite %s! SDL Error: %s\n",
            path.c_str(),
            SDL_GetError());
    } else {
        surface = SDL_ConvertSurface(
            loadedSurface,
            pixelFormat,
            0);
        if (surface == NULL) {
            printf(
                "Unable to optimize Sprite %s! SDL Error: %s\n",
                path.c_str(),
                SDL_GetError());
		}
        SDL_FreeSurface(loadedSurface);
        loadedSurface = NULL;
    }
}

void Sprite::setPixelFormat(SDL_PixelFormat* fmt) {
    pixelFormat = fmt;
}

SDL_PixelFormat* Sprite::getPixelFormat() {
    return pixelFormat;
}

SDL_Rect* Sprite::getPosRect() {
    return &posRect;
}

SDL_Surface* Sprite::getSurface() {
    return surface;
}


inline std::string extractNameFromPath(const std::string& path) {
    std::string name = path.substr(path.rfind('/') + 1);
    return name.substr(0, name.size() - 4);
}

void SpriteIndex::addSprite(const std::string& path) {
    Sprite* sprite = new Sprite();
    sprite->loadBMP(path);
    sprites.insert({
        extractNameFromPath(path),
        sprite});
}

inline bool endsWith(const std::string& a, const std::string& b) {
    if (b.size() > a.size()) {
        return false;
    }
    return std::equal(a.begin() + a.size() - b.size(), a.end(), b.begin());
}

bool SpriteIndex::init(const std::string& resourcesPath) {
    dirent *entry = nullptr;
    DIR *dp = nullptr;
    dp = opendir(resourcesPath.c_str());
    if (dp == nullptr) {
        return false;
    }
    while (entry = readdir(dp)) {
        if (!endsWith(entry->d_name, ".bmp")) {
            continue;
        }
        addSprite(resourcesPath + '/' + entry->d_name);
    }
    closedir(dp);
    return true;
}

Sprite* SpriteIndex::get(const std::string& id) {
    auto found = sprites.find(id);
    // Raise an error if not in the map
    assert(found != sprites.end());
    return found->second;
}
