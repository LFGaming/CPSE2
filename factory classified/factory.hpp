#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Shape.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Line.hpp"
#include "Picture.hpp"

class Factory {
public:

    static sf::Color getColor(const std::string& color) {
        if (color == "red") {
            return sf::Color::Red;
        } else if (color == "green") {
            return sf::Color::Green;
        } else if (color == "blue") {
            return sf::Color::Blue;
        } else if (color == "yellow") {
            return sf::Color::Yellow;
        } else if (color == "magenta") {
            return sf::Color::Magenta;
        } else if (color == "cyan") {
            return sf::Color::Cyan;
        } else if (color == "white") {
            return sf::Color::White;
        } else if (color == "black") {
            return sf::Color::Black;
        } else if (color == "white"){
            return sf::Color::White;
        }else {
            throw std::runtime_error("\nUnknown color \n");
        }
    }

    static std::unique_ptr<Shape> createShape(std::string& line) {

        std::string type;
        sf::Vector2f position, position2; 
        sf::Color color;
        std::string colorString;
        std::string image;
        int size;
        int x, y;


        std::istringstream iss(line);

        iss >> type >> position.x >> position.y;
        if (!position.x || !position.y)
        {
            throw std::runtime_error("\nInvalid position \n");
        }
        if(!iss){
            throw std::runtime_error("\nInvalid file \n");
        }

        if (type == "circle") {
            iss >> size >> colorString;
            if (!size)
            {
                throw std::runtime_error("\nInvalid size \n");
            }
            color = getColor(colorString);
            return std::make_unique<Circle>(position, size, color);
        } else if (type == "rectangle") {
            iss >> x >> y >> colorString;
            if (!x || !y)
            {
                throw std::runtime_error("\nInvalid pos2 \n");
            }
            position2 = sf::Vector2f(x, y);
            color = getColor(colorString);
            return std::make_unique<Rectangle>(position, position2, color);
        } else if (type == "line") {
            iss >> x >> y >> colorString;
            if (!x || !y)
            {
                throw std::runtime_error("\nInvalid end \n");
            }
            position2 = sf::Vector2f(x, y);
            color = getColor(colorString);
            return std::make_unique<Line>(position, position2, color);
        } else if (type == "picture") {
            iss >> image >> x >> y;
            if (!x || !y)
            {
                throw std::runtime_error("\nInvalid scale \n");
            }
            position2 = sf::Vector2f(x, y);
            return std::make_unique<Picture>(position, image, position2);
        } else {
            throw std::runtime_error("\nUnknown type \n");
        }
    }
};

#endif // FACTORY_HPP