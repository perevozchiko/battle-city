#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "object.h"
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
    void enemyMoving();
    sf::RenderWindow window;
    sf::Texture gameTexture;
    Object player;
    Object enemy;
    void updateFPS(const sf::Time &elapsedTime);

    sf::Font font;
    struct FPSInfo
        {
            sf::Time updateTime{sf::Time::Zero};
            int frame{0};
            sf::Text text;
        };
    FPSInfo fpsInfo;

};

int getRandomNumber(int min, int max);

#endif // GAME_H
