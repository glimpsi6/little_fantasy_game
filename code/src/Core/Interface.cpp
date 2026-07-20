#include "Core/Interface.h"

Interface::Interface(ResourceManager& resManager) : _resManager(resManager), _isInteractiveZone(false)
{
    _interactiveIcon.setTexture(_resManager.getGlobalTexture("interface"));
    _interactiveIcon.setTextureRect(sf::IntRect(0, 16,  16, 16));
}

void Interface::update()
{
    
}