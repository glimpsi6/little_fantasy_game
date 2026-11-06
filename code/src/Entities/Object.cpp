#include "Entities/Object.h"

Object::Object(std::string objectName, float X, float Y, ResourceManager& resManager, int W, int H, InputManager& inputMng) :
        _objectName(objectName), Entity(X, Y, resManager, W, H, inputMng)
{
    setupSprite();
}

void Object::update(float time)  
{ 
    _sprite.setPosition(_coord.x, _coord.y); 

    if(_eIcon.getInteractiveZone() && _inputMng.isKeyJustPressed(sf::Keyboard::E)) {
        //todo действие с предметом
    }
}

void Object::reset()
{

}

void Object::setupSprite()
{
    _sprite.setTexture(_resMng.getLevelTexture(_objectName));
    _sprite.setTextureRect(sf::IntRect(0, 0, _w, _h));
}