#include "Systems/InteractiveIcon.h"
#include "Entities/Entity.h"

InteractiveIcon::InteractiveIcon(ResourceManager& resMng) : UIElement(resMng), _isInteractiveZone(false)
{
    _sprite.setTexture(_resMng.getGlobalTexture("eIcon"));
    _sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); //todo убрать magic num
}

void InteractiveIcon::update()
{
    
}

void InteractiveIcon::setPosition(Coordinates entity_coord, int w)
{
    float x = entity_coord.x;
    if(w > 16) { //todo убрать magic num
        x += (w - 16) / 2;
    }

    float y = entity_coord.y - 20;
    _sprite.setPosition(x, y);
}

void InteractiveIcon::drawInterface(sf::RenderWindow& window)
{
    window.draw(_sprite);
}