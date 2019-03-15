#ifndef PLAYER_H
#define PLAYER_H
#include "tank.h"

class Player : public Tank
{
public:
    Player();
    void adaptPlayerPosition();
    void update(const sf::Time& elapsedTime) override;
    void handleRealTimeInput();

private:

};

#endif // PLAYER_H
