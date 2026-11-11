#ifndef INTERACTIVEICON_H
#define INTERACTIVEICON_H
#include "Systems/UIElement.h"

struct Coordinates;

class InteractiveIcon : public UIElement
{
public:
    InteractiveIcon(ResourceManager& resMng);
    ~InteractiveIcon() = default;
    void update() override;
    void drawInterface(sf::RenderWindow& window) override;

    void setInteractiveZone(bool flag) { _isInteractiveZone = flag; }
    bool getInteractiveZone() { return _isInteractiveZone; }
    void setPosition(Coordinates entity_coord, int w);
private:
    bool _isInteractiveZone;
    sf::Sprite _sprite;
};

#endif // INTERACTIVEICON_H