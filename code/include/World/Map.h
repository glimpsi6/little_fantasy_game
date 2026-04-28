#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "Core/ResourceManager.h"
#include "Entities/Npc.h"

class Map{
public:
    Map( std::string mapTileName, int W, int H, int tileSize, ResourceManager& resManager);
    void updateMap(float time);
    void updateMap(std::string mapTileName);

    void drawFloorLatyer(sf::RenderWindow& window);
    void drawWallsLatyer(sf::RenderWindow& window);
    void drawEntityLatyer(sf::RenderWindow& window);
    void drawFringeLatyer(sf::RenderWindow& window);
    void drawNPC(sf::RenderWindow& window);
    const std::vector<std::vector<int>>& getFloorLayer() const { return _floorLayer; }
    const std::vector<std::vector<int>>& getWallsLayer() const { return _wallsLayer; }
    const std::vector<std::vector<int>>& getEntityLayer() const { return _entityLayer; }
    const std::vector<std::vector<int>>& getObjectsLayer() const { return _fringeLayer; }
    const std::vector<std::shared_ptr<Npc>>& getNpcs() const { return _npcs; }
    void loadNpc(Npc& npc) { _npcs.push_back(std::make_shared<Npc>(npc)); }
    
private:
    std::vector<std::vector<int>> _floorLayer;
    std::vector<std::vector<int>> _wallsLayer;
    std::vector<std::vector<int>> _entityLayer;
    std::vector<std::vector<int>> _fringeLayer;
    std::vector<std::shared_ptr<Npc>> _npcs;
    ResourceManager& _resManager;
    const sf::Texture* _tilesetTexture;
    int _tilesetColumns;
    int _tilesetRows; //не использую
    int _w;
    int _h;
    int _tileSize;

    std::vector<int> parseCSV(const std::string& csvLine);
    void parseTMX();
};

#endif // MAP_H