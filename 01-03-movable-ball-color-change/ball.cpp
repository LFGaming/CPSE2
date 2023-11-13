#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball( sf::Vector2f position, float size ) :
    position{ position },
    size{ size },
    colorChangeTimer{ 0.0f }, // Move this line up
    color{ sf::Color::White } // Move this line down
{}

void ball::draw( sf::RenderWindow & window ) const {
    sf::CircleShape circle;
    circle.setRadius(size);
    circle.setPosition(position);
    circle.setFillColor(color);
    window.draw(circle);
}

void ball::update(float deltaTime) {
    colorChangeTimer += deltaTime;
    if (colorChangeTimer >= 0.1f) { // change color every second
        colorChangeTimer = 0.0f;
        color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    }
}

void ball::move( sf::Vector2f delta ) {
    position += delta;
}

void ball::jump( sf::Vector2f target ) {
    position = target;
}