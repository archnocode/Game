#ifndef BODY_HPP
#define BODY_HPP

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "texturemanager.hpp"

using namespace std;

class Body{
public:
    sf::Vector2f pos;
    sf::Sprite sprite;
    int health;
    float speed;

    Body(float x, float y, float speed, const TextureManager& texturePath);
    void move();
    void draw(sf::RenderWindow &window);
};

#endif //BODY_HPP