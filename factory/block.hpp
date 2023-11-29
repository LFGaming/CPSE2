#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class block : public drawable {
public:

	block( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB );

	void draw( sf::RenderWindow & window ) override;

	void move( sf::Vector2f delta ) override;

	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );
	sf::RectangleShape rectangleshape;
	sf::FloatRect getGlobalBounds() const override {
    return rectangleshape.getGlobalBounds();
}

sf::Vector2f get_normal() const {
    // The normal of a block is a vector that points up (in 2D games, up is usually negative y)
    return sf::Vector2f(0, -1);
}

sf::Vector2f get_position() const {
    // Return the position of the block
    return position;
}

sf::Vector2f get_size() const {
    // Return the size of the block
    return size;
}

private:
	sf::Vector2f position;
	sf::Vector2f size; // Add this line
	sf::Color colorRGB;
};

#endif
