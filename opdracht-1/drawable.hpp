#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include <SFML/Graphics.hpp>

class drawable {
    protected:
        sf::Vector2f position;
        sf::Color color;
        sf::Vector2f bounce;

    public:
        drawable(const sf::Vector2f& position, const sf::Color& color, sf::Vector2f bounce):
            position{position},
            color{color},
            bounce{bounce}
        {}

        virtual void draw(sf::RenderWindow &window);
        
        virtual sf::Vector2f getBounce(sf::FloatRect &thing){
            return bounce;
        }
};

#endif // OBJECT_HPP