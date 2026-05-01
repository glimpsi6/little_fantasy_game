#include "Entities/Object.h"

Object::Object(std::string objectName, float X, float Y, ResourceManager& resManager, int W, int H) :
        _objectName(objectName), Entity(X, Y, resManager, W, H)
{
    setupSprite();
}

void Object::update(float time)  
{ 
    _sprite.setPosition(_coord.x, _coord.y); 
}

void Object::reset()
{

}

void Object::setupSprite()
{
    _sprite.setTexture(_resManager.getLevelTexture(_objectName));
    _sprite.setTextureRect(sf::IntRect(0, 0, _w, _h));
}