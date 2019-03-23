#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "set.h"
#include "tilemap.h"

namespace BattleCity {

/** @class
 *
 */
class Game
{
public:
    Game(const sf::String& name, const sf::ContextSettings& settings);

    void run();

private:
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void updateFPS(const sf::Time &elapsedTime);
    void render();
    void init();

    sf::RenderWindow window;
    //    Player player;


    //    sf::Texture gameTexture;

    //    std::vector<Enemy> enemies;

    std::vector<TileMap> tiles;


    sf::Font font;
    struct FPSInfo
    {
        sf::Time updateTime{sf::Time::Zero};
        int frame{0};
        sf::Text text;
    };
    FPSInfo fpsInfo;


    //    // Динамический массив сделать  int *testMap = new int[HEIGHTMAP];
    //    const static int HEIGHTMAP =  40;
    //    const static int WIDTHMAP = 50;
    //    //int *testMap = new int[HEIGHTMAP];
    //    sf::String testMap[HEIGHTMAP] =
    //    {
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                   *******************************",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "******************************                    ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "********************************************      ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  ",
    //        "                                                  "
    //    };


};
} //namespace BattleCity

#endif // GAME_H
