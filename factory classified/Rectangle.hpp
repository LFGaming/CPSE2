#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "Shape.hpp"

class Rectangle : public Shape {
protected:
    sf::Vector2f size;
    sf::Color color;
public:
    Rectangle(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
        : Shape(position), size(size), color(color) {}

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(position);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    }

    void move(const sf::Vector2f& offset) override {
        position += offset;
    }

    bool contains(const sf::Vector2f& point) const override {
        return position.x <= point.x && point.x <= position.x + size.x &&
               position.y <= point.y && point.y <= position.y + size.y;
    }

    std::string saveme()  override{
        std::string s = "rectangle " + std::to_string(static_cast<int>(position.x)) + " " + std::to_string(static_cast<int>(position.y)) + " " + std::to_string(static_cast<int>(size.x)) + " " + std::to_string(static_cast<int>(size.y))  + " " + getColorString(color);
        return s;
    }
};

#endif // RECTANGLE_HPP