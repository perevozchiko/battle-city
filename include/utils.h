#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "set.h"
#include "player.h"

namespace BattleCity {

namespace utils {

/** @note http://realtimecollisiondetection.net/blog/?p=89
 *
 */
bool equalFloat(float x, float y);

std::vector<std::string> readFileMap(const int level);
sf::Vector2i setOffset(int type);
std::string getStringMap(sf::Vector2i map, int numString);
int charToInt(char ch);
std::ostream& operator<< (std::ostream &out, const Player &p);
void print(Player &p);
sf::IntRect toIntRect(const sf::FloatRect &value);

} //namespace Utils
} //namespace BattleCity
#endif // UTILS_H
