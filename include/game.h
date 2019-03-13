#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "player.h"
#include "conf.h"



class Game
{
public:
    Game();
    void run();

private:
    void adaptPlayerPosition();
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void render();
    void handleRealTimeInput();
    sf::RenderWindow window;
    sf::Texture gameTexture;
    Player heroTank;
};

#endif // GAME_H
