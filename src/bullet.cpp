#include "bullet.h"
namespace BattleCity {

Bullet::Bullet(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    direction(SET::Direction::UP),
    size(SET::SIZE_TILE_BULLET)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
}

Bullet::~Bullet()
{

}

SET::Direction Bullet::getDirection() const
{
    return direction;
}

void Bullet::setDirection(const SET::Direction &value)
{
    setSpeed(SET::BULLET_SPEED);
    direction = value;
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

void Bullet::update(const sf::Time &elapsedTime)
{
    int dx = 0;
    int dy = 0;
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

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

bool Bullet::getRemoved() const
{
    return removed;
}

void Bullet::setRemoved(bool value)
{
    removed = value;
}

SET::bulletType Bullet::getType() const
{
    return type;
}

void Bullet::setType(const SET::bulletType &value)
{
    type = value;
}

sf::IntRect Bullet::getGlobalRect() const
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
} //namespace BattleCity
