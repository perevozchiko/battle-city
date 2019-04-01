#include "enemy.h"
namespace BattleCity {

Enemy::Enemy()
{

}

Enemy::Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position):
    Entity(position),
    size(SETTINGS::SIZE_TILE_ENEMY),
    direction(SETTINGS::Direction::DOWN)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
}

Enemy::~Enemy()
{

}

void Enemy::changeDirectionMoving()
{
    RandomGen random;

    switch(random(1,4))
    {
    case 1:
        setDirection(SETTINGS::Direction::LEFT);
        break;

    case 2:
        setDirection(SETTINGS::Direction::RIGHT);
        break;

    case 3:
        setDirection(SETTINGS::Direction::UP);
        break;

    case 4:
        setDirection(SETTINGS::Direction::DOWN);
        break;
    }
}

void Enemy::setDirection(const SETTINGS::Direction &_direction)
{
    setSpeed(SETTINGS::ENEMY_SPEED);
    direction = _direction;
    switch (direction)
    {
    case SETTINGS::Direction::LEFT:
        setRotation(-90.0f);
        break;
    case SETTINGS::Direction::RIGHT:
        setRotation(90.0f);
        break;
    case SETTINGS::Direction::UP:
        setRotation(0.0f);
        break;
    case SETTINGS::Direction::DOWN:
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
    case SETTINGS::Direction::LEFT:
        dx = -getSpeed();
        dy = 0;
        break;
    case SETTINGS::Direction::RIGHT:
        dx = getSpeed();
        dy = 0;
        break;
    case SETTINGS::Direction::UP:
        dx = 0;
        dy = -getSpeed();
        break;
    case SETTINGS::Direction::DOWN:
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

    if ((utils::equalFloat(pos.x, SETTINGS::WINDOW_WIDTH - size.x/2) && direction == SETTINGS::Direction::RIGHT)
            || (utils::equalFloat(pos.x, size.x/2) && direction == SETTINGS::Direction::LEFT)
            || (utils::equalFloat(pos.y, SETTINGS::WINDOW_HEIGHT - size.y/2) && direction == SETTINGS::Direction::DOWN)
            || (utils::equalFloat(pos.y, size.y/2) && direction == SETTINGS::Direction::UP))
    {
        changeDirectionMoving();
    }
    setPosition(pos);
}

sf::Sprite Enemy::getSprite() const
{
    return sprite;
}

SETTINGS::Direction Enemy::getDirection() const
{
    return direction;
}

void Enemy::setTexture(const sf::Texture &texture, sf::Vector2i offset)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, SETTINGS::SIZE_TILE_ENEMY));
    sprite.setOrigin(SETTINGS::SIZE_TILE_ENEMY.x/2, SETTINGS::SIZE_TILE_ENEMY.y/2);
}

int Enemy::getRemoved() const
{
    return removed;
}

void Enemy::setRemoved(int value)
{
    removed = value;
}
} //namespace BattleCity
