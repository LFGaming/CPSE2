#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
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

int main( int argc, char *argv[] ){
    std::cout << "Starting application opdracht 1\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window", sf::Style::Close | sf::Style::Titlebar};

    std::vector<Shape> shapes = readShapesFromFile("objects.txt");

    while (window.isOpen()) {
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