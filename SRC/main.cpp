#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Event.hpp>
#include <math.h>
#include "mylib.hpp"

using namespace std;

const int width =  800;
const int height = 800;

int main(){
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game");
    window.setFramerateLimit(60);

    //Переменные
    vec2f image{width/2, height/2};
    float speed = 10.f;

    //SF
    sf::Texture texture;
    sf::Clock clock;


    //Загрузка ресурсов
    if (!texture.loadFromFile("STATIC/IMAGES/texture.jpg"))
        return -1;

    //Переменные для ресурсов
    sf::Sprite sprite(texture);


    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            image.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            image.x += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            image.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            image.y += speed;
        }

        sprite.setPosition(sf::Vector2f{image.x, image.y});
        window.clear();

        window.draw(sprite);

        window.display();
    }
}