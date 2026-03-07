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
}

void Collisions::setCharacters(std::vector<std::shared_ptr<Character>> &characters)
{
    _characters = &characters;
}
