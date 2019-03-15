#include "include/tank.h"

Tank::Tank() :
    Entity (gameTexture, {0, 0}, Conf::SizeTexture, {Conf::WindowWidth/2, 0})
{
    gameTexture.loadFromFile("resources/images/sprite.bmp");
}






//void Game::adaptPosition(Entity &obj)
//{
//    sf::Vector2f position = obj.getPosition();

//    position.x = std::max(position.x, static_cast<float>(obj.getSize()/2));
//    position.x = std::min(position.x, static_cast<float>(Conf::WindowWidth - obj.getSize()/2));

//    position.y = std::max(position.y, static_cast<float>(obj.getSize()/2));
//    position.y = std::min(position.y, static_cast<float>(Conf::WindowHeight - obj.getSize()/2));

//    obj.setPosition(position);
//}

//void Entity::update(const sf::Time elapsedTime)
//{
//    switch (dir)
//    {
//    case Direction::LEFT:
//        dx = -speed;
//        dy = 0;
//        break;
//    case Direction::RIGHT:
//        dx = speed;
//        dy = 0;
//        break;
//    case Direction::UP:
//        dx = 0;
//        dy = -speed;
//        break;
//    case Direction::DOWN:
//        dx = 0;
//        dy = speed;
//        break;
//    }
//    if (type == Conf::Type::Player)
//        speed = 0;
//    sprite.move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
//}

//void Entity::setDir(Direction _dir)
//{
//    speed = Conf::TankSpeed;
//    dir = _dir;
//    switch (dir)
//    {
//    case Entity::Direction::LEFT:
//        sprite.setRotation(-90.0f);
//        break;
//    case Entity::Direction::RIGHT:
//        sprite.setRotation(90.0f);
//        break;
//    case Entity::Direction::UP:
//        sprite.setRotation(0.0f);
//        break;
//    case Entity::Direction::DOWN:
//        sprite.setRotation(180.0f);
//        break;
//    }
//}

//Entity::Direction Entity::getDir() const
//{
//    return dir;
//}

//void Entity::setSpeed(float _speed)
//{
//    speed = _speed;
//}


