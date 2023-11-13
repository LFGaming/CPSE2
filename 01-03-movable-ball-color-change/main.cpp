#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.hpp"

sf::Vector2f Vector2f_from_Vector2i( sf::Vector2i rhs ){
    return sf::Vector2f(
        static_cast< float >( rhs.x ),
        static_cast< float >( rhs.y )
    );
}

int main( int argc, char *argv[] ){
    std::cout << "Starting application 01-03 moveable ball\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
    ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };

    sf::Clock clock; // Add this line

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Add this line

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            my_ball.move(sf::Vector2f{ -5, 0 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            my_ball.move(sf::Vector2f{ +5, 0 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            my_ball.move(sf::Vector2f{ 0, -5 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            my_ball.move(sf::Vector2f{ 0, +5 });
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            my_ball.jump( 
                Vector2f_from_Vector2i( 
                    sf::Mouse::getPosition( window )));
        }

        my_ball.update(deltaTime); // Add this line

        sf::Event event;
        if( window.pollEvent(event) ){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        my_ball.draw(window);
        window.display();

        sf::sleep(sf::milliseconds(20));
    }

    std::cout << "Terminating application\n";
    return 0;
}