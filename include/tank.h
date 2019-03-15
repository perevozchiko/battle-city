#ifndef TANKS_H
#define TANKS_H
#include "entity.h"

class Tank : public Entity
{
public:
    Tank();

    enum class Direction
    {
        LEFT = 0,
        RIGHT,
        DOWN,
        UP
    };

    Direction getDir() const;
    void setDir(Direction _dir);
    void setSpeed(float _speed);


private:
    Direction dir;
    float speed;
    float dx;
    float dy;
    bool collisionDetect = false;
    Conf::Type type;
    sf::Texture gameTexture;
};

#endif // TANKS_H
