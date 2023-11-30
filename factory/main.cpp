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
    // float size; // Diameter for circles
    sf::Color color;
    std::string textureFile; // Filename of the texture for pictures
    sf::Vector2f scale; // Scale factor for pictures
    bool isDragging = false;
    sf::Vector2f size;
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
        if (iss >> shape.type >> shape.position.x >> shape.position.y) {
            if (shape.type == "circle" || shape.type == "rectangle") {
                iss >> shape.size.x >> shape.size.y >> r >> g >> b;
                shape.color = sf::Color(r, g, b);
            } else if (shape.type == "line") {
                iss >> shape.end.x >> shape.end.y >> r >> g >> b;
                shape.color = sf::Color(r, g, b);
            } else if (shape.type == "picture") {
                iss >> shape.textureFile >> shape.scale.x >> shape.scale.y;
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
        sf::FloatRect bounds;
        if (shape.type == "circle") {
            sf::CircleShape circle(shape.size.x / 2); // Radius is half the diameter
            circle.setPosition(shape.position);
            circle.setFillColor(shape.color);
            window.draw(circle);
            bounds = circle.getGlobalBounds();
        } else if (shape.type == "rectangle") {
            sf::RectangleShape rectangle(shape.size);
            rectangle.setPosition(shape.position);
            rectangle.setFillColor(shape.color);
            window.draw(rectangle);
            bounds = rectangle.getGlobalBounds();
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
            sf::Vector2u originalSize = texture.getSize();
            sprite.setScale(shape.scale.x / originalSize.x, shape.scale.y / originalSize.y);
            window.draw(sprite);
            bounds = sprite.getGlobalBounds();
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
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (auto& shape : shapes) {
                    sf::FloatRect bounds;
                    if (shape.type == "circle") {
                        sf::CircleShape circle(shape.size.x / 2);
                        circle.setPosition(shape.position);
                        bounds = circle.getGlobalBounds();
                    } else if (shape.type == "rectangle") {
                        sf::RectangleShape rectangle(shape.size);
                        rectangle.setPosition(shape.position);
                        bounds = rectangle.getGlobalBounds();
                    } else if (shape.type == "picture") {
                        sf::Texture texture;
                        if (!texture.loadFromFile(shape.textureFile)) {
                            std::cerr << "Error loading texture: " << shape.textureFile << std::endl;
                            continue;
                        }
                        sf::Sprite sprite(texture);
                        sprite.setPosition(shape.position);
                        sf::Vector2u originalSize = texture.getSize();
                        sprite.setScale(shape.scale.x / originalSize.x, shape.scale.y / originalSize.y);
                        bounds = sprite.getGlobalBounds();
                    }
                    if (bounds.contains(mousePos)) {
                        shape.isDragging = true;
                    }
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (auto& shape : shapes) {
                    shape.isDragging = false;
                }
            }
        }
    }

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (auto& shape : shapes) {
        if (shape.isDragging) {
            sf::Vector2f oldPosition = shape.position;
            shape.position = mousePos;
            if (shape.type == "rectangle") {
                shape.end = shape.position + shape.size;
            }
        }
    }
}
std::ofstream file("objects.txt");
for (const auto& shape : shapes) {
    if (shape.type == "circle" || shape.type == "rectangle") {
        file << shape.type << " " << shape.position.x << " " << shape.position.y << " " << shape.size.x << " " << shape.size.y << " "
             << (int)shape.color.r << " " << (int)shape.color.g << " " << (int)shape.color.b << "\n";
    } else if (shape.type == "line") {
        file << shape.type << " " << shape.position.x << " " << shape.position.y << " " << shape.end.x << " " << shape.end.y << " "
             << (int)shape.color.r << " " << (int)shape.color.g << " " << (int)shape.color.b << "\n";
    } else if (shape.type == "picture") {
        file << shape.type << " " << shape.position.x << " " << shape.position.y << " " << shape.textureFile << " " << shape.scale.x << " " << shape.scale.y << "\n";
    }
}
file.close();

std::cout << "Terminating application\n";
return 0;
}