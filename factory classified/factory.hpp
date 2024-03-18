#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "exception.hpp"
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
            throw unknown_color(color);
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
        if ((!position.x && position.x != 0) || (!position.y && position.y != 0))
        {
            throw invalid_position(type);
        }
        if(!iss){
            throw end_of_file();
        }

        if (type == "circle") {
            iss >> size >> colorString;
            if (!size)
            {
                throw invalid_size(type);
            }
            color = getColor(colorString);
            return std::make_unique<Circle>(position, size, color);
        } else if (type == "rectangle") {
            iss >> x >> y >> colorString;
            if (!x || !y)
            {
                throw invalid_position(type);
            }
            position2 = sf::Vector2f(x, y);
            color = getColor(colorString);
            return std::make_unique<Rectangle>(position, position2, color);
        } else if (type == "line") {
            iss >> x >> y >> colorString;
            if (!x || !y)
            {
                throw invalid_position(type);
            }
            position2 = sf::Vector2f(x, y);
            color = getColor(colorString);
            return std::make_unique<Line>(position, position2, color);
        } else if (type == "picture") {
            iss >> image >> x >> y;
            if (!x || !y)
            {
                throw invalid_scale(type);
            }
            position2 = sf::Vector2f(x, y);
            return std::make_unique<Picture>(position, image, position2);
        } else {
            throw unknown_shape(type);
        }
    }
};

#endif // FACTORY_HPP