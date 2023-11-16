#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "block.hpp"
#include "wall.hpp"
// #include "drawable.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application opdracht 1\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window", sf::Style::Close | sf::Style::Titlebar};
    // ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 }, sf::Vector2f{ 1.0, 1.0 } }; // Add velocity parameter
    block my_block{ sf::Vector2f{ 320.0, 240.0 }, sf::Vector2f{ 50.0, 50.0 }, sf::Color::Yellow };
    // wall my_wall{ sf::Vector2f{ 320.0, 240.0 }, sf::Vector2f{ 50.0, 50.0 } }; // Add size parameter

    // Create four walls
    wall top_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Blue };
	wall bottom_wall{ sf::Vector2f{ 0.0, 470.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Red };
	wall left_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Magenta };
	wall right_wall{ sf::Vector2f{ 630.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Green };


	action actions[] = {
		action( sf::Keyboard::Left,  [&](){ my_block.move( sf::Vector2f( -1.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ my_block.move( sf::Vector2f( +1.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ my_block.move( sf::Vector2f(  0.0, -1.0 )); }),
		action( sf::Keyboard::Down,  [&](){ my_block.move( sf::Vector2f(  0.0, +1.0 )); }),
		action( sf::Mouse::Left,     [&](){ my_block.jump( sf::Mouse::getPosition( window )); })
	};

while (window.isOpen()) {
    for(auto & action : actions) {
        action();
    }

    window.clear();
    my_ball.draw(window);
    my_block.draw(window);

    // Collision detection and response
    wall* walls[] = { &top_wall, &bottom_wall, &left_wall, &right_wall };
    for(auto & wall : walls) {
        if (my_ball.collides_with(*wall)) {
            my_ball.handle_collision();
        }
    }

    if(my_ball.collides_with(my_block)) {
        my_ball.bounce(my_block.get_normal());
    }

    my_ball.move();

    top_wall.draw(window);
    bottom_wall.draw(window);
    left_wall.draw(window);
    right_wall.draw(window);

    window.display();

    sf::sleep(sf::milliseconds(20));

    sf::Event event;        
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
	std::cout << "Terminating application\n";
	return 0;
}

