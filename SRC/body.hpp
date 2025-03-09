#ifndef BODY_HPP
#define BODY_HPP

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "texturemanager.hpp"
#include "settings.hpp"

using namespace std;

class Body{
public:
    int x;
    int y;
    sf::Sprite sprite;
    float speed;
    int id;

    Body(int x, int y, const TextureManager& texturePath) : speed(10.f), x(x), y(y), sprite(texturePath.getTexture()){
        sprite.setScale({0.2f, 0.1f});
    }
    void move();
    void draw(sf::RenderWindow &window);
};

#endif //BODY_HPP