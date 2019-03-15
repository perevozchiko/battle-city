#ifndef CONF_H
#define CONF_H
#include <SFML/Window/Event.hpp>
#include <string>

namespace Conf {

const int WindowWidth = 800;
const int WindowHeight = 600;
const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
const float TankSpeed = 30.f;
const std::string GameName = "Battle City";
const sf::Vector2i SizeTexture = {32, 32};

enum class Type {
    Player,
    Enemy
};

enum class EnemyType{
    Simple = 0,
    QuickMoving,
    QuickFiring,
    LongLived
};

enum class PlayerType{
    Small = 0,
    Light,
    Medium,
    Heavy,
    SuperHeavy
};

}
#endif // CONF_H
