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
    void adaptPosition(Object &obj);
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void render();
    void handleRealTimeInput();
    void enemyDirectionMoving();
    void updateFPS(const sf::Time &elapsedTime);
    void updateEnemy(const sf::Time &elapseTime);


    sf::RenderWindow window;
    sf::Texture gameTexture;
    Object player;
    std::vector<Object> enemies;


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
