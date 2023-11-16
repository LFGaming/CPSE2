#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "wall.hpp"
#include <iostream>

class ball {
public:
    ball( sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(1.0, 1.0) );
    void draw( sf::RenderWindow & window ) const;
    void move();
    void jump( sf::Vector2f target );
    void jump( sf::Vector2i target );

    bool collides_with(const wall & other) const {
        // Check if the ball's position is within the boundaries of the wall
        bool collision = position.x - radius < other.get_position().x + other.get_size().x &&
                         position.x + radius > other.get_position().x &&
                         position.y - radius < other.get_position().y + other.get_size().y &&
                         position.y + radius > other.get_position().y;
        return collision;
    }

    bool collides_with(const block & other) const {
        // Check if the ball's position is within the boundaries of the block
        bool collision = position.x - radius < other.get_position().x + other.get_size().x &&
                         position.x + radius > other.get_position().x &&
                         position.y - radius < other.get_position().y + other.get_size().y &&
                         position.y + radius > other.get_position().y;
        return collision;
    }
void bounce(const sf::Vector2f & normal) {
    float dotProduct = velocity.x * normal.x + velocity.y * normal.y;
    velocity = velocity - 2.0f * dotProduct * normal;
}
    void handle_collision();
    // void bounce(const sf::Vector2f & normal);

private:
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float size;
};

#endif