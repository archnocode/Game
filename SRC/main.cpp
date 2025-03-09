#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Event.hpp>
#include <math.h>
#include <sstream>
#include "body.hpp"
#include "texturemanager.hpp"

using namespace std;

const int width =  800;
const int height = 800;

bool focused = false;

int main(){
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game");
    window.setFramerateLimit(60);

    sf::TcpSocket socket;

    TextureManager texture("STATIC/IMAGES/texture.jpg");
    Body enemy(0, 100, texture);
    Body player(0, height-100, texture);

    if (socket.connect({127, 0, 0, 1}, 12345) != sf::Socket::Status::Done) {
        std::cerr << "Не удалось подключиться к серверу" << endl;
        return 1;
    }

    char buffer[1024];
    size_t received;



    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::FocusGained>())
                focused = true;
            if (event->is<sf::Event::FocusLost>())
                focused = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }




        string message = to_string(player.x);
        if (socket.send(message.c_str(), message.size()) != sf::Socket::Status::Done) {
            std::cerr << "Не удалось отправить данные серверу" << endl;
            return 1;
        }

        if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Status::Done) {
            std::cerr << "Не удалось получить данные от сервера" << endl;
            break;
        }

        string response(buffer, received);
        enemy.x = atoi(response.c_str());
        cout << "Enemy: " << enemy.x << "Player: " << player.x << endl;

        window.clear();

        {
            player.move();
            
            player.draw(window);
            enemy.draw(window);
        }

        window.display();
    }
}