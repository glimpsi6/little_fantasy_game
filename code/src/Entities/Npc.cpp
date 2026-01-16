#include "Entities/Npc.h"

Npc::Npc(float X, float Y, ResourceManager& resManager, float W, float H, Collisions& collis) :
        Character(X, Y, resManager, W, H), _collis(collis)
{
    _isMoving = false;
    setupSprite();
}

void Npc::update(float time)
{
    _sprite.setPosition(_coord.x, _coord.y);
}

void Npc::reset()
{

}

void Npc::setupSprite()
{
    _sprite.setTexture(_resManager.getGlobalTexture("hero"));
    _sprite.setTextureRect(sf::IntRect(0, 0, _w, _h));
}

void Npc::setMoving(float x, float y, float time, float& currentFrame)
{
    //считаем направление от нынешних координат до вверденных и выставляем соотвествующее направление и спрайты
    
    
    // setDirection(Direction::LEFT);
    // setSpeed(0.1);
    // currentFrame += 0.004*time;
    // if (currentFrame > 2) currentFrame -= 2; 
    // _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 16, 16, 16));
}