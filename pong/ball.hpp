#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "wall.hpp"
#include <iostream>
#include <vector>
#include "drawable.hpp"

class ball : public drawable {
public:
    ball( sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(2.0, 2.0) );
    void draw( sf::RenderWindow & window ) override;
    void move(sf::Vector2f delta = sf::Vector2f{ 0,0 }) override;
    void jump( sf::Vector2f target );
    void jump( sf::Vector2i target );
    // void handle_collision(block &block, wall &wall);
    void handle_collision(block &block);
    void hasOverlap(const std::vector<drawable*>& drawables);
    sf::FloatRect getGlobalBounds() const override;

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

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::CircleShape circle2; // Moved this line after 'radius'
    float size;
};

#endif