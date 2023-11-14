#include <SFML/Graphics.hpp>
#include "block.hpp"

block::block( sf::Vector2f position, sf::Vector2f size, sf::Color colorRGB ) :
    position{ position },
    size{ size },
    colorRGB{ colorRGB }
{}

void block::draw( sf::RenderWindow & window ) const {
    sf::RectangleShape rectangle(size); // Set size of rectangle
    rectangle.setPosition(position);
    rectangle.setFillColor(colorRGB);
    window.draw(rectangle);
}

void block::move( sf::Vector2f delta ) {
    position += delta;
}

void block::jump( sf::Vector2f target ){
    position = target;
}

void block::jump( sf::Vector2i target ){
    jump( sf::Vector2f( 
        static_cast< float >( target.x ), 
        static_cast< float >( target.y )
    ));
}