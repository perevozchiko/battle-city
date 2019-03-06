#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "tank.h"
#include "map.h"


class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(const Time& elapsedTime);
    void render();
    void handleRealTimeInput();
    RenderWindow window;
    Texture gameTexture;
    Tank heroTank;
    Map map;
};

#endif // GAME_H
