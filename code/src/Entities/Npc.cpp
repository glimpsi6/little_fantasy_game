#include "Entities/Npc.h"
#include "World/Collisions.h"

Npc::Npc(std::string npcName, float X, float Y, ResourceManager& resMng, int W, int H, InputManager& inputMng, Collisions& collis) :
        _npcName(npcName), Character(X, Y, resMng, W, H, inputMng, collis), _isDialogue(false), _dialogue(npcName, _isDialogue, resMng, inputMng)
{
    _isMoving = false;
    setupSprite();
}

void Npc::update(float time)
{
    _mD.speed = 0;
    _collis.interactionWithMap(*this, _coord);
    _sprite.setPosition(_coord.x, _coord.y);

    if(_eIcon.getInteractiveZone() && _inputMng.isKeyJustPressed(sf::Keyboard::E) && state == GameState::Playing) {
        _dialogue.startDialogue();
    }
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
