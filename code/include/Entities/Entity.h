#ifndef ENTITY_H
#define ENTITY_H
#include "Core/ResourceManager.h"
#include "Core/Game.h"

struct Coordinates
{
    float x;
    float y;

    // Перегрузка оператора ==
    bool operator==(const Coordinates& other) const {
        // Сравниваем с допустимой погрешностью для float
        const float epsilon = 0.0001f;
        return (std::abs(x - other.x) < epsilon) && 
               (std::abs(y - other.y) < epsilon);
    }
    
    // Перегрузка оператора !=
    bool operator!=(const Coordinates& other) const {
        return !(*this == other);
    }
};

class Entity
{
public:
    Entity(float X, float Y, ResourceManager& resManager) :
        _coord{X, Y}, _resManager(resManager) {}
    virtual ~Entity() = default;

    virtual void update(float time) = 0;
    virtual void reset() = 0;
    void drawEntity(sf::RenderWindow& window) { window.draw(_sprite); }
    Coordinates getCoord() { return _coord; }

protected:
    ResourceManager& _resManager;
    Coordinates _coord;
    sf::Sprite _sprite;

    virtual void setupSprite() = 0;
};

#endif // ENTITY_H