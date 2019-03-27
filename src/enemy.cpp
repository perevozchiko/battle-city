#include "enemy.h"
namespace BattleCity {

Enemy::Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position):
    Entity(position),
    size(SET::SIZE_TILE_TANK),
    direction(SET::Direction::DOWN)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
}

void Enemy::changeDirectionMoving()
{
    RandomGen random;

    switch(random(1,4))
    {
    case 1:
        if (direction != SET::Direction::LEFT)
        {
            setDirection(SET::Direction::LEFT);
        }
        else
        {
            changeDirectionMoving();
        }
        break;
    case 2:
        if (direction != SET::Direction::RIGHT)
        {
            setDirection(SET::Direction::RIGHT);
        }
        else
        {
            changeDirectionMoving();
        }
        break;
    case 3:
        if (direction != SET::Direction::UP)
        {
            setDirection(SET::Direction::UP);
        }
        else
        {
            changeDirectionMoving();
        }
        break;
    case 4:
        if (direction != SET::Direction::DOWN)
        {
            setDirection(SET::Direction::DOWN);
        }
        else
        {
            changeDirectionMoving();
        }
        break;
    }
}

void Enemy::setDirection(const SET::Direction &_direction)
{
    setSpeed(SET::TANK_SPEED);
    direction = _direction;
    switch (direction)
    {
    case SET::Direction::LEFT:
        setRotation(-90.0f);
        break;
    case SET::Direction::RIGHT:
        setRotation(90.0f);
        break;
    case SET::Direction::UP:
        setRotation(0.0f);
        break;
    case SET::Direction::DOWN:
        setRotation(180.0f);
        break;
    }
}

sf::FloatRect Enemy::getGlobalRect() const
{
    auto pos = getPosition();
    auto r = sprite.getGlobalBounds();
    r.left = pos.x - r.width/2;
    r.top = pos.y - r.height/2;
    return r;
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

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Enemy::adaptEnemyPosition()
{
    sf::Vector2f pos = adaptPosition();

    if ((utils::equalFloat(pos.x, SET::WINDOW_WIDTH - size.x/2) && direction == SET::Direction::RIGHT)
            || (utils::equalFloat(pos.x, size.x/2) && direction == SET::Direction::LEFT)
            || (utils::equalFloat(pos.y, SET::WINDOW_HEIGHT - size.y/2) && direction == SET::Direction::DOWN)
            || (utils::equalFloat(pos.y, size.y/2) && direction == SET::Direction::UP))
    {
        changeDirectionMoving();
    }
    setPosition(pos);
}

sf::Sprite Enemy::getSprite() const
{
    return sprite;
}

SET::Direction Enemy::getDirection() const
{
    return direction;
}

} //namespace BattleCity
