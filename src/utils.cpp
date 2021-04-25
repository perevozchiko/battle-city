#include "utils.h"

namespace BattleCity {

namespace utils {

bool equalFloat(float x, float y)
{
    float maxXYOne = std::max({1.0f, std::fabs(x), std::fabs(y)});
    return std::fabs(x - y) <= std::numeric_limits<float>::epsilon()*maxXYOne;
}

std::vector<std::string> readFromFileMap(const int level)
{
    std::vector<std::string> map;
    std::string levelStr = std::to_string(level);
    std::string path = SETTINGS::PATH_MAPS + levelStr;
    std::ifstream fileMap(path);

    if (!fileMap)
    {
        std::cerr << "Невозможно открыть файл" << std::endl;
        exit(1);
    }
    std::string str;
    while(true)
    {
        str = "";
        std::getline(fileMap, str);
        if (fileMap.eof())
        {
            break;
        }
        map.push_back(str);
    }
    return map;
}

sf::Vector2i setOffset(int type)
{
    switch (static_cast<SETTINGS::TileType>(type))
    {
    case SETTINGS::TileType::Empty:
        return {1000, 1000};

    case SETTINGS::TileType::Brick:
        return {0, 256};

    case SETTINGS::TileType::Concrete:
        return {0, 272};

    case SETTINGS::TileType::Shrub:
        return {0, 304};

    case SETTINGS::TileType::Ice:
        return {0, 288};

    case SETTINGS::TileType::Water:
        return {0, 320};
    }
    return {0,0};
}

int charToInt(char ch)
{
    return ch - '0';
}

sf::IntRect toIntRect(const sf::FloatRect &value)
{
    sf::IntRect r;
    r.top = static_cast<int>(std::round(value.top));
    r.left = static_cast<int>(std::round(value.left));
    r.width = static_cast<int>(std::round(value.width));
    r.height = static_cast<int>(std::round(value.height));
    return r;
}



sf::RectangleShape createBorder(sf::Vector2i size, sf::Vector2i pos)
{
    sf::RectangleShape border({static_cast<float>(size.x), static_cast<float>(size.y)});
    border.setPosition(pos.x, pos.y);
    sf::Color color(116, 116, 116);
    border.setFillColor(color);
    return border;
}

SETTINGS::PositionEnemy setStartPosition(int value)
{
    int position;
    if (!value)
    {
        RandomGen rand;
        position = rand(1,3);
    }
    else
    {
        position = value;
    }
    return static_cast<SETTINGS::PositionEnemy>(position);
}

} //namespace utils
} //namespace BattleCity
