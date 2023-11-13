#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball(sf::Vector2f position, float size) :
	position{ position },
	size{ size }
{}

void ball::draw(sf::RenderWindow & window) const {
	sf::CircleShape circle;
	circle.setRadius( size );
	circle.setPosition( position );
	circle.setFillColor(sf::Color(125,0,255));
	window.draw( circle );
}
