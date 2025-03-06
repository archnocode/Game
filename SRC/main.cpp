#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Game");

    //Переменные
    sf::Texture texture;
    

    //Загрузка ресурсов
    if (!texture.loadFromFile("STATIC/IMAGES/texture.jpg"))
        return -1;

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        window.display();
    }
}