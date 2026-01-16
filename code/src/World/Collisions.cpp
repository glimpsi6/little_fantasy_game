#include "World/Collisions.h"

void Collisions::interactionWithMap(Coordinates &coord, movingData &mD, int w, int h)
{
    for (int i = coord.y / 16; i < (coord.y + h) / 16; i++)
    {
        for (int j = coord.x / 16; j < (coord.x + w) / 16; j++)
        {
            int tileId = _map.getWallsLayer()[i][j];
            if (tileId != 0)
            {
                if (mD.dy > 0)
                    coord.y = i * 16 - h; // столкновение снизу
                if (mD.dy < 0)
                    coord.y = i * 16 + 16; // сверху
                if (mD.dx > 0)
                    coord.x = j * 16 - w; // справа
                if (mD.dx < 0)
                    coord.x = j * 16 + 16; // слева
            }
        }
    }

    // interactionWithCharacters(coord, mD, w, h);
}

void Collisions::setCharacters(std::vector<std::shared_ptr<Character>> &characters)
{
    _characters = &characters;
}

void Collisions::interactionWithCharacters(Coordinates &coord, movingData &mD, int w, int h)
{
    for (const auto &character : *_characters)
    {
        // Пропускаем самого себя
        if (character->getCoord() == coord)
            continue;

        // Получаем данные другого персонажа
        Coordinates otherCoord = character->getCoord();
        int otherW = character->getWidth();
        int otherH = character->getHeight();

        // Проверяем столкновение AABB
        if (checkAABBCollision(coord.x, coord.y, w, h,
                               otherCoord.x, otherCoord.y, otherW, otherH))
        {
            // Вычисляем глубину проникновения
            float overlapX = std::min(coord.x + w, otherCoord.x + otherW) -
                             std::max(coord.x, otherCoord.x);
            float overlapY = std::min(coord.y + h, otherCoord.y + otherH) -
                             std::max(coord.y, otherCoord.y);

            // Разрешаем столкновение в сторону наименьшего перекрытия
            if (overlapX < overlapY)
            {
                // Столкновение по горизонтали
                if (mD.dx > 0)
                    coord.x = otherCoord.x - w; // справа
                else if (mD.dx < 0)
                    coord.x = otherCoord.x + otherW; // слева
            }
            else
            {
                // Столкновение по вертикали
                if (mD.dy > 0)
                    coord.y = otherCoord.y - h; // снизу
                else if (mD.dy < 0)
                    coord.y = otherCoord.y + otherH; // сверху
            }
        }
    }
}

bool Collisions::checkAABBCollision(float x1, float y1, int w1, int h1,
                                    float x2, float y2, int w2, int h2)
{
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}