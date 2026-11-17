#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "Core/ResourceManager.h"
#include "Core/pugixml.hpp"

class Entity;

struct CollisionObject {
    sf::FloatRect bounds;               // для прямоугольников и AABB полигонов
    std::vector<sf::Vector2f> points;   // для полигонов (мировые координаты)
    bool isPolygon = false;
};

class Map{
public:
    Map( std::string mapTileName, int W, int H, int tileSize, ResourceManager& resMng);
    ~Map() = default;
    void update(float time);
    void updateMap(std::string mapTileName);

    void drawFloorLayer(sf::RenderWindow& window);
    void drawWallsLayer(sf::RenderWindow& window);
    void drawFringeLayer(sf::RenderWindow& window);
    void drawEntities(sf::RenderWindow& window);
    const std::vector<std::vector<int>>& getFloorLayer() const { return _floorLayer; }
    const std::vector<std::vector<int>>& getWallsLayer() const { return _wallsLayer; }
    const std::vector<std::vector<int>>& getFringeLayer() const { return _fringeLayer; }
    const std::vector<std::shared_ptr<Entity>>& getEntities() const { return _entities; }
    const std::vector<CollisionObject>& getColiders() const { return _colliders; }
    void addEntity(std::shared_ptr<Entity> entity);
    
private:
    std::vector<std::vector<int>> _floorLayer;
    std::vector<std::vector<int>> _wallsLayer;
    std::vector<std::vector<int>> _fringeLayer;
    std::vector<std::shared_ptr<Entity>> _entities;
    std::vector<CollisionObject> _colliders;
    ResourceManager& _resMng;
    const sf::Texture* _tilesetTexture;
    
    int _tilesetColumns;
    int _tilesetRows; //не использую
    int _w;
    int _h;
    int _tileSize;

    std::vector<int> parseCSV(const std::string& csvLine);
    void parseCollisionObjects();
    void parseTMX();
};

#endif // MAP_H