#ifndef UIELEMENT_H
#define UIELEMENT_H
#include "Core/ResourceManager.h"

class UIElement{
public:
    UIElement(ResourceManager& resManager) : _resManager(resManager) {};
    virtual ~UIElement() = default;
    virtual void update() = 0;
    virtual void drawInterface(sf::RenderWindow& window) = 0;
protected:
    /*! \brief ссылка на ресурсы класса*/
    ResourceManager& _resManager;
};

#endif // UIELEMENT_H