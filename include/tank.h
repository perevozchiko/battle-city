#ifndef TANKS_H
#define TANKS_H
#include "entity.h"

class Tank : public Entity
{
public:
    Tank();
    Tank(sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position);

    sf::Vector2f adaptPosition();

    Conf::Direction getDir() const;
    void setDir(Conf::Direction _dir);

    void setSpeed(float _speed);
    float getSpeed() const;

    float getDx() const;
    void setDx(float value);

    float getDy() const;
    void setDy(float value);



private:
    Conf::Direction dir;
    float speed;
    float dx;
    float dy;
    bool collisionDetect = false;
    Conf::Type type;
    sf::Texture gameTexture;
};

#endif // TANKS_H
