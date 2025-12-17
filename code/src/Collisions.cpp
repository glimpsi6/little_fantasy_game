#include "Collisions.h"

void Collisions::interactionWithMap(Coordinates& coord, movingData& mD, int w, int h)
{
    for (int i = coord.y / 16; i < (coord.y + h) / 16; i++) {
        for (int j = coord.x / 16; j < (coord.x + w) / 16; j++) {
            int tileId = _map.getWallsLayer()[i][j];
            if (tileId != 0) {
                if (mD.dy > 0) coord.y = i * 16 - h;   // столкновение снизу
                if (mD.dy < 0) coord.y = i * 16 + 16;  // сверху
                if (mD.dx > 0) coord.x = j * 16 - w;   // справа
                if (mD.dx < 0) coord.x = j * 16 + 16;  // слева
            }
        }
    }
}