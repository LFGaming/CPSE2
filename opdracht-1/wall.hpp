#ifndef _WALL_HPP
#define _WALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class wall : public drawable {
public:
    wall( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB ); // Add size parameter

    void draw( sf::RenderWindow & window ) override;
    void move(sf::Vector2f delta ) override;
	sf::Vector2f get_position() const { return position; }
    sf::Vector2f get_size() const { return size; }

    sf::Vector2f get_normal() const {
        // The normal of a wall is a vector that points up (in 2D games, up is usually negative y)
        return sf::Vector2f(0, -1);
    }
    sf::RectangleShape rectangleshape;

private:
    sf::Vector2f position;
    sf::Vector2f size; // Add this line
	sf::Color colorRGB;

};

#endif