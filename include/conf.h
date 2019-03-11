#ifndef CONF_H
#define CONF_H
#include <SFML/Window/Event.hpp>
#include <string>

namespace Conf {

const int WINDOW_WIDTH = 640.0f;
const int WINDOW_HEIGHT = 480.0f;
const sf::Time TIME_PER_FRAME = sf::seconds(1.0f/60.f);
const int SPEED = 2;
const std::string GAME_NAME = "Battle City";
const int SIZE_TEXTURE = 32;


}


#endif // CONF_H
