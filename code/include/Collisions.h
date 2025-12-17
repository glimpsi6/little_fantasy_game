#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "Map.h"
#include "Entity.h"
#include "Character.h"

class Collisions
{
public:
    Collisions(Map map) : _map(map) {}
    void interactionWithMap(Coordinates& coord, movingData& mD, int w, int h);
private:
    Map _map;
};

#endif // COLLISIONS_H