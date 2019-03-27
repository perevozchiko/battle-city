#ifndef SET_H
#define SET_H
#include <SFML/Window/Event.hpp>
#include <vector>

namespace BattleCity {

namespace SET {

// Настройки OpenGL
const int MAJOR = 3;
const int MINOR = 0;
const int ANTIALIASING = 0;


// Настройки Window
const sf::String GAME_NAME = "Battle City";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT =  640;


// FPS
const float FPS_POS = 5.f;
const int FPS_FONT_SIZE = 12;

// Paths
const sf::String PATH_FONTS = "resources/fonts/vapor_trails_remixed.otf";
const sf::String PATH_IMAGES = "resources/images/sprite.bmp";
const sf::String PATH_MAPS = "resources/maps/";

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60);
const float TANK_SPEED = 70.f;
const sf::Vector2i SIZE_TILE_TANK = {28, 28};
const sf::Vector2i SIZE_TILE_MAP = {16, 16};

// Количество элементов на карте по высоте и ширине
const int MAP_WIDTH = WINDOW_WIDTH / SIZE_TILE_MAP.x;
const int MAP_HEIGHT = WINDOW_HEIGHT / SIZE_TILE_MAP.y;

//Позиция player в начале
const sf::Vector2f PLAYER_POSITION = {WINDOW_WIDTH/2 - 70.f, float(WINDOW_HEIGHT-SIZE_TILE_TANK.y-5)} ;


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
    Empty = 0,
    Brick,
    Concrete,
    Shrub,
    Ice,
    Water
};
} //namespace SET
} //namespace BattleCity
#endif // SET_H
