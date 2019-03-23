#include "enemy.h"
namespace BattleCity {
//Enemy::Enemy():
//    Tank ({0, 426}, {32, 32}, {0, 0})
//{

//}

//void Enemy::changeDirectionMoving()
//{
//    RandomGen gen;
//    int random = gen(1,4);
//    switch(random)
//    {
//    case 1:
//        setDir(SET::Direction::LEFT);
//        break;
//    case 2:
//        setDir(SET::Direction::RIGHT);
//        break;
//    case 3:
//        setDir(SET::Direction::UP);
//        break;
//    case 4:
//        setDir(SET::Direction::DOWN);
//        break;
//    }
//}

//void Enemy::update(const sf::Time &elapsedTime)
//{
//    switch (getDir())
//    {
//    case SET::Direction::LEFT:
//        setDx(-getSpeed());
//        setDy(0);
//        break;
//    case SET::Direction::RIGHT:
//        setDx(getSpeed());
//        setDy(0);
//        break;
//    case SET::Direction::UP:
//        setDx(0);
//        setDy(-getSpeed());
//        break;
//    case SET::Direction::DOWN:
//        setDx(0);
//        setDy(getSpeed());
//        break;
//    }
//    getSprite().move(getDx() * elapsedTime.asSeconds(), getDy() * elapsedTime.asSeconds());
//}

//void Enemy::adaptEnemyPosition()
//{
//    sf::Vector2f position = adaptPosition();
//    if ((utils::equalFloat(position.x, SET::WINDOW_WIDTH - getSize().x/2) && getDir() == SET::Direction::RIGHT)
//            || (utils::equalFloat(position.x, getSize().x/2) && getDir() == SET::Direction::LEFT)
//            || (utils::equalFloat(position.y, SET::WINDOW_HEIGHT - getSize().y/2) && getDir() == SET::Direction::DOWN)
//            || (utils::equalFloat(position.y, getSize().y/2) && getDir() == SET::Direction::UP))
//    {
//        changeDirectionMoving();
//    }
//    setPosition(position);

//}
} //namespace BattleCity
