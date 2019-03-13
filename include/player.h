#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include <conf.h>

class Player
{
public:
    enum class Direction
    {
        NO,
        LEFT,
        RIGHT,
        DOWN,
        UP
    };

    Player(sf::Texture& _texture, int _x, int _y, int _width, int _height);


    sf::Sprite& getSprite() {return sprite;}
    Direction getDir() {return dir;}
    sf::Vector2f getSize() {return size;}
    void update();
    void setDir(Direction _dir);
    void setSpeed(float _speed);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &value);

    sf::Vector2f getHalfSize() const;

    void setHalfSize(const sf::Vector2f &value);

private:
    sf::Texture& texture;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f halfSize;
    sf::Sprite sprite;
    Direction dir;
    float speed;
    float dx;
    float dy;
    bool collisionDetect = false;
};

#endif // TANK_H
