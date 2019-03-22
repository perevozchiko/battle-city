#include "include/tank.h"
namespace BattleCity {
//Tank::Tank() :
//Entity ({0, 0}, SET::SizeTileTank, {SET::WINDOW_WIDTH/2, static_cast<float> (SET::WINDOW_HEIGHT - SET::SizeTileTank.y/2)})
//{
//    getSprite().setOrigin(getSize().x/2, getSize().y/2);
//}

//Tank::Tank(sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position) :
//Entity (_offset, _size, _position)
//{
//    getSprite().setOrigin(getSize().x/2, getSize().y/2);
//}

//void Tank::setDir(SET::Direction _dir)
//{
//    speed = SET::TankSpeed;
//    dir = _dir;
//    switch (dir)
//    {
//    case SET::Direction::LEFT:
//        getSprite().setRotation(-90.0f);
//        break;
//    case SET::Direction::RIGHT:
//        getSprite().setRotation(90.0f);
//        break;
//    case SET::Direction::UP:
//        getSprite().setRotation(0.0f);
//        break;
//    case SET::Direction::DOWN:
//        getSprite().setRotation(180.0f);
//        break;
//    }
//}

//SET::Direction Tank::getDir() const
//{
//    return dir;
//}

//void Tank::setSpeed(float _speed)
//{
//    speed = _speed;
//}

//float Tank::getSpeed() const
//{
//    return speed;
//}

//float Tank::getDx() const
//{
//    return dx;
//}

//void Tank::setDx(float value)
//{
//    dx = value;
//}

//float Tank::getDy() const
//{
//    return dy;
//}

//void Tank::setDy(float value)
//{
//    dy = value;
//}

//sf::Vector2f Tank::adaptPosition()
//{
//    sf::Vector2f position = getPosition();

//    position.x = std::max(position.x, static_cast<float>(getSize().x/2));
//    position.x = std::min(position.x, static_cast<float>(SET::WINDOW_WIDTH - getSize().x/2));

//    position.y = std::max(position.y, static_cast<float>(getSize().y/2));
//    position.y = std::min(position.y, static_cast<float>(SET::WINDOW_HEIGHT - getSize().y/2));

//    return position;
//}

} //namespace BattleCity
