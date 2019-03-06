#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Tank
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

    Tank(Texture& _texture, int _x, int _y, int _width, int _height);

    Sprite& getSprite() {return sprite;}
    Direction getDir() {return dir;}
    void update();
    void setDir(Direction dir);

private:
    Texture& texture;
    Vector2i position;
    Vector2i size;
    Sprite sprite;
    Direction dir;
    float speed;
};

#endif // TANK_H
