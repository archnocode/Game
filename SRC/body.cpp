#include "body.hpp"

Body::Body(float x, float y, float speed, const TextureManager& texturePath) : health(100), speed(speed), pos(x, y), sprite(texturePath.getTexture()){}

void Body::move(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        pos.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        pos.x += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        pos.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        pos.y += speed;
    }
    sprite.setPosition({pos.x, pos.y});
}

void Body::draw(sf::RenderWindow &window){
    window.draw(sprite);
}