#include <SFML/Graphics.hpp>

int main()
{
    int i = 0;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "My Program");
    window.setFramerateLimit(60);

    sf::Font open_sans;
    open_sans.loadFromFile("c:\\Windows\\Fonts\\COMICZ.TTF");

    sf::Text my_text;
    my_text.setFont(open_sans);
    my_text.setString("Score: " + std::to_string(i));

    sf::Text increment_button;
    increment_button.setFont(open_sans);
    increment_button.setString("Increment");
    increment_button.setPosition(10, 50);

    sf::Text decrement_button;
    decrement_button.setFont(open_sans);
    decrement_button.setString("Decrement");
    decrement_button.setPosition(10, 100);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (increment_button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    i++;
                else if (decrement_button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    i--;
            }
        }

        my_text.setString("Score: " + std::to_string(i));

        window.clear();
        window.draw(my_text);
        window.draw(increment_button);
        window.draw(decrement_button);
        window.display();
    }

    return 0;
}

// #include <SFML/Graphics.hpp>
// int main()
// {
//     int i = 0;
//     sf::RenderWindow window(sf::VideoMode(1280, 720), "My Program");
//     window.setFramerateLimit(60);

//     sf::Font open_sans;
//     open_sans.loadFromFile("c:\\Windows\\Fonts\\COMICZ.TTF");

//     sf::Text my_text;
//     my_text.setFont(open_sans);
//     my_text.setString("Score: ");
 
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed) window.close();
 
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
//         }

//         // for (size_t i = 0; i < 100; i++)
//         // {
//             my_text.setString("Score: " + std::to_string(i));
//         // }
     
//         window.clear();
//         window.draw(my_text);
//         window.display();
//         i++;
//     }
 
 
 
//     return 0;
// }