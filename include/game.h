#ifndef GAME_H
#define GAME_H

#include "tank.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(const Time& elapsedTime);
    void render();
    void handleInput(Keyboard::Key key, bool isPressed);
    RenderWindow window;
    Texture gameTexture;
    Tank heroTank;
};

#endif // GAME_H
