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
    void interactionWithMap(Character& character, Coordinates& coord);
    // void setCharacters(std::vector<std::shared_ptr<Character>>& characters);
private:
    Map& _map;
    std::vector<std::shared_ptr<Character>>* _characters;
};

#endif // COLLISIONS_H