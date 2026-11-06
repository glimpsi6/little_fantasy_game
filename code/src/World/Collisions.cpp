#include "World/Collisions.h"
#include "Entities/Character.h"

void Collisions::interactionWithMap(Character& ch, Coordinates& coord)
{ 
    for (int i = ch.getCoord().y / TILE_SIZE; i < (ch.getCoord().y + ch.getHeight()) / TILE_SIZE; i++)
    {
        for (int j = ch.getCoord().x / TILE_SIZE; j < (ch.getCoord().x + ch.getWidth()) / TILE_SIZE; j++)
        {
            int mapTileId = _map.getWallsLayer()[i][j];
            if (mapTileId != 0)
            {
                if (ch.getSeed().dy > 0)
                    coord.y = i * TILE_SIZE - ch.getHeight(); // столкновение снизу
                if (ch.getSeed().dy < 0)
                    coord.y = i * TILE_SIZE + TILE_SIZE; // сверху
                if (ch.getSeed().dx > 0)
                    coord.x = j * TILE_SIZE - ch.getWidth(); // справа
                if (ch.getSeed().dx < 0)
                    coord.x = j * TILE_SIZE + TILE_SIZE; // слева
            }
        }
    }

    for (size_t i = 0; i < _map.getEntities().size(); i++)
    {
        if(&ch == _map.getEntities()[i].get()) continue;

        Coordinates npcCoord = _map.getEntities()[i]->getCoord();
        int npcH = _map.getEntities()[i]->getHeight();
        int npcW = _map.getEntities()[i]->getWidth();

        if( (ch.getCoord().x - npcCoord.x < radius && npcCoord.x - ch.getCoord().x < radius) &
            (ch.getCoord().y - npcCoord.y < radius && npcCoord.y - ch.getCoord().y < radius)) {
            _map.getEntities()[i]->setEIcon(true);
        } else {
            _map.getEntities()[i]->setEIcon(false);
        }
 
        // Проверяем пересечение
        bool overlapX = (ch.getCoord().x < npcCoord.x + npcW) && (ch.getCoord().x + ch.getWidth() > npcCoord.x);
        bool overlapY = (ch.getCoord().y < npcCoord.y + npcH) && (ch.getCoord().y + ch.getHeight() > npcCoord.y);
        
        if (overlapX && overlapY)
        {
            // Выталкиваем в зависимости от направления движения
            if (ch.getSeed().dy > 0)
                coord.y = npcCoord.y - ch.getHeight();
            if (ch.getSeed().dy < 0)
                coord.y = npcCoord.y + npcH;
            if (ch.getSeed().dx > 0)
                coord.x = npcCoord.x - ch.getWidth();
            if (ch.getSeed().dx < 0)
                coord.x = npcCoord.x + npcW;
        }
    }

}

// void Collisions::setCharacters(std::vector<std::shared_ptr<Character>> &characters)
// {
//     _characters = &characters;
// }