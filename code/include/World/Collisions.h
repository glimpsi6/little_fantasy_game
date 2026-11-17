#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "World/Map.h"

class Character;
struct movingData;
struct Coordinates;

constexpr int radius = 25;

class Collisions
{
public:
    Collisions(Map& map) : _map(map) {}
    void interactionWithMap(Character& character);
    void interactionPlayerWithNPC(Character& character);
private:
    Map& _map;
};

#endif // COLLISIONS_H