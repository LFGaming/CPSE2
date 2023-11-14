#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <SFML/Graphics.hpp>

class block {
public:

	block( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB );

	void draw( sf::RenderWindow & window ) const;

	void move( sf::Vector2f delta );

	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );

	sf::Vector2f get_position() const { return position; }
    sf::Vector2f get_size() const { return size; }

private:
	sf::Vector2f position;
	sf::Vector2f size; // Add this line
	sf::Color colorRGB;
};

#endif
