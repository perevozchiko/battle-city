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

    Object(Conf::Type _type, sf::Texture& _texture, int _x, int _y, sf::Vector2i _offset, int _size);

    Direction getDir() const;
    void update(const sf::Time elapsedTime);
    void setDir(Direction _dir);
    void setSpeed(float _speed);
    void setPosition(const sf::Vector2f &value);

    sf::Vector2f getPosition() const;
    sf::Sprite getSprite() const;
    int getSize() const;

private:
    sf::Texture& texture;
    sf::Vector2f position;
    int size;
    sf::Sprite sprite;
    Direction dir;
    float speed;
    float dx;
    float dy;
    bool collisionDetect = false;
    sf::Vector2i offset;
    Conf::Type type;
};

#endif // TANK_H
