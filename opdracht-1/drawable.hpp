#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <SFML/Graphics.hpp>

class drawable {
public:
    //drawable(){};
    virtual void draw( sf::RenderWindow & window ) = 0;
    virtual void move( sf::Vector2f delta = sf::Vector2f{0,0}) = 0;
};

#endif // OBJECT_HPP