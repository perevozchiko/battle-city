#ifndef CONF_H
#define CONF_H
#include <SFML/Window/Event.hpp>
#include <string>

namespace Conf {

const std::string PathFonts = "resources/fonts/vapor_trails_remixed.otf";
const std::string PathImages = "resources/images/sprite.bmp";

const static int WindowWidth = 800;
const static int WindowHeight =  640;
const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
const float TankSpeed = 40.f;
const std::string GameName = "Battle City";
const sf::Vector2i SizeTileTank = {32, 32};
const sf::Vector2i SizeTileMap = {16, 16};

enum class Type
{
    Player = 0,
    Enemy
};


enum class EnemyType
{
    Simple = 0,
    QuickMoving,
    QuickFiring,
    LongLived
};

enum class PlayerType
{
    Small = 0,
    Light,
    Medium,
    Heavy,
    SuperHeavy
};

enum class Direction
{
    LEFT = 0,
    RIGHT,
    DOWN,
    UP
};

enum class Tile {
    Brick = 0,
    Concrete,
    Shrub,
    Ice,
    Water
};

}
#endif // CONF_H
