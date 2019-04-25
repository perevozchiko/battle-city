#include "enemy.h"
namespace BattleCity {

int Enemy::count = SETTINGS::ALL_ENEMY_ROUND;

Enemy::Enemy(const sf::Texture &texture, SETTINGS::EnemyType _type, SETTINGS::PositionEnemy startPosition) :
    size(SETTINGS::SIZE_TILE_ENEMY),
    direction(SETTINGS::Direction::UP),
    type(_type)
{
    sf::Vector2i offset = getOffset(type);
    setTexture(texture, offset);
    setPosition(getStartPosition(startPosition));
    setObjectType(Entity::ObjectType::Enemy);
    count--;
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

    if (((pos.x >= (SETTINGS::MAP_WIDTH - size.x/2)) && (direction == SETTINGS::Direction::RIGHT))
            || ((pos.x <= (SETTINGS::MAP_LEFT + size.x/2)) && (direction == SETTINGS::Direction::LEFT))
            || ((pos.y >= (SETTINGS::MAP_HEIGHT - size.y/2)) && (direction == SETTINGS::Direction::DOWN))
            || ((pos.y <= (SETTINGS::MAP_TOP + size.y/2)) && (direction == SETTINGS::Direction::UP)))
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

sf::Vector2i Enemy::getStartPosition(SETTINGS::PositionEnemy _startPosition)
{
    sf::Vector2i startPosition;
    startPosition.y = SETTINGS::SIZE_TILE_ENEMY.y/2 + SETTINGS::MAP_TOP;
    switch (_startPosition)
    {
    case SETTINGS::PositionEnemy::LeftCorner:
        startPosition.x = SETTINGS::SIZE_TILE_ENEMY.x/2 + SETTINGS::MAP_LEFT;
        break;

    case SETTINGS::PositionEnemy::Center:
        startPosition.x = SETTINGS::SIZE_TILE_ENEMY.x/2 + SETTINGS::MAP_LEFT + SETTINGS::MAP_SIZE / 2;
        break;

    case SETTINGS::PositionEnemy::RightCorner:
        startPosition.x = SETTINGS::MAP_LEFT + SETTINGS::MAP_SIZE - SETTINGS::SIZE_TILE_ENEMY.x/2;
        break;
    }

    return startPosition;
}

sf::Vector2i Enemy::getOffset(SETTINGS::EnemyType &value)
{
    sf::Vector2i offset;
    switch(value)
    {
    case SETTINGS::EnemyType::Simple:
        offset = {3, 426};// size 26x30
        break;
    case SETTINGS::EnemyType::LongLived:
        offset = {3, 810};// size 26x30
        break;
    case SETTINGS::EnemyType::QuickFiring:
        offset = {3, 682};// size 26x30
        break;
    case SETTINGS::EnemyType::QuickMoving:
        offset = {3, 554};// size 26x30
        break;
    }
    return offset;
}

int Enemy::getCount()
{
    return count;
}

} //namespace BattleCity
