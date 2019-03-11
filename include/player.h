#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
#include <conf.h>
using namespace sf;

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

    Player(Texture& _texture, int _x, int _y, int _width, int _height);

    bool collisionDetect = false;
    Sprite& getSprite() {return sprite;}
    Direction getDir() {return dir;}
    Vector2i getSize() {return size;}
    void update(Time timeMove);
    void setDir(Direction _dir);
    void setSpeed(float _speed);
    Vector2f getPosition() const;
    void setPosition(const Vector2f &value);


private:
    Texture& texture;
    Vector2f position;
    Vector2i size;
    Sprite sprite;
    Direction dir;
    float speed;
    float dx;
    float dy;
};

#endif // TANK_H
