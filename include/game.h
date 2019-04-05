#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "settings.h"
#include "tile.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "base.h"

#include <memory>

namespace BattleCity {

/** @class
 *
 */
class Game
{
public:
    Game(const sf::String& name, const sf::ContextSettings& settings);
    ~Game();

    void run();

private:
    void processEvents();
    void update(const sf::Time &elapsedTime);
    void updateFPS(const sf::Time &elapsedTime);
    void render();

    sf::RenderWindow window;
    sf::Texture texture;
    Player player;
    Base base;
    sf::Text enemyCount;

    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<sf::RectangleShape> borders;

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
