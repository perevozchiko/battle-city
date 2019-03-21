#ifndef TANK_H
#define TANK_H
#include <SFML/Graphics.hpp>

#include <conf.h>
#include <iostream>

class Entity
{
public:
    Entity();
    Entity(sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position);
    virtual ~Entity();

    void setOffset(const sf::Vector2i &value);
    sf::Vector2i getOffset() const;
    sf::Sprite& getSprite();

    void setPosition(const sf::Vector2f &value);
    void setPosition(const sf::Vector2i &value);
    sf::Vector2f getPosition() const;

    void setSprite(const sf::Sprite &value);
    sf::Vector2i getSize() const;

    virtual void update(const sf::Time &elapsedTime) = 0;

    sf::Texture getTexture() const;
   void setTextureRectange(sf::IntRect value);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    sf::Vector2f position;
};

#endif // TANK_H
