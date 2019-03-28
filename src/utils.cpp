#include "utils.h"

namespace BattleCity {

namespace utils {

bool equalFloat(float x, float y)
{
    float maxXYOne = std::max({1.0f, std::fabs(x), std::fabs(y)});
    return std::fabs(x - y) <= std::numeric_limits<float>::epsilon()*maxXYOne;
}

std::vector<std::string> readFileMap(const int level)
{
    std::vector<std::string> map;
    std::string levelStr = std::to_string(level);
    std::string path = SET::PATH_MAPS + levelStr;
    std::ifstream fileMap(path);

    if (!fileMap)
    {
        std::cerr << "Невозможно открыть файл" << std::endl;
        exit(1);
    }
    std::string str;
    while(fileMap)
    {
        str = "";
        std::getline(fileMap, str);
        if (!fileMap.eof())
        {
            map.push_back(str);
        }
    }
    return map;
}

sf::Vector2i setOffset(int type)
{
    switch (static_cast<SET::Tile>(type))
    {
    case SET::Tile::Empty:
        return {1000, 1000};

    case SET::Tile::Brick:
        return {0, 256};

    case SET::Tile::Concrete:
        return {0, 272};


    case SET::Tile::Shrub:
        return {0, 304};

    case SET::Tile::Ice:
        return {0, 288};

    case SET::Tile::Water:
        return {0, 320};
    }
    return {0,0};
}

int charToInt(char ch)
{
    return ch - '0';
}

//std::ostream& operator<< (std::ostream &out, const Player &p)
//{
//    out << p.getPosition().x;
//    return out;
//}

//void print(Player &player)
//{
//    auto p = player.getGlobalRect();
//    std::cout << "Player - Нижняя левая : [ "<< std::round(p.top + p.height) << " " << std::round(p.left) << " ]" << std::endl;
//    std::cout << "Player - Верхняя левая : [ "<< std::round(p.top) << " " << std::round(p.left) << " ]" << std::endl;

//}

sf::IntRect toIntRect(const sf::FloatRect &value)
{
    sf::IntRect r;
    r.top = static_cast<int>(std::round(value.top));
    r.left = static_cast<int>(std::round(value.left));
    r.width = static_cast<int>(std::round(value.width));
    r.height = static_cast<int>(std::round(value.height));
    return r;
}

} //namespace utils
} //namespace BattleCity
