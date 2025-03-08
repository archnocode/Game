#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "mylib.hpp"
#include "body.hpp"
#include "texturemanager.hpp"

using namespace std;

class Player{
    public:

    TextureManager texture;
    Body body;

    Player(float x, float y, float speed, const string& filePath);
};

#endif //PLAYER_HPP