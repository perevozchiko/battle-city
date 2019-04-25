#include "player.h"


namespace BattleCity {

Player::Player(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position):
    Entity(position),
    size(SETTINGS::SIZE_TILE_PLAYER),
    direction(SETTINGS::Direction::UP)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
    setObjectType(Entity::ObjectType::Player);
}

Player::~Player()
{

}

void Player::setDirection(const SETTINGS::Direction &_direction)
{

    setSpeed(SETTINGS::PLAYER_SPEED);
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

sf::Vector2i Player::getSize() const
{
    return size;
}

bool Player::isAlive() const
{
    return life;
}

void Player::setForRemove()
{
    life = false;
}

SETTINGS::Direction Player::getDirection() const
{
    return direction;
}

void Player::update(const sf::Time &elapsedTime)
{
    setMovement();

    if (!life)
    {
        setPosition(SETTINGS::PLAYER_POSITION);
        life = true;
    }

    setSpeed(0);
    move(movement.x * elapsedTime.asSeconds(), movement.y * elapsedTime.asSeconds());
    adaptPlayerPosition();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void Player::handleRealTimeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        setDirection(SETTINGS::Direction::LEFT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setDirection(SETTINGS::Direction::RIGHT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        setDirection(SETTINGS::Direction::UP);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        setDirection(SETTINGS::Direction::DOWN);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        shoot = true;
    }
    else
    {
        shoot = false;
    }
}

sf::IntRect Player::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r = utils::toIntRect(sprite.getGlobalBounds());
    r.left = pos.x - r.width/2;
    r.top = pos.y - r.height/2;
    return r;
}

void Player::adaptPlayerPosition()
{
    setPosition(adaptPosition());
}

void Player::setMovement()
{
    switch (direction)
    {
    case SETTINGS::Direction::LEFT:
        movement.x = -getSpeed();
        movement.y = 0;
        break;
    case SETTINGS::Direction::RIGHT:
        movement.x = getSpeed();
        movement.y = 0;
        break;
    case SETTINGS::Direction::UP:
        movement.x = 0;
        movement.y = -getSpeed();
        break;
    case SETTINGS::Direction::DOWN:
        movement.x = 0;
        movement.y = getSpeed();
        break;
    }
}

sf::Vector2f Player::getMovement() const
{
    return movement;
}

} //namespace BattleCity
