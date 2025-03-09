#include <iostream>
#include <cstring>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Event.hpp>
#include <math.h>
#include <sstream>
#include "body.hpp"
#include "texturemanager.hpp"
#include "settings.hpp"

using namespace std;

bool focused = false;


vector<int> parse(string str) {
    istringstream iss(str);
    vector<string> tokens;
    string token;
    vector<int> res;

    while (iss >> token) {
        tokens.push_back(token);
    }

    for (const auto& t : tokens) {
        res.push_back(atoi(t.c_str()));
    }

    return res;
}

int main(){
    sf::RenderWindow window(sf::VideoMode({width, height}), "Game");
    window.setFramerateLimit(FPS);

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

    if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Status::Done) {
        std::cerr << "Не удалось получить данные от сервера" << endl;
        return -1;
    }

    string response(buffer, received);
    int id = atoi(response.c_str());

    sf::CircleShape ball(r);
    sf::Vector2f move;
    sf::Vector2f pos{width/2-r, height/2-r};

    ball.setFillColor(sf::Color::Green);
    ball.setOutlineThickness(5.f);
    ball.setOutlineColor(sf::Color(250, 150, 100));
    ball.setPosition(pos);

    if (id == 0){
        srand(time(NULL));

        move = sf::Vector2f(1+rand() % 3, 1+rand() % 3);
    }

    int t = 0;
    int timer = 5*FPS;

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

        string message = "p" + to_string(player.x);
        if (socket.send(message.c_str(), message.size()) != sf::Socket::Status::Done) {
            std::cerr << "Не удалось отправить данные серверу" << endl;
            return 1;
        }

        if (socket.receive(buffer, sizeof(buffer), received) != sf::Socket::Status::Done) {
            std::cerr << "Не удалось получить данные от сервера" << endl;
            break;
        }

        string response(buffer, received);
        if (response.c_str()[0] == 'p')
            enemy.x = atoi(response.substr(1).c_str());
        else{
            ball.setPosition({parse(response)[0], parse(response)[1]});
            enemy.x = parse(response)[2];
        }

        if (id == 0 && t >= timer){
            pos.x += move.x;
            pos.y += move.y;

            ball.setPosition(pos);

            if (pos.x +r+r >= width || pos.x <= 0)
                move.x = -move.x;

            if (pos.y +r+r > height){
                cout << "YOU LOSE!" << endl;
                window.close();
            }
            if (pos.y < 0){
                cout << "YOU WIN!" << endl;
                window.close();
            }

            if ((pos.y +r+r >= player.y && (pos.x > player.x && pos.x < player.x + player.sprite.getTexture().getSize().x*0.2f)))
                move.y = -move.y;
            if ((pos.y +r+r <= enemy.y + enemy.sprite.getTexture().getSize().y*0.1f && (pos.x > enemy.x && pos.x < enemy.x + enemy.sprite.getTexture().getSize().x*0.2f)))
                move.y = -move.y;

            string message = to_string(pos.x) + " " + to_string(height-pos.y) + " " + to_string(player.x);
            if (socket.send(message.c_str(), message.size()) != sf::Socket::Status::Done) {
                std::cerr << "Не удалось отправить данные серверу" << endl;
                return 1;
            }
        }
        

        window.clear();

        {
            if (focused){
                player.move();
            }
            
            window.draw(ball);
            player.draw(window);
            enemy.draw(window);
        }

        window.display();

        if (t < timer)
            t++;
    }
}