#include "bullet.h"
namespace BattleCity {

Bullet::Bullet(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    direction(SET::Direction::UP),
    size(SET::SIZE_TILE_BULLET),
    visible(true)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
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

bool Bullet::getVisible() const
{
    return visible;
}

void Bullet::setVisible(bool value)
{
    visible = value;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
        states.transform *= getTransform();
        target.draw(sprite, states);
}

} //namespace BattleCity
