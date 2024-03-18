#include "Shape.hpp"
#include <iostream>

void Shape::draw(sf::RenderWindow& window) const {
    if (type == "circle") {
        sf::CircleShape circle(size.x / 2);
        circle.setPosition(position);
        circle.setFillColor(color);
        window.draw(circle);
    } else if (type == "rectangle") {
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(position);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    } else if (type == "line") {
        sf::Vertex line[] = {
            sf::Vertex(position, color),
            sf::Vertex(end, color)
        };
        window.draw(line, 2, sf::Lines);
    } else if (type == "picture") {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
            return;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(position);
        sf::Vector2u originalSize = texture.getSize();
        sprite.setScale(scale.x / originalSize.x, scale.y / originalSize.y);
        window.draw(sprite);
    }
}

void Shape::move(const sf::Vector2f& offset) {
    position += offset;
    if (type == "rectangle") {
        end += offset;
    }
}

bool Shape::contains(const sf::Vector2f& point) const {
    sf::FloatRect bounds;
    if (type == "circle") {
        sf::CircleShape circle(size.x / 2);
        circle.setPosition(position);
        bounds = circle.getGlobalBounds();
    } else if (type == "rectangle") {
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(position);
        bounds = rectangle.getGlobalBounds();
    } else if (type == "line") {
        bounds = sf::FloatRect(std::min(position.x, end.x), std::min(position.y, end.y),
                                std::abs(end.x - position.x), std::abs(end.y - position.y));
    } else if (type == "picture") {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
            return false;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(position);
        sf::Vector2u originalSize = texture.getSize();
        sprite.setScale(scale.x / originalSize.x, scale.y / originalSize.y);
        bounds = sprite.getGlobalBounds();
    }

    return bounds.contains(point);
}
