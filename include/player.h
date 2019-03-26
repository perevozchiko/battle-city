#ifndef PLAYER_H
#define PLAYER_H
#include "tank.h"
namespace BattleCity {

/** @class
 *
 */
class Player
{
public:
    Player() = delete;
    Player(sf::Vector2i _offset, const sf::Texture &texture);

    void update(const sf::Time& elapsedTime);
    void handleRealTimeInput();

    float getSpeed() const;
    void setSpeed(float value);

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &value);

    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

    sf::Vector2i getOffset() const;
    void setOffset(const sf::Vector2i &value);

    sf::Sprite& getSprite();
    void setSprite(const sf::Sprite &value);

    sf::Vector2i getSize() const;
    void setSize(const sf::Vector2i &value);

    void adaptPosition();

private:
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    sf::Vector2f position;
    float speed;
    SET::Direction direction;

};
} //namespace BattleCity
#endif // PLAYER_H
