#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
#include "Shape.hpp"

class Line : public Shape {
private:
    sf::Color color;
    sf::Vector2f end;

public:
    Line(const sf::Vector2f& position, const sf::Vector2f& end, const sf::Color& color)
        : Shape(position), color(color), end(end) {}

    void draw(sf::RenderWindow& window) const override {
        sf::Vertex line[] = {
            sf::Vertex(position, color),
            sf::Vertex(end, color)
        };
        window.draw(line, 2, sf::Lines);
    }

    void move(const sf::Vector2f& offset) override {
        position += offset;
        end += offset;
    }

    bool contains(const sf::Vector2f& point) const override {
    sf::FloatRect bounds;
        bounds = sf::FloatRect(std::min(position.x, end.x), std::min(position.y, end.y),
                                std::abs(end.x - position.x), std::abs(end.y - position.y));
        return bounds.contains(point);
    }

    std::string saveme(){
        std::string s = "line " + std::to_string(static_cast<int>(position.x)) + " " + std::to_string(static_cast<int>(position.y)) + " " + std::to_string(static_cast<int>(end.x)) + " " + std::to_string(static_cast<int>(end.y)) + " " + getColorString(color);
        return s;
    }
};

#endif // LINE_HPP