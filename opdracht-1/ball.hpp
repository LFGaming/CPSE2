#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "block.hpp"
#include "wall.hpp"

class ball {
public:
    ball( sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(1.0, 1.0) );
    void draw( sf::RenderWindow & window ) const;
    void move();
	void jump( sf::Vector2f target );
	void jump( sf::Vector2i target );

    void bounce(const block& bl);
    void bounce(const wall& w);

private:
    sf::Vector2f position;
    sf::Vector2f velocity;
	float size;
};

#endif
