#include "Entities/Npc.h"
#include "World/Collisions.h"

Npc::Npc(std::string npcName, float X, float Y, ResourceManager& resManager, int W, int H, Collisions& collis) :
        _npcName(npcName), Character(X, Y, resManager, W, H, collis)
{
    _isMoving = false;
    setupSprite();
}

void Npc::reset()
{

}

void Npc::setupSprite()
{
    _sprite.setTexture(_resManager.getLevelTexture(_npcName));
    _sprite.setTextureRect(sf::IntRect(0, 0, _w, _h));
}

void Npc::setMoving(float x, float y, float time, float& currentFrame)
{
    
}