#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "Core/Game.h"

class ResourceManager {
public:
    ResourceManager();

    void loadResource(enum IdnLocation idnLoc);
    void unloadResource();

    const sf::Texture& getGlobalTexture(const std::string& id) const;  
    const sf::Font& getGlobalFont(const std::string& id) const;
    const sf::SoundBuffer& getGlobalSoundBuffer(const std::string& id) const;

    const sf::Texture& getLevelTexture(const std::string& id) const;   
    const std::string& getLevelMap(const std::string& id) const;
    const sf::SoundBuffer& getLevelSoundBuffer(const std::string& id) const;

private:
    std::map<std::string, sf::Texture> _globalTextures; 
    std::map<std::string, sf::Font> _globalFonts;
    std::map<std::string, sf::SoundBuffer> _globalSounds;

    std::map<std::string, sf::Texture> _levelTextures; 
    std::map<std::string, std::string> _levelMaps; 
    std::map<std::string, sf::SoundBuffer> _levelSounds;

    void loadFonts(std::string path, std::map<std::string, sf::Font>& fonts);
    void loadTextures(std::string path, std::map<std::string, sf::Texture>& textures);
    void loadMaps(std::string path, std::map<std::string, std::string>& maps);
    void loadSounds(std::string path, std::map<std::string, sf::SoundBuffer>& sounds);
};

#endif // RESOURCEMANAGER_H