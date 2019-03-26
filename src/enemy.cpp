#include "enemy.h"
namespace BattleCity {

Enemy::Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position) :
    Entity(position),
    size(SET::SIZE_TILE_TANK),
    direction(SET::Direction::DOWN)
{

}

void Enemy::changeDirectionMoving()
{
    switch(random(1,4))
    {
    case 1:
        direction = SET::Direction::LEFT;
        break;
    case 2:
        direction = SET::Direction::RIGHT;
        break;
    case 3:
        direction = SET::Direction::UP;
        break;
    case 4:
        direction = SET::Direction::DOWN;
        break;
    }
}

void Enemy::update(const sf::Time &elapsedTime)
{
    float dx = 0;
    float dy = 0;
    switch (direction)
    {
    case SET::Direction::LEFT:
        dx = -getSpeed();
        dy = 0;
        break;
    case SET::Direction::RIGHT:
        dx = getSpeed();
        dy = 0;
        break;
    case SET::Direction::UP:
        dx = 0;
        dy = -getSpeed();
        break;
    case SET::Direction::DOWN:
        dx = 0;
        dy = getSpeed();
        break;
    }
    move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
}

void Enemy::adaptEnemyPosition()
{
    sf::Vector2f position = adaptPosition();
    if ((utils::equalFloat(position.x, SET::WINDOW_WIDTH - size.x/2) && direction == SET::Direction::RIGHT)
            || (utils::equalFloat(position.x, size.x/2) && direction == SET::Direction::LEFT)
            || (utils::equalFloat(position.y, SET::WINDOW_HEIGHT - size.y/2) && direction == SET::Direction::DOWN)
            || (utils::equalFloat(position.y, size.y/2) && direction == SET::Direction::UP))
    {
        changeDirectionMoving();
    }
    setPosition(position);

}

SET::Direction Enemy::getDirection() const
{
    return direction;
}

void Enemy::setDirection(const SET::Direction &value)
{
    direction = value;
}
} //namespace BattleCity
