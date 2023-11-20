#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.hpp"
#include "block.hpp"
#include "wall.hpp"
#include "drawable.hpp"

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
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 }, sf::Vector2f{ 1.0, 1.0 } }; // Add velocity parameter
    block Right_block{ sf::Vector2f{ 540, 220.0 }, sf::Vector2f{ 50.0, 50.0 }, sf::Color::Yellow };
    block Left_block{ sf::Vector2f{ 100, 220.0 }, sf::Vector2f{ 50.0, 50.0 }, sf::Color::Green };

    // Create four walls
    wall top_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Blue };
	wall bottom_wall{ sf::Vector2f{ 0.0, 470.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Red };
	wall left_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Magenta };
	wall right_wall{ sf::Vector2f{ 630.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Green };

	std::vector<drawable*> drawables = { &top_wall, &bottom_wall, &left_wall, &right_wall, &Right_block, &Left_block };

	std::vector<wall> walls;
	walls.push_back(top_wall);
	walls.push_back(bottom_wall);
	walls.push_back(left_wall);
	walls.push_back(right_wall);

	action actions[] = {
		action( sf::Keyboard::Left,  [&](){ Right_block.move( sf::Vector2f( -3.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ Right_block.move( sf::Vector2f( +3.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ Right_block.move( sf::Vector2f(  0.0, -3.0 )); }),
		action( sf::Keyboard::Down,  [&](){ Right_block.move( sf::Vector2f(  0.0, +3.0 )); }),
		action( sf::Mouse::Left,     [&](){ Right_block.jump( sf::Mouse::getPosition( window )); }),
		action( sf::Keyboard::A,  [&](){ Left_block.move( sf::Vector2f( -3.0,  0.0 )); }),
		action( sf::Keyboard::D, [&](){ Left_block.move( sf::Vector2f( +3.0,  0.0 )); }),
		action( sf::Keyboard::W,    [&](){ Left_block.move( sf::Vector2f(  0.0, -3.0 )); }),
		action( sf::Keyboard::S,  [&](){ Left_block.move( sf::Vector2f(  0.0, +3.0 )); }),
		action( sf::Mouse::Left,     [&](){ Left_block.jump( sf::Mouse::getPosition( window )); }),
		action( [](){ return true; }, [&](){ my_ball.hasOverlap(drawables); }), // Wall collision
		action( [](){ return true; }, [&](){ my_ball.handle_collision(Right_block); }), // Block collision
		action( [](){ return true; }, [&](){ my_ball.handle_collision(Left_block); }), // Block collision
		action( [](){ return true; }, [&](){ my_ball.move(); }) // Always move the ball
	};

while (window.isOpen()) {
    for(auto & action : actions) {
        action();
    }

    window.clear();
    my_ball.draw(window);
    Right_block.draw(window);
    Left_block.draw(window);
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