#include <SDL2/SDL.h>
#include <string>

#include "input.h"
#include "sprite.h"

class Creature : public Observer {
private:
    bool changedPos;
    int x, y;
    Sprite* sprite;

    void moveX(int dx);
    void moveY(int dy);
public:
    Creature();
    ~Creature();

    void init(std::string spritePath);
    Sprite* getSprite();

    void onNotify(int event);
};