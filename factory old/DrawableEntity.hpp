#ifndef DRAWABLE_ENTITY_HPP
#define DRAWABLE_ENTITY_HPP

#include <SFML/Graphics.hpp>

class DrawableEntity {
public:
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void move(const sf::Vector2f& offset) = 0;
    virtual bool contains(const sf::Vector2f& point) const = 0;
    virtual ~DrawableEntity() = default;
    virtual std::string getType() const = 0;
};

#endif // DRAWABLE_ENTITY_HPP