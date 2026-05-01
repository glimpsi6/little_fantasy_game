#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "World/Map.h"

class Character;
struct movingData;
struct Coordinates;

class Collisions
{
public:
    Collisions(Map& map) : _map(map) {}
    void interactionWithMap(Character& character, Coordinates& coord, movingData& mD);
    void setCharacters(std::vector<std::shared_ptr<Character>>& characters);
    void func(Character& character, Coordinates &coord);
private:
    Map& _map;
    std::vector<std::shared_ptr<Character>>* _characters;
};

#endif // COLLISIONS_H