#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "settings.h"
#include "randomgen.h"

namespace BattleCity {

namespace utils {

/** @note http://realtimecollisiondetection.net/blog/?p=89
 *
 */
bool equalFloat(float x, float y);
std::vector<std::string> readFromFileMap(const int level);
sf::Vector2i setOffset(int type);
std::string getStringMap(sf::Vector2i map, int numString);
int charToInt(char ch);
sf::IntRect toIntRect(const sf::FloatRect &value);
sf::Vector2i getEnemyType(SETTINGS::EnemyType &value);
sf::RectangleShape createBorder(sf::Vector2i size, sf::Vector2i pos);
SETTINGS::PositionEnemy setStartPosition(int value = 0);

} //namespace Utils
} //namespace BattleCity
#endif // UTILS_H
