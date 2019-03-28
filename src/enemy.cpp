#include "enemy.h"
namespace BattleCity {

Enemy::Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position):
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

    switch(random(1,2))
    {
    case 1:
        setDirection(SET::Direction::LEFT);
        break;

    case 2:
        setDirection(SET::Direction::RIGHT);
        break;

    case 3:
        setDirection(SET::Direction::UP);
        break;

    case 4:
        setDirection(SET::Direction::DOWN);
        break;
    }
}

void Enemy::setDirection(const SET::Direction &_direction)
{
    setSpeed(SET::ENEMY_SPEED);
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

sf::IntRect Enemy::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r =
    {
        int(std::round(sprite.getGlobalBounds().left)),
        int(std::round(sprite.getGlobalBounds().top)),
        int(std::round(sprite.getGlobalBounds().width)),
        int(std::round(sprite.getGlobalBounds().height))
    };
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
    if (getCollisionDetected() == false)
    {
        move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
    }
    else
    {
        move(0,0);
        setCollisionDetected(false);
    }
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Enemy::adaptEnemyPosition()
{
    sf::Vector2i pos = adaptPosition();

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
