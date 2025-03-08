#ifndef TEXTUREMANAGE_HPP
#define TEXTUREMANAGE_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class TextureManager {
    private:
        sf::Texture texture;
    
    public:
    TextureManager(const string& texturePath) {
        if (!texture.loadFromFile(texturePath)) 
            throw runtime_error("Failed to load texture");
    }
    
    const sf::Texture& getTexture() const {
        return texture;
    }
};

#endif //TEXTUREMANAGER_HPP