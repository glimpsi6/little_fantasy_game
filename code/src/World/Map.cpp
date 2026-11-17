#include "World/Map.h"
#include "Entities/Entity.h"

Map::Map(std::string mapTileName, int W, int H, int tileSize, ResourceManager& resMng) :
    _w(W), _h(H), _tileSize(tileSize), _resMng(resMng),
    _tilesetTexture(&_resMng.getLevelTexture(mapTileName))
{
    _tilesetColumns = (*_tilesetTexture).getSize().x / _tileSize;
    _tilesetRows = (*_tilesetTexture).getSize().y / _tileSize;


    parseTMX();
    parseCollisionObjects();
}

void Map::update(float time)
{
    for(size_t i = 0; i < _entities.size(); i++) {
        _entities[i]->update(time);
    }
}

void Map::updateMap(std::string mapTileName)
{
    _tilesetTexture = &_resMng.getLevelTexture(mapTileName);
    _tilesetColumns = (*_tilesetTexture).getSize().x / _tileSize;
    _tilesetRows = (*_tilesetTexture).getSize().y / _tileSize;
}

void Map::drawFloorLayer(sf::RenderWindow& window)
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

void Map::drawWallsLayer(sf::RenderWindow& window) 
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

void Map::drawFringeLayer(sf::RenderWindow& window)
{
    for (int y = 0; y < _h; y++) {
        for (int x = 0; x < _w; x++) {
            int tileId = _fringeLayer[y][x];
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

void Map::drawEntities(sf::RenderWindow& window)
{
    for(size_t i = 0; i < _entities.size(); i++) {
        _entities[i]->drawEntity(window);
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

void Map::parseCollisionObjects() 
{
    pugi::xml_document doc;

    if (!doc.load_file(_resMng.getLevelMap("trone_map").c_str())) {
        std::cerr << "Failed to load trone_map.tmx\n";
        return;
    }

    pugi::xml_node mapNode = doc.child("map");
    if (!mapNode) {
        std::cerr << "No <map> node in TMX\n";
        return;
    }

    for (pugi::xml_node group : mapNode.children("objectgroup")) {
        if (std::string(group.attribute("name").as_string()) != "border")
            continue;

        for (pugi::xml_node obj : group.children("object")) {
            CollisionObject col;

            float objX = obj.attribute("x").as_float();
            float objY = obj.attribute("y").as_float();
            float w    = obj.attribute("width").as_float(0.f);
            float h    = obj.attribute("height").as_float(0.f);

            pugi::xml_node polyNode = obj.child("polygon");
            if (polyNode) {
                col.isPolygon = true;
                // Парсим "points": "0,0 40,-20 80,0"
                std::string pts = polyNode.attribute("points").as_string();
                std::stringstream ss(pts);
                std::string pair;
                while (ss >> pair) {
                    size_t comma = pair.find(',');
                    if (comma != std::string::npos) {
                        float px = std::stof(pair.substr(0, comma));
                        float py = std::stof(pair.substr(comma + 1));
                        // Мировые координаты = позиция объекта + точка
                        col.points.emplace_back(objX + px, objY + py);
                    }
                }
                // Вычисляем AABB для быстрой отсечки
                if (!col.points.empty()) {
                    float minX = col.points[0].x, maxX = minX;
                    float minY = col.points[0].y, maxY = minY;
                    for (auto& p : col.points) {
                        minX = std::min(minX, p.x); maxX = std::max(maxX, p.x);
                        minY = std::min(minY, p.y); maxY = std::max(maxY, p.y);
                    }
                    col.bounds = sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
                }
            } else {
                // Прямоугольник
                col.bounds = sf::FloatRect(objX, objY, w, h);
            }

            _colliders.push_back(std::move(col));
        }
    }
}

void Map::parseTMX()
{
    // Читаем TMX файл
    std::ifstream tmxFile(_resMng.getLevelMap("trone_map")); 
    if (!tmxFile.is_open()) {
        std::cerr << "Не удалось открыть trone_map.tmx!" << std::endl;
    }
    
    std::string line;
    
    int currentLayer = -1;
    
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
            currentLayer = 2; // fringes
            _fringeLayer.resize(_h, std::vector<int>(_w, 0));
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
                        _fringeLayer[row] = rowData;
                    }
                    row++;
                }
            }
            currentLayer = -1; // Сброс после чтения данных
        }
    }
    
    tmxFile.close();
}

void Map::addEntity(std::shared_ptr<Entity> entity) 
{ 
    _entities.push_back(entity);
}