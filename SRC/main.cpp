#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Event.hpp>
#include <math.h>
#include "player.hpp"

using namespace std;

const int width =  800;
const int height = 800;

int main(){
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game");
    window.setFramerateLimit(60);

    //Переменные

    //SF
    sf::Clock clock;

    //Загрузка ресурсов

    //Переменные для ресурсов
    Player player(width/2, height/2, 10.f, "STATIC/IMAGES/texture.jpg");


    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }

        player.body.move();
        window.clear();

        window.draw(player.body.sprite);

        window.display();
    }
}