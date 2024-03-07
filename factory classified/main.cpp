#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Shape.hpp"
#include "factory.hpp"

std::vector<std::unique_ptr<Shape>> readShapesFromFile(const std::string& filename) {
    std::vector<std::unique_ptr<Shape>> shapes;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return shapes;
    }

    std::vector<std::string> invalidLines; // Keep track of invalid lines
    std::string line;
    int lineCount = 0; // Track line number for error reporting
    try{
        while (std::getline(file, line)) {
            lineCount++;
            std::unique_ptr<Shape> shape;
            Factory factory;
            shape = factory.createShape(line);
            shapes.push_back(std::move(shape));
        }

        // Close the file
        file.close();
    }
    catch(std::exception & error){
        std::cerr << error.what();
        std::cerr << "Error reading line " << lineCount << " in file: " << filename << std::endl <<std::endl;
        exit(1);
    }
        return shapes;
    
}

int main(int argc, char* argv[]) {
    std::cout << "Starting application opdracht 1\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window", sf::Style::Close | sf::Style::Titlebar };

    std::vector<std::unique_ptr<Shape>> shapes = readShapesFromFile("objects.txt");

    bool isAnyObjectBeingDragged = false;
    Shape* pickedObject = nullptr;

    sf::Vector2f oldMousePos;

    while (window.isOpen()) {
        window.clear();

        for (auto& shape : shapes) {
            shape->draw(window);
        }

        // Check for picking only if no object is being dragged
        if (!isAnyObjectBeingDragged) {
            for (auto& shape : shapes) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (shape->contains(mousePos)) {
                        shape->isDragging = true;
                        isAnyObjectBeingDragged = true;
                        pickedObject = shape.get();
                        oldMousePos = mousePos;  // Store the initial mouse position
                    }
                }
            }
        }

        window.display();

        sf::sleep(sf::milliseconds(20));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left && pickedObject != nullptr) {
                    pickedObject->isDragging = false;
                    isAnyObjectBeingDragged = false;
                    pickedObject = nullptr;
                }
            }
        }

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (auto& shape : shapes) {
            if (shape->isDragging) {
                sf::Vector2f offset = mousePos - oldMousePos;
                shape->move(offset);
                oldMousePos = mousePos;  // Update the old mouse position
            }
        }
    }

    // Write the updated shapes back to the file
    std::string shapeSaveString;
    std::ofstream file("objects.txt");
    for (const auto& shape : shapes) {
        shapeSaveString = shape->saveme();
        file << shapeSaveString << "\n";
    }
    file.close();

    std::cout << "Terminating application\n";
    return 0;
}
