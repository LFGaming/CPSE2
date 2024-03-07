#ifndef PICTURE_HPP
#define PICTURE_HPP

#include <SFML/Graphics.hpp>
#include "Shape.hpp"

class Picture : public Shape {
protected:
    std::string image;
    sf::Vector2f size;
public:
    Picture(const sf::Vector2f& position, const std::string& image, const sf::Vector2f& size)
        : Shape(position), image(image), size(size) {}

    void draw(sf::RenderWindow& window) const override {
        sf::Texture texture;
        texture.loadFromFile(image);
        sf::Sprite sprite(texture);
        sprite.setPosition(position);
        sf::Vector2u originalSize = texture.getSize();
        sprite.setScale(size.x / originalSize.x, size.y / originalSize.y);
        window.draw(sprite);
    }

    void move(const sf::Vector2f& offset) override {
        position += offset;
    }

    bool contains(const sf::Vector2f& point) const override {
        return position.x <= point.x && point.x <= position.x + 100 &&
               position.y <= point.y && point.y <= position.y + 100;
    }
    std::string saveme()  override{
        std::string s = "picture " + std::to_string(static_cast<int>(position.x)) + " " + std::to_string(static_cast<int>(position.y)) + " " + image + " " + std::to_string(static_cast<int>(size.x)) + " " + std::to_string(static_cast<int>(size.y));
        return s;
    }

};

#endif // PICTURE_HPP