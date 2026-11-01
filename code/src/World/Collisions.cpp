#include "World/Collisions.h"
#include "Entities/Character.h"

void Collisions::interactionWithMap(Character& character, Coordinates &coord, movingData &mD)
{
    for (int i = coord.y / TILE_SIZE; i < (coord.y + character.getHeight()) / TILE_SIZE; i++)
    {
        for (int j = coord.x / TILE_SIZE; j < (coord.x + character.getWidth()) / TILE_SIZE; j++)
        {
            int mapTileId = _map.getWallsLayer()[i][j];
            if (mapTileId != 0)
            {
                if (mD.dy > 0)
                    coord.y = i * TILE_SIZE - character.getHeight(); // столкновение снизу
                if (mD.dy < 0)
                    coord.y = i * TILE_SIZE + TILE_SIZE; // сверху
                if (mD.dx > 0)
                    coord.x = j * TILE_SIZE - character.getWidth(); // справа
                if (mD.dx < 0)
                    coord.x = j * TILE_SIZE + TILE_SIZE; // слева
            }
        }
    }

    for (size_t i = 0; i < _map.getEntities().size(); i++)
    {
        if(&character == _map.getEntities()[i].get()) continue;

        Coordinates npcCoord = _map.getEntities()[i]->getCoord();
        int npcH = _map.getEntities()[i]->getHeight();
        int npcW = _map.getEntities()[i]->getWidth();
        
        // Проверяем пересечение
        bool overlapX = (coord.x < npcCoord.x + npcW) && (coord.x + character.getWidth() > npcCoord.x);
        bool overlapY = (coord.y < npcCoord.y + npcH) && (coord.y + character.getHeight() > npcCoord.y);
        
        if (overlapX && overlapY)
        {
            // Выталкиваем в зависимости от направления движения
            if (mD.dy > 0)
                coord.y = npcCoord.y - character.getHeight();
            if (mD.dy < 0)
                coord.y = npcCoord.y + npcH;
            if (mD.dx > 0)
                coord.x = npcCoord.x - character.getWidth();
            if (mD.dx < 0)
                coord.x = npcCoord.x + npcW;
        }
    }
}

void Collisions::setCharacters(std::vector<std::shared_ptr<Character>> &characters)
{
    _characters = &characters;
}