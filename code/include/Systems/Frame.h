#ifndef FRAME_H
#define FRAME_H
#include "Systems/UIElement.h"

class Frame : public UIElement
{
public:
    Frame(ResourceManager& resMng);
    ~Frame() = default;
    void update() override;
    void drawInterface(sf::RenderWindow& window) override;
private:
    sf::Sprite _sprite;
};

#endif // FRAME_H