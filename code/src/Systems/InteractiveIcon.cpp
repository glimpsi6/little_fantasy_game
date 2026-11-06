#include "Systems/InteractiveIcon.h"
#include "Entities/Entity.h"

InteractiveIcon::InteractiveIcon(ResourceManager& resManager) : UIElement(resManager), _isInteractiveZone(false)
{
    _sprite.setTexture(_resManager.getGlobalTexture("interface"));
    _sprite.setTextureRect(sf::IntRect(0, 16,  16, 16));
}

void InteractiveIcon::update()
{
    
}

void InteractiveIcon::setPosition(Coordinates coord)
{
    _sprite.setPosition(coord.x, coord.y - 20);
}

void InteractiveIcon::drawInterface(sf::RenderWindow& window)
{
    window.draw(_sprite);
}