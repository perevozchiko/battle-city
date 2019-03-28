#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "set.h"
#include "tile.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"

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

    sf::RenderWindow window;
    sf::Texture texture;
    Player player;

    Enemy enemy;
    //std::vector<Enemy> enemies;

    std::vector<Tile> tiles;

    sf::Font font;
    struct FPSInfo
    {
        sf::Time updateTime{sf::Time::Zero};
        int frame{0};
        sf::Text text;
    };
    FPSInfo fpsInfo;

    RandomGen random;
};
} //namespace BattleCity

#endif // GAME_H
