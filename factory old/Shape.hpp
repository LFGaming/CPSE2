#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "DrawableEntity.hpp"

class Shape : public DrawableEntity {
public:
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
    std::string getType() const override { return type; }
};

#endif // SHAPE_HPP