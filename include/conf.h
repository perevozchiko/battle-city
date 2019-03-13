#ifndef CONF_H
#define CONF_H
#include <SFML/Window/Event.hpp>
#include <string>

namespace Conf {

const int WindowWidth = 640;
const int WindowHeight = 480;
const sf::Time TimePerFrame = sf::seconds(1.0f/60.f);
const float TankSpeed = 3.0f;
const std::string GameName = "Battle City";
const int SizeTexture = 32;


}


#endif // CONF_H
