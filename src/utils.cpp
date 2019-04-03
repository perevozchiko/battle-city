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
    switch (static_cast<SETTINGS::Tile>(type))
    {
    case SETTINGS::Tile::Empty:
        return {1000, 1000};

    case SETTINGS::Tile::Brick:
        return {0, 256};

    case SETTINGS::Tile::Concrete:
        return {0, 272};


    case SETTINGS::Tile::Shrub:
        return {0, 304};

    case SETTINGS::Tile::Ice:
        return {0, 288};

    case SETTINGS::Tile::Water:
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

sf::Vector2i getEnemyType(const int &value)
{
    SETTINGS::EnemyType i = static_cast<SETTINGS::EnemyType>(value);
    switch(i)
    {
    case SETTINGS::EnemyType::Simple:
        return {3, 426};// size 26x30
    case SETTINGS::EnemyType::LongLived:
        return {3, 810};// size 26x30
    case SETTINGS::EnemyType::QuickFiring:
        return {3, 682};// size 26x30
    case SETTINGS::EnemyType::QuickMoving:
        return {3, 554};// size 26x30
    }
}

} //namespace utils
} //namespace BattleCity
