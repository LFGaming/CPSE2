#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <SFML/Graphics.hpp>
#include "Shape.hpp"

class Circle : public Shape {
protected:
    int size;
    sf::Color color;
public:
    Circle(const sf::Vector2f& position, const int& size, const sf::Color& color)
        : Shape(position), size(size), color(color) {}

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape circle(size / 2);
        circle.setFillColor(color);
        circle.setPosition(position);
        window.draw(circle);
    }

    void move(const sf::Vector2f& offset) override {
        position += offset;
    }

    bool contains(const sf::Vector2f& point) const override {
    sf::FloatRect bounds;
        sf::CircleShape circle(size / 2);
        circle.setPosition(position);
        bounds = circle.getGlobalBounds();
        return bounds.contains(point);
    }

    std::string saveme()  override{
        std::string s = "circle " + std::to_string(static_cast<int>(position.x)) + " " + std::to_string(static_cast<int>(position.y)) + " " + std::to_string(size) + " " + getColorString(color);
        return s;
    }
};

#endif // CIRCLE_HPP