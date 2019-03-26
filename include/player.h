#ifndef PLAYER_H
#define PLAYER_H
#include "tank.h"

namespace BattleCity {

/** @class
 *
 */
class Player : public Entity
{
public:
    Player() = delete;
    Player(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position);

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void handleRealTimeInput();
    void adaptPosition();
    sf::FloatRect getGlobalRect() const;


    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

    sf::Vector2i getSize() const;


private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SET::Direction direction;
};
} //namespace BattleCity
#endif // PLAYER_H
