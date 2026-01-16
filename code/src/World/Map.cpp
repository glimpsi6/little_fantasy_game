#include "World/Map.h"

Map::Map(std::string mapTileName, int W, int H, int tileSize, ResourceManager& resManager) :
    _w(W), _h(H), _tileSize(tileSize), _resManager(resManager),
    _tilesetTexture(&_resManager.getLevelTexture(mapTileName))
{
    _tilesetColumns = (*_tilesetTexture).getSize().x / _tileSize;
    _tilesetRows = (*_tilesetTexture).getSize().y / _tileSize;

    parseTMX();
}

void Map::updateMap(std::string mapTileName)
{
    _tilesetTexture = &_resManager.getLevelTexture(mapTileName);
    _tilesetColumns = (*_tilesetTexture).getSize().x / _tileSize;
    _tilesetRows = (*_tilesetTexture).getSize().y / _tileSize;
}

void Map::drawFloorLatyer(sf::RenderWindow& window)
{
    for (int y = 0; y < _h; y++) {
        for (int x = 0; x < _w; x++) {
            int tileId = _floorLayer[y][x];
            if (tileId > 0) {
                // ID в Tiled начинаются с 1, но в спрайте с 0
                tileId--; // уменьшаем на 1
                
                // Вычисляем позицию тайла в тайлсете
                int tileXInTileset = (tileId % _tilesetColumns) * _tileSize;
                int tileYInTileset = (tileId / _tilesetColumns) * _tileSize;
                
                sf::Sprite tileSprite(*_tilesetTexture);
                tileSprite.setTextureRect(sf::IntRect(tileXInTileset, tileYInTileset, _tileSize, _tileSize));
                
                // Позиция на карте
                float posX = x * _tileSize;
                float posY = y * _tileSize;
                tileSprite.setPosition(posX, posY);
                
                window.draw(tileSprite);
            }
        }
    }
}

void Map::drawWallsLatyer(sf::RenderWindow& window) 
{
    for (int y = 0; y < _h; y++) {
        for (int x = 0; x < _w; x++) {
            int tileId = _wallsLayer[y][x];
            if (tileId > 0) {
                // Обработка флагов Tiled 
                tileId--;
                
                int tileXInTileset = (tileId % _tilesetColumns) * _tileSize;
                int tileYInTileset = (tileId / _tilesetColumns) * _tileSize;
                
                sf::Sprite tileSprite(*_tilesetTexture);
                tileSprite.setTextureRect(sf::IntRect(tileXInTileset, tileYInTileset, _tileSize, _tileSize));
                
                float posX = x * _tileSize;
                float posY = y * _tileSize;
                tileSprite.setPosition(posX, posY);
                
                window.draw(tileSprite);
        
            }
        }
    }
} 

void Map::drawEntityLatyer(sf::RenderWindow& window)
{

}

void Map::drawObjectsLatyer(sf::RenderWindow& window)
{
    for (int y = 0; y < _h; y++) {
        for (int x = 0; x < _w; x++) {
            int tileId = _objectsLayer[y][x];
            if (tileId > 0) {
                // Обработка флагов
                tileId--;

                int tileXInTileset = (tileId % _tilesetColumns) * _tileSize;
                int tileYInTileset = (tileId / _tilesetColumns) * _tileSize;
                
                sf::Sprite tileSprite(*_tilesetTexture);
                tileSprite.setTextureRect(sf::IntRect(tileXInTileset, tileYInTileset, _tileSize, _tileSize));
                
                float posX = x * _tileSize;
                float posY = y * _tileSize;
                tileSprite.setPosition(posX, posY);

                window.draw(tileSprite);
        
            }
        }
    }
}

std::vector<int> Map::parseCSV(const std::string& csvLine)
{
    std::vector<int> result;
    std::stringstream ss(csvLine);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        // Убираем лишние символы
        token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());
        token.erase(std::remove(token.begin(), token.end(), '\r'), token.end());
        token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
        
        if (!token.empty()) {
            try {
                // Пробуем преобразовать в long long чтобы избежать переполнения
                long long value = std::stoll(token);
                // Преобразуем в int (обрезаем если нужно)
                result.push_back(static_cast<int>(value));
            } catch (const std::exception& e) {
                std::cerr << "Ошибка парсинга токена: " << token << std::endl;
                result.push_back(0); // Или другое значение по умолчанию
            }
        }
    }
    
    return result;
}

void Map::parseTMX()
{
    // Читаем TMX файл
    std::ifstream tmxFile(_resManager.getLevelMap("trone_map")); 
    if (!tmxFile.is_open()) {
        std::cerr << "Не удалось открыть trone_map.tmx!" << std::endl;
    }
    
    std::string line;
    
    int currentLayer = -1; // -1 = не в слое, 0 = floor, 1 = walls, 2 = objects
    
    // Парсим TMX построчно
    while (std::getline(tmxFile, line)) {
        // Ищем начало слоя
        if (line.find("<layer id=\"1\"") != std::string::npos) {
            currentLayer = 0; // floor
            _floorLayer.resize(_h, std::vector<int>(_w, 0));
        }
        else if (line.find("<layer id=\"2\"") != std::string::npos) {
            currentLayer = 1; // walls
            _wallsLayer.resize(_h, std::vector<int>(_w, 0));
        }
        else if (line.find("<layer id=\"3\"") != std::string::npos) {
            currentLayer = 2; // objects
            _objectsLayer.resize(_h, std::vector<int>(_w, 0));
        }
        // Ищем данные слоя
        else if (currentLayer >= 0 && line.find("<data encoding=\"csv\">") != std::string::npos) {
            // Читаем следующие строки пока не встретим </data>
            int row = 0;
            while (std::getline(tmxFile, line) && line.find("</data>") == std::string::npos) {
                std::vector<int> rowData = parseCSV(line);
                
                if (rowData.size() == _w && row < _h) {
                    if (currentLayer == 0) {
                        _floorLayer[row] = rowData;
                    }
                    else if (currentLayer == 1) {
                        _wallsLayer[row] = rowData;
                    }
                    else if (currentLayer == 2) {
                        _objectsLayer[row] = rowData;
                    }
                    row++;
                }
            }
            currentLayer = -1; // Сброс после чтения данных
        }
    }
    
    tmxFile.close();
}