#ifndef INTERFACE_H
#define INTERFACE_H
#include "Core/ResourceManager.h"
#include "Entities/Entity.h"

class Interface{
public:
    Interface(ResourceManager& resManager);
    ~Interface() = default;
    void update();

    void setInteractiveZoneTrue() { _isInteractiveZone = true; }
    void setInteractiveZoneFalse() { _isInteractiveZone = false; }
    bool getInteractiveZone() { return _isInteractiveZone; }
    void setPositionInteractiveIcon(Coordinates coord);
    void drawInterface(sf::RenderWindow window);
private:
    /*! \brief ссылка на ресурсы класса*/
    ResourceManager& _resManager;
    bool _isInteractiveZone;
    sf::Sprite _interactiveIcon;
    sf::Sprite _frame;
};

#endif // INTERFACE_H