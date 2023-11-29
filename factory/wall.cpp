#include <SFML/Graphics.hpp>
#include "wall.hpp"

wall::wall( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB ) : // Add size parameter
    position{ position },
    size{ size },
	colorRGB{ colorRGB}
{
    rectangleshape = sf::RectangleShape(size);
    rectangleshape.setPosition(position);
    rectangleshape.setFillColor(sf::Color(colorRGB));
}

void wall::draw( sf::RenderWindow & window ) {
    sf::RectangleShape rectangle(size); // Set size of rectangle
    rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color(colorRGB));
    window.draw(rectangle);
}

void wall::move(sf::Vector2f delta)
{
}
