#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
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

    Sprite& getSprite() {return sprite;}
    Direction getDir() {return dir;}
    void update(Time timeMove);
    void setDir(Direction dir);
    void setSpeed(float speed);

private:
    Texture& texture;
    Vector2i position;
    Vector2i size;
    Sprite sprite;
    Direction dir;
    float speed;
    float dx;
    float dy;
};

#endif // TANK_H
