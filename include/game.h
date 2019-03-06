#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "tank.h"
#include "SFML/Graphics.hpp"


class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(const sf::Time& elapsedTime);
    void render();
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    sf::RenderWindow window;
    sf::Texture gameTexture;
    Tank heroTank;
};

#endif // GAME_H
