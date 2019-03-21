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
    // Динамический массив сделать  int *testMap = new int[HEIGHTMAP];
    const static int HEIGHTMAP =  40;
    const static int WIDTHMAP = 50;
    //int *testMap = new int[HEIGHTMAP];
    sf::String testMap[HEIGHTMAP] =
    {
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                   *******************************",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "******************************                    ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "********************************************      ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  ",
        "                                                  "
    };

private:
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void render();
    void updateFPS(const sf::Time &elapsedTime);


    sf::RenderWindow window;
    Player player;


    sf::Texture gameTexture;

    std::vector<Enemy> enemies;
    std::vector<TileMap> tiles;

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
