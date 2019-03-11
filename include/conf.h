#ifndef CONF_H
#define CONF_H
#include <SFML/Window/Event.hpp>
#include <string>

namespace Conf {

const float WINDOW_WIDTH = 640.0f;
const float WINDOW_HEIGHT = 480.0f;
const sf::Time TIME_PER_FRAME = sf::seconds(1.0f/30.f);
const int SPEED = 100;
const std::string GAME_NAME = "Battle City";
const int SIZE_TEXTURE = 32;


}


#endif // CONF_H
