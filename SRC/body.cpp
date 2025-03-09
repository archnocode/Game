#include "body.hpp"

//Body::Body(float x, float y, float speed, const TextureManager& texturePath){}

void Body::move(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        x += speed;
    }
    sprite.setPosition({x, y});
}

void Body::draw(sf::RenderWindow &window){
    window.draw(sprite);
}