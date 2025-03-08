#include "player.hpp"

Player::Player(float x, float y, float speed, const string& filePath) : texture(filePath), body(x, y, texture){}