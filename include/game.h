#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>

#include <SFML/Window/Event.hpp>

#include "player.h"
#include "enemy.h"
#include "tilemap.h"


class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void render();
    void updateFPS(const sf::Time &elapsedTime);

    sf::RenderWindow window;
    sf::Texture gameTexture;
    Player player;
    std::vector<Enemy> enemies;




    sf::Font font;
    struct FPSInfo
    {
        sf::Time updateTime{sf::Time::Zero};
        int frame{0};
        sf::Text text;
    };
    FPSInfo fpsInfo;
};


#endif // GAME_H
