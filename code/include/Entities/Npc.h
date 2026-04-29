#ifndef Npc_H
#define Npc_H
#include "Entities/Character.h"

class Collisions;

/*---------------------------------------------------------------------------------------*/

/*! \brief Класс мирных NPC, , дочерний от класса Character*/
class Npc : public Character
{
public:
    Npc(std::string npcName, float X, float Y, ResourceManager& resManager, int W, int H, Collisions& collis);
    virtual ~Npc() = default;

    void reset() override;
    void setMoving(float x, float y, float time, float& currentFrame);

protected:
    void setupSprite() override;
    bool _isMoving;
    std::string _npcName;
};

/*---------------------------------------------------------------------------------------*/

#endif // Npc_H