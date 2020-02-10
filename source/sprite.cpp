#include "sprite.h"

SDL_PixelFormat* Sprite::pixelFormat = NULL;

Sprite::Sprite(int _tileScreenSize) {
    tileScreenSize = _tileScreenSize;
    posRect = {0, 0, tileScreenSize, tileScreenSize};
}

Sprite::~Sprite() {
    SDL_FreeSurface(surface);
    surface = NULL;
}

void Sprite::updatePos(const IVec2 pos) {
    posRect.x = pos.x * tileScreenSize;
    posRect.y = pos.y * tileScreenSize;
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


inline SpriteEnum extractEnumFromPath(const std::string& path) {
    std::string name = path.substr(path.rfind('/') + 1);
    return spriteNameMap[name.substr(0, name.size() - 4)];
}

void SpriteIndex::addSprite(const std::string& path) {
    Sprite* sprite = new Sprite(tileScreenSize);
    sprite->loadBMP(path);
    sprites.insert({
        extractEnumFromPath(path),
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

Sprite* SpriteIndex::get(const SpriteEnum sprite) const {
    auto found = sprites.find(sprite);
    // Raise an error if not in the map
    assert(found != sprites.end());
    return found->second;
}

int SpriteIndex::getTileScreenSize() const {
    return tileScreenSize;
}
