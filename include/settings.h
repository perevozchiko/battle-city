#ifndef SET_H
#define SET_H
#include <SFML/Window/Event.hpp>
#include <vector>

namespace BattleCity {

namespace SETTINGS {

// Настройки OpenGL
const int MAJOR = 3;
const int MINOR = 0;
const int ANTIALIASING = 0;


// Настройки Window
const sf::String GAME_NAME = "Battle City";
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT =  448;

// FPS
const float FPS_POS = 5.f;
const int FPS_FONT_SIZE = 12;

// Paths
const sf::String PATH_FONTS = "resources/fonts/vapor_trails_remixed.otf";
const sf::String PATH_IMAGES = "resources/images/sprite.bmp";
const sf::String PATH_MAPS = "resources/maps/";

const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60);

const int MAP_OFFSET_LEFT = 32;
const int MAP_OFFSET_TOP = 16;
const int MAP_SIZE = 416;
const int COUNT_TILES_MAP = 26;
const int ENEMY_SPEED = 70;
const int PLAYER_SPEED = 120;
const int BULLET_SPEED = 500;
const sf::Vector2i SIZE_TILE_PLAYER = {26, 26};
const sf::Vector2i SIZE_TILE_ENEMY = {26, 30};
const int MAX_NUM_ENEMY = 4;
const int ALL_ENEMY_ROUND = 20;
const sf::Vector2i SIZE_TILE_BULLET = {6, 8};
const int SIZE_TILE_MAP = 16;
//Позиция player в начале добавить размер базы
const sf::Vector2i PLAYER_POSITION = {WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT-SIZE_TILE_PLAYER.y/2} ;


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



enum class bulletType {
    Player,
    Enemy
};
} //namespace SET
} //namespace BattleCity
#endif // SET_H
