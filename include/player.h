#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace BattleCity {

/** @class
 *
 */
class Player : public Entity
{
public:
    Player() = delete;
    Player(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    ~Player() override;

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void handleRealTimeInput();
    void adaptPlayerPosition();
    sf::IntRect getGlobalRect() const;


    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

    sf::Vector2i getSize() const;
    bool shoot{false};

    bool getRemoved() const;
    void setRemoved(bool value);

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SET::Direction direction;
    bool removed{false};
};
} //namespace BattleCity
#endif // PLAYER_H
