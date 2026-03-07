#ifndef Npc_H
#define Npc_H
#include "Entities/Character.h"
#include "World/Collisions.h"

/*---------------------------------------------------------------------------------------*/

/*! \brief Класс мирных NPC, , дочерний от класса Character*/
class Npc : public Character
{
public:
    Npc(float X, float Y, ResourceManager& resManager, float W, float H, Collisions& collis);
    virtual ~Npc() = default;

    void update(float time) override;
    void reset() override;
    void setupSprite() override;
    void setMoving(float x, float y, float time, float& currentFrame); //TODO сюда проверку на коллизии чтобы не стукался

protected:
    Collisions& _collis;
    bool _isMoving;
};

/*---------------------------------------------------------------------------------------*/

#endif // Npc_H