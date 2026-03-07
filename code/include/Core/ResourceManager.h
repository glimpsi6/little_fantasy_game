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

/*---------------------------------------------------------------------------------------*/

//TODO сделать текстуру заглушку яркую, грузить ее в случае проблемы загрузки другой текстуры, чтобы игра не крашилась сразу

/*! \brief Класс загрузки и управления ресурсами игры*/
class ResourceManager {
public:
    /*! \brief Функция загрузки глобальных ресурсов*/
    ResourceManager();
    /*! \brief Функция загрузки ресурсов определенной локации*/
    /*! \param idnLoc идентификатор локации*/
    void loadResource(enum IdnLocation idnLoc);
    /*! \brief Функция очищения ранее загруженных ресурсов*/
    void unloadResource();

    /*! \brief Функция получения конкретной глобальной текстуры по идентификатору*/
    /*! \param id текстовый идентификатор*/
    const sf::Texture& getGlobalTexture(const std::string& id) const; 
    /*! \brief Функция получения конкретного глобального шрифта по идентификатору*/ 
    /*! \param id текстовый идентификатор*/
    const sf::Font& getGlobalFont(const std::string& id) const;
    /*! \brief Функция получения конкретного глобального звука по идентификатору*/
    /*! \param id текстовый идентификатор*/
    const sf::SoundBuffer& getGlobalSoundBuffer(const std::string& id) const;

    /*! \brief Функция получения конкретной текстуры уровня по идентификатору*/
    /*! \param id текстовый идентификатор*/
    const sf::Texture& getLevelTexture(const std::string& id) const; 
    /*! \brief Функция получения конкретной карты уровня по идентификатору*/
    /*! \param id текстовый идентификатор*/  
    const std::string& getLevelMap(const std::string& id) const;
    /*! \brief Функция получения конкретного звука уровня по идентификатору*/
    /*! \param id текстовый идентификатор*/
    const sf::SoundBuffer& getLevelSoundBuffer(const std::string& id) const;

private:
    /*! \brief Словарь для хранения глобальных текстур*/
    std::map<std::string, sf::Texture> _globalTextures; 
    /*! \brief Словарь для хранения глобальных шрифтов*/
    std::map<std::string, sf::Font> _globalFonts;
    /*! \brief Словарь для хранения глобальных звуков*/
    std::map<std::string, sf::SoundBuffer> _globalSounds;

    /*! \brief Словарь для хранения текстур уровня*/
    std::map<std::string, sf::Texture> _levelTextures; 
    /*! \brief Словарь для хранения карт уровня*/
    std::map<std::string, std::string> _levelMaps; 
    /*! \brief Словарь для хранения звуков уровня*/
    std::map<std::string, sf::SoundBuffer> _levelSounds;

    /*! \brief Функция загрузки шрифтов*/
    /*! \param path путь к дирректории, где находятся assets*/
    /*! \param textures словарь в который запишется названия шрифтов и их значение типа sf::Font*/
    void loadFonts(std::string path, std::map<std::string, sf::Font>& fonts);
    /*! \brief Функция загрузки текстур*/
    /*! \param path путь к дирректории, где находятся assets*/
    /*! \param textures словарь в который запишется названия текстур и их значения типа sf::Texture*/
    void loadTextures(std::string path, std::map<std::string, sf::Texture>& textures);
    /*! \brief Функция загрузки карт tmx*/
    /*! \param path путь к дирректории, где находятся assets*/
    /*! \param textures словарь в который запишется названия карт и пути к картам типа tmx для последующего парсига*/
    void loadMaps(std::string path, std::map<std::string, std::string>& maps);
    /*! \brief Функция загрузки звуков*/
    /*! \param path путь к дирректории, где находятся assets*/
    /*! \param textures словарь в который запишется названия звуков и их значения типа sf::SoundBuffer*/
    void loadSounds(std::string path, std::map<std::string, sf::SoundBuffer>& sounds);
};

#endif // RESOURCEMANAGER_H