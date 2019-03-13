#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include <conf.h>

class Object
{
public:
    enum class Direction
    {
        LEFT,
        RIGHT,
        DOWN,
        UP
    };

    Object(sf::Texture& _texture, int _x, int _y, int _width, int _height);

    Direction getDir() const;
    void update(const sf::Time elapsedTime);
    void setDir(Direction _dir);
    void setSpeed(float _speed);
    void setPosition(const sf::Vector2f &value);

    sf::Vector2f getPosition() const;
    sf::Sprite getSprite() const;
    sf::Vector2i getSize() const;

private:
    sf::Texture& texture;
    sf::Vector2f position;
    sf::Vector2i size;
    sf::Sprite sprite;
    Direction dir;
    float speed;
    float dx;
    float dy;
    bool collisionDetect = false;
};

#endif // TANK_H
