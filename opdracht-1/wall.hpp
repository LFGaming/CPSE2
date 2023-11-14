#ifndef _WALL_HPP
#define _WALL_HPP

#include <SFML/Graphics.hpp>

class wall {
public:
    wall( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB ); // Add size parameter

    void draw( sf::RenderWindow & window ) const;

	sf::Vector2f get_position() const { return position; }
    sf::Vector2f get_size() const { return size; }

private:
    sf::Vector2f position;
    sf::Vector2f size; // Add this line
	sf::Color colorRGB;
};

#endif