#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include "Shape.hpp"

std::vector<Shape> readShapesFromFile(const std::string& filename) {
    std::vector<Shape> shapes;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return shapes;
    }

    std::vector<std::string> invalidLines; // Keep track of invalid lines
    std::string line;
    int lineCount = 0; // Track line number for error reporting
    while (std::getline(file, line)) {
        lineCount++;
        std::istringstream iss(line);
        Shape shape;
        int r, g, b;
        if (iss >> shape.type >> shape.position.x >> shape.position.y) {
            if (shape.type == "circle" || shape.type == "rectangle") {
                if (iss >> shape.size.x >> shape.size.y >> r >> g >> b) {
                    shape.color = sf::Color(r, g, b);
                    shapes.push_back(shape);
                } else {
                    invalidLines.push_back(line); // Store invalid line
                    std::cerr << "Incomplete data in line " << lineCount << " of file: " << filename << std::endl;
                    exit(1); // Exit the program after identifying a wrong line
                }
            } else if (shape.type == "line") {
                if (iss >> shape.end.x >> shape.end.y >> r >> g >> b) {
                    shape.color = sf::Color(r, g, b);
                    shapes.push_back(shape);
                } else {
                    invalidLines.push_back(line); // Store invalid line
                    std::cerr << "Incomplete data in line " << lineCount << " of file: " << filename << std::endl;
                    exit(1); // Exit the program after identifying a wrong line
                }
            } else if (shape.type == "picture") {
                if (iss >> shape.textureFile >> shape.scale.x >> shape.scale.y) {
                    shapes.push_back(shape);
                } else {
                    invalidLines.push_back(line); // Store invalid line
                    std::cerr << "Incomplete data in line " << lineCount << " of file: " << filename << std::endl;
                    exit(1); // Exit the program after identifying a wrong line
                }
            } else {
                invalidLines.push_back(line); // Store invalid line
                std::cerr << "Unknown shape type in line " << lineCount << " of file: " << filename << std::endl;
                exit(1); // Exit the program after identifying a wrong line
            }
        } else {
            invalidLines.push_back(line); // Store invalid line
            std::cerr << "Error reading line " << lineCount << " in file: " << filename << std::endl;
            exit(1); // Exit the program after identifying a wrong line
        }
    }

    // Close the file
    file.close();

    // Append invalid lines to the end of the shapes file
    std::ofstream outFile(filename, std::ios_base::app);
    if (outFile.is_open()) {
        for (const auto& invalidLine : invalidLines) {
            outFile << invalidLine << "\n";
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file for appending: " << filename << std::endl;
    }

    return shapes;
}


int main(int argc, char* argv[]) {
    std::cout << "Starting application opdracht 1\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window", sf::Style::Close | sf::Style::Titlebar };

    std::vector<Shape> shapes = readShapesFromFile("objects.txt");

    bool isAnyObjectBeingDragged = false;
    Shape* pickedObject = nullptr;

    sf::Vector2f oldMousePos;

    while (window.isOpen()) {
        window.clear();

        for (auto& shape : shapes) {
            shape.draw(window);
        }

        // Check for picking only if no object is being dragged
        if (!isAnyObjectBeingDragged) {
            for (auto& shape : shapes) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (shape.contains(mousePos)) {
                        shape.isDragging = true;
                        isAnyObjectBeingDragged = true;
                        pickedObject = &shape;
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
            if (shape.isDragging) {
                sf::Vector2f offset = mousePos - oldMousePos;
                shape.move(offset);

                // Adjust the endpoints for lines
                if (shape.type == "line") {
                    shape.end += offset;
                }

                oldMousePos = mousePos;  // Update the old mouse position
            }
        }
    }

    // Write the updated shapes back to the file
    std::ofstream file("objects.txt");
    for (const auto& shape : shapes) {
        if (shape.type == "circle" || shape.type == "rectangle") {
            file << shape.type << " " << shape.position.x << " " << shape.position.y << " "
                 << shape.size.x << " " << shape.size.y << " "
                 << (int)shape.color.r << " " << (int)shape.color.g << " " << (int)shape.color.b << "\n";
        } else if (shape.type == "line") {
            file << shape.type << " " << shape.position.x << " " << shape.position.y << " "
                 << shape.end.x << " " << shape.end.y << " "
                 << (int)shape.color.r << " " << (int)shape.color.g << " " << (int)shape.color.b << "\n";
        } else if (shape.type == "picture") {
            file << shape.type << " " << shape.position.x << " " << shape.position.y << " "
                 << shape.textureFile << " " << shape.scale.x << " " << shape.scale.y << "\n";
        }
    }
    file.close();

    std::cout << "Terminating application\n";
    return 0;
}
