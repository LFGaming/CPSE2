#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 200), "SFML Buttons");

    // Button 1
    sf::RectangleShape button1(sf::Vector2f(150, 50));
    button1.setPosition(50, 50);
    button1.setFillColor(sf::Color::Green);

    sf::Font font;
    if (!font.loadFromFile("c:\\Windows\\Fonts\\COMICZ.TTF")) {
        std::cerr << "Error loading font file." << std::endl;
        return 1;
    }

    sf::Text buttonText1("Main Menu", font, 20);
    buttonText1.setPosition(button1.getPosition().x + 25, button1.getPosition().y + 10);
    buttonText1.setFillColor(sf::Color::White);

    // Button 2
    sf::RectangleShape button2(sf::Vector2f(150, 50));
    button2.setPosition(200, 50);
    button2.setFillColor(sf::Color::Blue);

    sf::Text buttonText2("Credits", font, 20);
    buttonText2.setPosition(button2.getPosition().x + 40, button2.getPosition().y + 10);
    buttonText2.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                // Check if button 1 is pressed
                if (button1.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    std::cout << "Button 1 pressed!" << std::endl;
                }

                // Check if button 2 is pressed
                if (button2.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    std::cout << "Button 2 pressed!" << std::endl;
                }
            }
        }

        window.clear();
        window.draw(button1);
        window.draw(buttonText1);
        window.draw(button2);
        window.draw(buttonText2);
        window.display();
    }

    return 0;
}
