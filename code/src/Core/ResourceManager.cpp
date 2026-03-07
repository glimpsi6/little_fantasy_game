#include "Core/ResourceManager.h"
#include <iostream>

/*---------------------------------------------------------------------------------------*/

ResourceManager::ResourceManager()
{
    // Загрузка глобальных текстур
    loadTextures("assets/global/textures/", _globalTextures);
    // Загрузка шрифтов
    loadFonts("assets/global/fonts/", _globalFonts);
}

/*---------------------------------------------------------------------------------------*/

void ResourceManager::loadResource(enum IdnLocation idnLoc)
{
    unloadResource();

    std::string path = "assets/levels/" + std::to_string(static_cast<int>(idnLoc)) + "/textures/";
    loadTextures(path, _levelTextures);
    path = "assets/levels/" + std::to_string(static_cast<int>(idnLoc)) + "/maps/";
    loadMaps(path, _levelMaps);
    path = "assets/levels/" + std::to_string(static_cast<int>(idnLoc)) + "/sounds/";
    loadSounds(path, _levelSounds);
    
    /*нужно загрузить:
    отдельно 1 раз за игру hero.png
    0)  assets/trone_tiles.png это в текстуры 
        assets/trone_map.tmx это в карты
        пара для коридора
        пара для башни
    1)  пара для улицы деревни
        пара для таверны
        пара для церкви
        пара для дома семья
        пара для дома стражника
        пара для дома клерка
        пара для дома коллектора
    2)  пара для леса
        пара для дерева*/
} 

/*---------------------------------------------------------------------------------------*/

void ResourceManager::unloadResource()
{
    _levelTextures.clear(); 
    _levelMaps.clear();
    _levelSounds.clear(); 
} 

/*---------------------------------------------------------------------------------------*/

const sf::Texture& ResourceManager::getGlobalTexture(const std::string& id) const
{
    auto it = _globalTextures.find(id);
    if (it == _globalTextures.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

const sf::Font& ResourceManager::getGlobalFont(const std::string& id) const
{
    auto it = _globalFonts.find(id);
    if (it == _globalFonts.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

const sf::SoundBuffer& ResourceManager::getGlobalSoundBuffer(const std::string& id) const
{
    auto it = _globalSounds.find(id);
    if (it == _globalSounds.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

const sf::Texture& ResourceManager::getLevelTexture(const std::string& id) const
{
    auto it = _levelTextures.find(id);
    if (it == _levelTextures.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

const std::string& ResourceManager::getLevelMap(const std::string& id) const
{
    auto it = _levelMaps.find(id);
    if (it == _levelMaps.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

const sf::SoundBuffer& ResourceManager::getLevelSoundBuffer(const std::string& id) const
{
    auto it = _levelSounds.find(id);
    if (it == _levelSounds.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return it->second;
}

/*---------------------------------------------------------------------------------------*/

void ResourceManager::loadTextures(std::string path, std::map<std::string, sf::Texture>& textures)
{
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            size_t dotPos = filename.find_last_of('.');
            std::string name = filename.substr(0, dotPos);

            textures[name] = sf::Texture();
            textures[name].loadFromFile(path + filename); //TODO во всех лоады сделать проверку
        }
    }
}

/*---------------------------------------------------------------------------------------*/

void ResourceManager::loadMaps(std::string path, std::map<std::string, std::string>& maps)
{
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            size_t dotPos = filename.find_last_of('.');
            std::string name = filename.substr(0, dotPos);

            maps[name] = path + filename;
        }
    }
}

/*---------------------------------------------------------------------------------------*/

void ResourceManager::loadFonts(std::string path, std::map<std::string, sf::Font>& fonts)
{
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            size_t dotPos = filename.find_last_of('.');
            std::string name = filename.substr(0, dotPos);

            fonts[name] = sf::Font();
            fonts[name].loadFromFile(path + filename);
        }
    }
}

/*---------------------------------------------------------------------------------------*/

void ResourceManager::loadSounds(std::string path, std::map<std::string, sf::SoundBuffer>& sounds)
{
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            size_t dotPos = filename.find_last_of('.');
            std::string name = filename.substr(0, dotPos);

            _levelSounds[name] = sf::SoundBuffer();
            _levelSounds[name].loadFromFile(path + filename);
        }
    }
}

/*---------------------------------------------------------------------------------------*/
