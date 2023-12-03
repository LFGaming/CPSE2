#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class DrawableEntity {
public:
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void move(const sf::Vector2f& offset) = 0;
    virtual bool contains(const sf::Vector2f& point) const = 0;
    virtual ~DrawableEntity() = default;
};

struct Shape : public DrawableEntity {
    std::string type;
    sf::Vector2f position;
    sf::Vector2f end; // Second point for lines and rectangles
    sf::Color color;
    std::string textureFile;
    sf::Vector2f scale;
    bool isDragging = false;
    sf::Vector2f size;

    // Implementing methods from the base class
    void draw(sf::RenderWindow& window) const override;
    void move(const sf::Vector2f& offset) override;
    bool contains(const sf::Vector2f& point) const override;
};

void Shape::draw(sf::RenderWindow& window) const {
    if (type == "circle") {
        sf::CircleShape circle(size.x / 2);
        circle.setPosition(position);
        circle.setFillColor(color);
        window.draw(circle);
    } else if (type == "rectangle") {
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(position);
        rectangle.setFillColor(color);
        window.draw(rectangle);
    } else if (type == "line") {
        sf::Vertex line[] = {
            sf::Vertex(position, color),
            sf::Vertex(end, color)
        };
        window.draw(line, 2, sf::Lines);
    } else if (type == "picture") {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
            return;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(position);
        sf::Vector2u originalSize = texture.getSize();
        sprite.setScale(scale.x / originalSize.x, scale.y / originalSize.y);
        window.draw(sprite);
    }
}

void Shape::move(const sf::Vector2f& offset) {
    position += offset;
    if (type == "rectangle") {
        end += offset;
    }
}

bool Shape::contains(const sf::Vector2f& point) const {
    sf::FloatRect bounds;
    if (type == "circle") {
        sf::CircleShape circle(size.x / 2);
        circle.setPosition(position);
        bounds = circle.getGlobalBounds();
    } else if (type == "rectangle") {
        sf::RectangleShape rectangle(size);
        rectangle.setPosition(position);
        bounds = rectangle.getGlobalBounds();
    } else if (type == "line") {
        bounds = sf::FloatRect(std::min(position.x, end.x), std::min(position.y, end.y),
                                std::abs(end.x - position.x), std::abs(end.y - position.y));
    } else if (type == "picture") {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFile)) {
            std::cerr << "Error loading texture: " << textureFile << std::endl;
            return false;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(position);
        sf::Vector2u originalSize = texture.getSize();
        sprite.setScale(scale.x / originalSize.x, scale.y / originalSize.y);
        bounds = sprite.getGlobalBounds();
    }

    return bounds.contains(point);
}

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

int main(int argc, char* argv[]) {
    std::cout << "Starting application opdracht 1\n";

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window", sf::Style::Close | sf::Style::Titlebar };

    std::vector<Shape> shapes = readShapesFromFile("objects.txt");

    while (window.isOpen()) {
        window.clear();

        for (const auto& shape : shapes) {
            shape.draw(window);

            sf::FloatRect bounds;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (auto& shape : shapes) {
                    if (shape.contains(mousePos)) {
                        shape.isDragging = true;
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
                shape.move(mousePos - oldPosition);
                if (shape.type == "rectangle") {
                    shape.end += mousePos - oldPosition;
                }
            }
        }
    }

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
