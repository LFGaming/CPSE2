#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.hpp"
#include "block.hpp"
#include "wall.hpp"
#include "drawable.hpp"
#include <fstream>
#include <sstream>

struct Shape {
    std::string type;
    sf::Vector2f position;
    sf::Vector2f end; // Second point for lines and rectangles
    float size; // Diameter for circles
    sf::Color color;
    std::string textureFile; // Filename of the texture for pictures
};

std::vector<Shape> readShapesFromFile(const std::string& filename) {
    std::vector<Shape> shapes;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return shapes;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Shape shape;
        int r, g, b;
        if (iss >> shape.type) {
            if (shape.type == "circle") {
                iss >> shape.position.x >> shape.position.y >> shape.size >> r >> g >> b;
                shape.color = sf::Color(r, g, b);
            } else if (shape.type == "rectangle" || shape.type == "line") {
                iss >> shape.position.x >> shape.position.y >> shape.end.x >> shape.end.y >> r >> g >> b;
                shape.color = sf::Color(r, g, b);
            } else if (shape.type == "picture") {
                iss >> shape.position.x >> shape.position.y >> shape.textureFile;
            }
            shapes.push_back(shape);
        } else {
            std::cerr << "Error reading line: " << line << std::endl;
        }
    }

    return shapes;
}

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
    block my_block{ sf::Vector2f{ 100.0, 100.0 }, sf::Vector2f{ 50.0, 50.0 }, sf::Color::Yellow };

    // Create four walls
    wall top_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Blue };
	wall bottom_wall{ sf::Vector2f{ 0.0, 470.0 }, sf::Vector2f{ 640.0, 10.0 }, sf::Color::Red };
	wall left_wall{ sf::Vector2f{ 0.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Magenta };
	wall right_wall{ sf::Vector2f{ 630.0, 0.0 }, sf::Vector2f{ 10.0, 480.0 }, sf::Color::Green };

	std::vector<drawable*> drawables = { &top_wall, &bottom_wall, &left_wall, &right_wall, &my_block };

	std::vector<wall> walls;
	walls.push_back(top_wall);
	walls.push_back(bottom_wall);
	walls.push_back(left_wall);
	walls.push_back(right_wall);

	action actions[] = {
		action( sf::Keyboard::Left,  [&](){ my_block.move( sf::Vector2f( -2.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ my_block.move( sf::Vector2f( +2.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ my_block.move( sf::Vector2f(  0.0, -2.0 )); }),
		action( sf::Keyboard::Down,  [&](){ my_block.move( sf::Vector2f(  0.0, +2.0 )); }),
		action( sf::Mouse::Left,     [&](){ my_block.jump( sf::Mouse::getPosition( window )); }),
		action( [](){ return true; }, [&](){ my_ball.hasOverlap(drawables); }), // Wall collision
		action( [](){ return true; }, [&](){ my_ball.handle_collision(my_block); }), // Block collision
		action( [](){ return true; }, [&](){ my_ball.move(); }) // Always move the ball
	};


std::vector<Shape> shapes = readShapesFromFile("objects.txt");

while (window.isOpen()) {
    for(auto & action : actions) {
        action();
    }

    window.clear();

for (const auto& shape : shapes) {
    if (shape.type == "circle") {
        sf::CircleShape circle(shape.size / 2); // Radius is half the diameter
        circle.setPosition(shape.position);
        circle.setFillColor(shape.color);
        window.draw(circle);
    } else if (shape.type == "rectangle") {
        sf::RectangleShape rectangle(shape.end - shape.position);
        rectangle.setPosition(shape.position);
        rectangle.setFillColor(shape.color);
        window.draw(rectangle);
    } else if (shape.type == "line") {
        sf::Vertex line[] = {
            sf::Vertex(shape.position, shape.color),
            sf::Vertex(shape.end, shape.color)
        };
        window.draw(line, 2, sf::Lines);
    } else if (shape.type == "picture") {
        sf::Texture texture;
        if (!texture.loadFromFile(shape.textureFile)) {
            std::cerr << "Error loading texture: " << shape.textureFile << std::endl;
            continue;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(shape.position);
        window.draw(sprite);
    }
}

    my_ball.draw(window);
    my_block.draw(window);
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
} // This is the missing closing brace

std::cout << "Terminating application\n";
return 0;
}