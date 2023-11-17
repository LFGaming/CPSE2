#include <SFML/Graphics.hpp>
#include "ball.hpp"

ball::ball(sf::Vector2f position, sf::Vector2f velocity) :
    position(position),
    velocity(velocity),
    radius(30.0f),
    circle2(radius) // Moved this line after 'radius'
{
    circle2.setRadius(radius);
    circle2.setPosition(position);
}

sf::FloatRect ball::getGlobalBounds() const {
    return circle2.getGlobalBounds();
}
// void ball::handle_collision(block &block, wall &wall) {
//     if (collides_with(wall)) {
//         if (position.x >= 450 || position.x <= 10) {
//             velocity.x *= -1;
//         }
//         if (position.y >= 400 || position.y <= 10) {
//             velocity.y *= -1;
//         }
//     }

//     if (collides_with(block)) {
//         float left = abs((position.x - radius) - (block.get_position().x + block.get_size().x));
//         float right = abs((position.x + radius) - block.get_position().x);
//         float top = abs((position.y - radius) - (block.get_position().y + block.get_size().y));
//         float bottom = abs((position.y + radius) - block.get_position().y);

//         float min = std::min({left, right, top, bottom});

//         if (min == left || min == right) {
//             velocity.x *= -1; // Hit the side of the block, reverse x velocity
//         } else {
//             velocity.y *= -1; // Hit the top or bottom of the block, reverse y velocity
//         }
//     }
// }

void ball::handle_collision(block &block) {
    sf::Vector2f nextPosition = position + velocity;
    sf::RectangleShape nextBallShape(sf::Vector2f(radius * 2, radius * 2));
    nextBallShape.setPosition(nextPosition);

    sf::RectangleShape blockShape(block.get_size());
    blockShape.setPosition(block.get_position());

    if (nextBallShape.getGlobalBounds().intersects(blockShape.getGlobalBounds())) {
        sf::Vector2f blockCenter = block.get_position() + block.get_size() / 8.f;
        sf::Vector2f directionToBlockCenter = blockCenter - nextPosition;

        if (std::abs(directionToBlockCenter.x) > std::abs(directionToBlockCenter.y)) {
            // Collision on the left or right side
            velocity.x *= -1;
            // Move the ball to the point of collision
            if (directionToBlockCenter.x > 0) {
                position.x = block.get_position().x - radius * 2;
            } else {
                position.x = block.get_position().x + block.get_size().x;
            }
        } else {
            // Collision on the top or bottom
            velocity.y *= -1;
            // Move the ball to the point of collision
            if (directionToBlockCenter.y > 0) {
                position.y = block.get_position().y - radius * 2;
            } else {
                position.y = block.get_position().y + block.get_size().y;
            }
        }
    }
}
void ball::move(sf::Vector2f delta){
    position += velocity;
}

void ball::draw( sf::RenderWindow & window ) {
    sf::CircleShape circle(radius); // Create a circle with radius
    circle.setPosition(position); // Set its position
    circle.setFillColor(sf::Color::Red); // Set its color
    circle2.setPosition(position);
    //std::cout << circle2.getPosition().x << std::endl;
    window.draw(circle); // Draw it on the window
}

void ball::jump( sf::Vector2f target ){
    position = target;
}

void ball::jump( sf::Vector2i target ){
    jump( sf::Vector2f( 
        static_cast< float >( target.x ), 
        static_cast< float >( target.y )
    ));
}

void ball::hasOverlap(const std::vector<drawable*>& drawables) {
    for (drawable* drawable : drawables) {
        if (drawable && circle2.getGlobalBounds().intersects(drawable->getGlobalBounds())) {
            auto boundingbox = drawable->getGlobalBounds();
            //std::cout << circle2.getPosition().x;
            //std::cout << "frank";
            //return true;
            // velocity.x *= -1;
            // velocity.y *= -1;
// block dummyBlock(sf::Vector2f(0, 0), sf::Vector2f(0, 0), sf::Color::Black);
//             // Cast the const wall to non-const
//             handle_collision(dummyBlock, const_cast<wall&>(walls[i]));

            // auto boundingbox = drawables[i].rectangleshape.getGlobalBounds();
            sf::FloatRect leftsideblock = sf::FloatRect(boundingbox.left, boundingbox.top+10, 5, boundingbox.height-15);
            sf::FloatRect rightsideblock = sf::FloatRect(boundingbox.left + boundingbox.width-5, boundingbox.top+10, 5, boundingbox.height-15);
            sf::FloatRect uppersideblock = sf::FloatRect(boundingbox.left+10, boundingbox.top, boundingbox.width-15, 5);
            sf::FloatRect lowersideblock = sf::FloatRect(boundingbox.left+5, boundingbox.top + boundingbox.height-5, boundingbox.width-10, 5);

            auto ballBounds = circle2.getGlobalBounds();
            if(ballBounds.intersects(uppersideblock) || ballBounds.intersects(lowersideblock)){
                velocity.y *= -1;
            }
            else if(ballBounds.intersects(leftsideblock) || ballBounds.intersects(rightsideblock)){
                velocity.x *= -1;
            }
        }
    }
}