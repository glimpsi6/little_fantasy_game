#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "World/Map.h"
#include "Entities/Character.h"

class Collisions
{
public:
    Collisions(Map map) : _map(map) {}
    void interactionWithMap(Coordinates& coord, movingData& mD, int w, int h);
    void interactionWithCharacters(Coordinates& coord, movingData& mD, int w, int h);
    void setCharacters(std::vector<std::shared_ptr<Character>>& characters);
private:
    Map _map;
    std::vector<std::shared_ptr<Character>>* _characters;
    bool checkAABBCollision(float x1, float y1, int w1, int h1,
                        float x2, float y2, int w2, int h2); 
};

#endif // COLLISIONS_H