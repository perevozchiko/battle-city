#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>

enum class Direction
{
    LEFT,
    RIGHT,
    DOWN,
    UP
};

class Tank
{
public:
   Tank(sf::Texture& _texture, int _x, int _y, int _width, int _height);
   void update(const sf::Time& time);
   sf::Sprite getSprite() {return sprite;}


private:
   sf::Texture& texture;
   sf::Vector2i position;
   sf::Vector2i size;
   sf::Sprite sprite;
   Direction dir;

};

#endif // TANK_H
