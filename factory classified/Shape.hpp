#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SFML/Graphics.hpp>

class Shape {
protected:
    sf::Vector2f position;
public:
    Shape(const sf::Vector2f& position)
        : position(position){}
    bool isDragging = false;

    // Implementing methods from the base class
    virtual void draw(sf::RenderWindow& window) const;
    virtual void move(const sf::Vector2f& offset);
    virtual bool contains(const sf::Vector2f& point) const;
    virtual std::string saveme();

    std::string getColorString(const sf::Color& color) {
        if (color == sf::Color::Red) {
            return "red";
        } else if (color == sf::Color::Green ) {
            return "green";
        } else if (color == sf::Color::Blue) {
            return "blue";
        } else if (color == sf::Color::Yellow ) {
            return "yellow";
        } else if (color == sf::Color::Magenta) {
            return "magenta";
        } else if (color == sf::Color::Cyan) {
            return "cyan";
        } else if (color == sf::Color::White) {
            return "white";
        } else if (color == sf::Color::Black) {
            return "black";
        } else {
            return "white";
        }
    }
};

#endif // SHAPE_HPP