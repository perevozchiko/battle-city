#include "player.h"
#include <iostream>
Player::Player() :
    Tank ()
{

}

void Player::update(const sf::Time &elapsedTime)
{
        switch (getDir())
        {
        case Conf::Direction::LEFT:
            setDx(-getSpeed());
            setDy(0);
            break;
        case Conf::Direction::RIGHT:
            setDx(getSpeed());
            setDy(0);
            break;
        case Conf::Direction::UP:
            setDx(0);
            setDy(-getSpeed());
            break;
        case Conf::Direction::DOWN:
            setDx(0);
            setDy(getSpeed());
            break;
        }
        setSpeed(0);
        getSprite().move(getDx() * elapsedTime.asSeconds(), getDy() * elapsedTime.asSeconds());
}

void Player::handleRealTimeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        setDir(Conf::Direction::LEFT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setDir(Conf::Direction::RIGHT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        setDir(Conf::Direction::UP);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        setDir(Conf::Direction::DOWN);
    }
}

void Player::adaptPlayerPosition()
{
    setPosition(adaptPosition());
}

