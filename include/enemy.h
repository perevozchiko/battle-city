#ifndef ENEMY_H
#define ENEMY_H
#include "tank.h"
#include "randomgen.h"
#include "utils.h"

class Enemy : public Tank
{
public:
    Enemy();
    void changeDirectionMoving();
    void update(const sf::Time& elapsedTime) override;
    void adaptEnemyPosition();

private:
};
#endif // ENEMY_H
