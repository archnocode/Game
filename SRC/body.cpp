#include "body.hpp"

void Body::move(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (x>0)){
        x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (x + sprite.getTexture().getSize().x < width)){
        x += speed;
    }
}

void Body::draw(sf::RenderWindow &window){
    sprite.setPosition({x, y});
    window.draw(sprite);
}