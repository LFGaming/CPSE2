#include <SFML/Graphics.hpp>
#include "wall.hpp"

wall::wall( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB ) : // Add size parameter
    position{ position },
    size{ size },
	colorRGB{ colorRGB}
{}

void wall::draw( sf::RenderWindow & window ) const {
    sf::RectangleShape rectangle(size); // Set size of rectangle
    rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color(colorRGB));
    window.draw(rectangle);
}