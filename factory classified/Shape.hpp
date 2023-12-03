#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "DrawableEntity.hpp"

struct Shape : public DrawableEntity {
    std::string type;
    sf::Vector2f position;
    sf::Vector2f end; // Second point for lines and rectangles
    sf::Color color;
    std::string textureFile;
    sf::Vector2f scale;
    bool isDragging = false;
    sf::Vector2f size;

    // Implementing methods from the base class
    void draw(sf::RenderWindow& window) const override;
    void move(const sf::Vector2f& offset) override;
    bool contains(const sf::Vector2f& point) const override;
};

#endif // SHAPE_HPP
