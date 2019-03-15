#include "enemy.h"

Enemy::Enemy():
    Tank ()
{

}

void Enemy::changeDirectionMoving()
{
    int random = gen(1,4);
    switch(random)
    {
    case 1:
        setDir(Conf::Direction::LEFT);
        break;
    case 2:
        setDir(Conf::Direction::RIGHT);
        break;
    case 3:
        setDir(Conf::Direction::UP);
        break;
    case 4:
        setDir(Conf::Direction::DOWN);
        break;
    }
}

void Enemy::update(const sf::Time &elapsedTime)
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
    getSprite().move(getDx() * elapsedTime.asSeconds(), getDy() * elapsedTime.asSeconds());
}

void Enemy::adaptEnemyPosition()
{
    sf::Vector2f position = adaptPosition();
    if ((Utils::equalFloat(position.x, Conf::WindowWidth - getSize().x/2) && getDir() == Conf::Direction::RIGHT)
            || (Utils::equalFloat(position.x, getSize().x/2) && getDir() == Conf::Direction::LEFT)
            || (Utils::equalFloat(position.y, Conf::WindowHeight - getSize().y/2) && getDir() == Conf::Direction::DOWN)
            || (Utils::equalFloat(position.y, getSize().y/2) && getDir() == Conf::Direction::UP))
    {
        changeDirectionMoving();
    }
    setPosition(position);

}
