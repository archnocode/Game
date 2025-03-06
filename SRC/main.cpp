#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

const int width =  800;
const int height = 800;

int main(){
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game");

    //Переменные
    float radius = 100.f;

    sf::Texture texture;
    sf::Clock clock;
    sf::Shader shader;
    sf::CircleShape circle(radius);


    //Загрузка ресурсов
    if (!shader.loadFromFile("STATIC/SHADERS/fragment.frag", sf::Shader::Type::Fragment))
        return -1;

    //Переменные для ресурсов


    circle.setPosition({(int)width/2-radius, (int)height/2-radius});

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        shader.setUniform("time", clock.getElapsedTime().asSeconds());

        window.clear();

        window.draw(circle, &shader);

        window.display();
    }
}