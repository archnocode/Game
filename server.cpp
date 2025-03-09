#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

std::vector<sf::TcpSocket*> clients;
std::mutex clientsMutex;

void handleClient(sf::TcpSocket* client) {
    char buffer[1024];
    std::size_t received;

    std::string clientsize = std::to_string(clients.size()-1);
    if (client->send(clientsize.c_str(), clientsize.size()) != sf::Socket::Status::Done){
        std::cout << "Не удалось отправить клиенту id" << std::endl;
    }

    while (true) {
        if (client->receive(buffer, sizeof(buffer), received) != sf::Socket::Status::Done) {
            std::cerr << "Клиент отключился" << std::endl;
            break;
        }

        std::string message(buffer, received);
        std::cout << "Получено сообщение: " << message << std::endl;

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            for (auto& otherClient : clients) {
                if (otherClient != client) {
                    std::cout << message << std::endl; 
                    if (otherClient->send(message.c_str(), message.size()) != sf::Socket::Status::Done) {
                        std::cerr << "Не удалось отправить сообщение клиенту" << std::endl;
                    }
                }
            }
        }
    }

    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
    }

    delete client;
}

int main() {
    sf::TcpListener listener;

    if (listener.listen(12345) != sf::Socket::Status::Done) {
        std::cerr << "Не удалось привязать сокет к порту 12345" << std::endl;
        return 1;
    }

    std::cout << "Сервер запущен и ожидает подключения..." << std::endl;

    while (true) {
        sf::TcpSocket* client = new sf::TcpSocket;

        if (clients.size() < 2){
            if (listener.accept(*client) != sf::Socket::Status::Done) {
                std::cerr << "Не удалось принять подключение" << std::endl;
                delete client;
                continue;
            }
        }

        std::cout << "Новый клиент подключен!" << std::endl;

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(client);
        }

        std::thread clientThread(handleClient, client);
        clientThread.detach(); 
    }

    return 0;
}