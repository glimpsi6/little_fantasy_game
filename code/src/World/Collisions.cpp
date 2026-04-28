#include "World/Collisions.h"

void Collisions::interactionWithMap(Coordinates &coord, movingData &mD, int w, int h)
{
    for (int i = coord.y / TILE_SIZE; i < (coord.y + h) / TILE_SIZE; i++)
    {
        for (int j = coord.x / TILE_SIZE; j < (coord.x + w) / TILE_SIZE; j++)
        {
            int tileId = _map.getWallsLayer()[i][j];
            if (tileId != 0)
            {
                if (mD.dy > 0)
                    coord.y = i * TILE_SIZE - h; // столкновение снизу
                if (mD.dy < 0)
                    coord.y = i * TILE_SIZE + TILE_SIZE; // сверху
                if (mD.dx > 0)
                    coord.x = j * TILE_SIZE - w; // справа
                if (mD.dx < 0)
                    coord.x = j * TILE_SIZE + TILE_SIZE; // слева
            }
        }
    }

    for (size_t i = 0; i < _map.getNpcs().size(); i++)
    {
        Coordinates npcCoord = _map.getNpcs()[i]->getCoord();
        int npcH = _map.getNpcs()[i]->getHeight();
        int npcW = _map.getNpcs()[i]->getWidth();
        
        // Проверяем пересечение
        bool overlapX = (coord.x < npcCoord.x + npcW) && (coord.x + w > npcCoord.x);
        bool overlapY = (coord.y < npcCoord.y + npcH) && (coord.y + h > npcCoord.y);
        
        if (overlapX && overlapY)
        {
            // Выталкиваем в зависимости от направления движения
            if (mD.dy > 0)
                coord.y = npcCoord.y - h;
            if (mD.dy < 0)
                coord.y = npcCoord.y + npcH;
            if (mD.dx > 0)
                coord.x = npcCoord.x - w;
            if (mD.dx < 0)
                coord.x = npcCoord.x + npcW;
        }
    }

}

void Collisions::setCharacters(std::vector<std::shared_ptr<Character>> &characters)
{
    _characters = &characters;
}
