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
    void adaptPlayerPosition();

private:
    void processEvents();
    void update(const Time& elapsedTime);
    void render();
    void handleRealTimeInput();
    RenderWindow window;
    Texture gameTexture;
    Player heroTank;
};

#endif // GAME_H
