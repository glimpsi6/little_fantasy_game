#include "Systems/Frame.h"

Frame::Frame(ResourceManager& resMng) : UIElement(resMng)
{
    _sprite.setTexture(_resMng.getGlobalTexture("frame"));
    _sprite.setTextureRect(sf::IntRect(0, 0, 640, 480));
}

void Frame::update()
{
    
}

void Frame::drawInterface(sf::RenderWindow& window)
{
    window.draw(_sprite);
}