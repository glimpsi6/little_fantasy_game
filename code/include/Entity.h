#ifndef ENTITY_H
#define ENTITY_H
#include "ResourceManager.h"
#include "Game.h"

struct Coordinates
{
    float x;
    float y;
};

class Entity
{
public:
    Entity(float X, float Y, ResourceManager& resManager) :
        _coord{X, Y}, _resManager(resManager) {}
    virtual ~Entity() = default;

    virtual void update(float time) = 0;
    virtual void reset() = 0;
    const sf::Sprite getSprite() const { return _sprite; }

protected:
    ResourceManager& _resManager;
    Coordinates _coord;
    sf::Sprite _sprite;

    virtual void setupSprite() = 0;
};

#endif // ENTITY_H