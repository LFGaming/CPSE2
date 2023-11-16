#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball(sf::Vector2f position, sf::Vector2f velocity) 
    : radius(30.0f), position(position), velocity(velocity) {}

void ball::handle_collision(block &block, wall &wall) {
    if (collides_with(wall)) {
        if (position.x >= 450 || position.x <= 10) {
            velocity.x *= -1;
        }
        if (position.y >= 400 || position.y <= 10) {
            velocity.y *= -1;
        }
    }

    if (collides_with(block)) {
        float left = abs((position.x - radius) - (block.get_position().x + block.get_size().x));
        float right = abs((position.x + radius) - block.get_position().x);
        float top = abs((position.y - radius) - (block.get_position().y + block.get_size().y));
        float bottom = abs((position.y + radius) - block.get_position().y);

        float min = std::min({left, right, top, bottom});

        if (min == left || min == right) {
            velocity.x *= -1; // Hit the side of the block, reverse x velocity
        } else {
            velocity.y *= -1; // Hit the top or bottom of the block, reverse y velocity
        }
    }
}

void ball::move() {
    position += velocity;
}

void ball::draw( sf::RenderWindow & window ) const {
    sf::CircleShape circle(radius); // Create a circle with radius
    circle.setPosition(position); // Set its position
    circle.setFillColor(sf::Color::Red); // Set its color
    window.draw(circle); // Draw it on the window
}

void ball::jump( sf::Vector2f target ){
    position = target;
}

void ball::jump( sf::Vector2i target ){
    jump( sf::Vector2f( 
        static_cast< float >( target.x ), 
        static_cast< float >( target.y )
    ));
}