#include "Entities/Npc.h"
#include "World/Collisions.h"

Npc::Npc(std::string npcName, float X, float Y, ResourceManager& resManager, int W, int H, InputManager& inputMng, Collisions& collis) :
        _npcName(npcName), Character(X, Y, resManager, W, H, inputMng, collis)
{
    _isMoving = false;
    setupSprite();
}

void Npc::reset()
{

}

void Npc::setupSprite()
{
    _sprite.setTexture(_resMng.getLevelTexture(_npcName));
    _sprite.setTextureRect(sf::IntRect(0, 64, _w, _h));
}

void Npc::setMoving(float x, float y, float time, float& currentFrame)
{
    
}