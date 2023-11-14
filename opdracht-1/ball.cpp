#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball( sf::Vector2f position, sf::Vector2f velocity ) :
    position{ position },
    velocity{ velocity }
{}

void ball::bounce(const block& bl) {
    sf::Vector2f bl_pos = bl.get_position();
    sf::Vector2f bl_size = bl.get_size();

    // Check for collision on the x axis
    if ((position.x + size > bl_pos.x && position.x < bl_pos.x + bl_size.x) &&
        (position.y + size > bl_pos.y && position.y < bl_pos.y + bl_size.y)) {
        velocity.x = -velocity.x; // Reverse x velocity
    }

    // Check for collision on the y axis
    if ((position.y + size > bl_pos.y && position.y < bl_pos.y + bl_size.y) &&
        (position.x + size > bl_pos.x && position.x < bl_pos.x + bl_size.x)) {
        velocity.y = -velocity.y; // Reverse y velocity
    }
}

void ball::bounce(const wall& w) {
    sf::Vector2f w_pos = w.get_position();
    sf::Vector2f w_size = w.get_size();

    // Check for collision on the x axis
    if ((position.x + size > w_pos.x && position.x < w_pos.x + w_size.x) &&
        (position.y + size > w_pos.y && position.y < w_pos.y + w_size.y)) {
        velocity.x = -velocity.x; // Reverse x velocity
    }

    // Check for collision on the y axis
    if ((position.y + size > w_pos.y && position.y < w_pos.y + w_size.y) &&
        (position.x + size > w_pos.x && position.x < w_pos.x + w_size.x)) {
        velocity.y = -velocity.y; // Reverse y velocity
    }
}
void ball::move() {
    position += velocity;
}

void ball::draw( sf::RenderWindow & window ) const {
    sf::CircleShape circle(10); // Create a circle with radius 10
    circle.setPosition(position); // Set its position
    circle.setFillColor(sf::Color::Red); // Set its color
    window.draw(circle); // Draw it on the window
}

// void ball::move( sf::Vector2f delta ){
// 	position += delta;
// }

void ball::jump( sf::Vector2f target ){
	position = target;
}

void ball::jump( sf::Vector2i target ){
	jump( sf::Vector2f( 
		static_cast< float >( target.x ), 
		static_cast< float >( target.y )
	));
}
