#ifndef ENTITY_H
#define ENTITY_H
#include "Core/ResourceManager.h"
#include "Core/Game.h"
#include "Systems/InteractiveIcon.h"
#include "Core/InputManager.h"

/*---------------------------------------------------------------------------------------*/

/*! \brief Структура контекста координатов*/
struct Coordinates
{
    // Координата x
    float x;
    // Координата y
    float y;

    // Перегрузка оператора ==
    bool operator==(const Coordinates& other) const {
        // Сравниваем с допустимой погрешностью для float
        const float epsilon = 0.0001f;
        return (std::abs(x - other.x) < epsilon) && 
               (std::abs(y - other.y) < epsilon);
    }
    
    // Перегрузка оператора !=
    bool operator!=(const Coordinates& other) const {
        return !(*this == other);
    }
};

/*---------------------------------------------------------------------------------------*/

/*! \brief Абстрактный класс сущности*/
class Entity
{
public:
    /*! \brief Конструктор класса, инициализирует координаты и ресурсы сущности*/
    /*! \param X координата x*/
    /*! \param Y координата y*/
    /*! \param resManager ссылка на ресурсы*/
    /*! \param W ширина сущности*/
    /*! \param H высота сущности*/
    Entity(float X, float Y, ResourceManager& resManager, int W, int H, InputManager& inputMng) :
        _coord{X, Y}, _resMng(resManager), _w(W), _h(H), _inputMng(inputMng), _eIcon(_resMng) {}
    virtual ~Entity() = default;

    /*! \brief Виртуальная функция обновления параметров класса*/
    /*! \param time время обновления кадра*/
    virtual void update(float time) = 0;

    /*! \brief Виртуальная функция сбрасывания параметров класса*/
    virtual void reset() = 0;

    /*! \brief Функция отрисовки спрайта объекта*/
    /*! \param window окно вывода*/
    void drawEntity(sf::RenderWindow& window) { 
        window.draw(_sprite); 
        if(_eIcon.getInteractiveZone()) {
            _eIcon.setPosition(this->getCoord());
            _eIcon.drawInterface(window);
        } 
    }

    /*! \brief Функция получения координатов объекта класса*/
    Coordinates getCoord() { return _coord; }

    void setCoord(Coordinates coord) { _coord = coord; }

    /*! \brief Функция получения ширины сущности*/
    float getWidth() { return _w; }
    
    /*! \brief Функция получения высоты сущности*/
    float getHeight() { return _h; }

    virtual void setEIcon(bool flag) { _eIcon.setInteractiveZone(flag); }
    // virtual void setAction() = 0;

protected:
    /*! \brief ссылка на ресурсы класса*/
    ResourceManager& _resMng;
    InputManager& _inputMng;
    InteractiveIcon _eIcon;
    /*! \brief координаты класса*/
    Coordinates _coord;
    /*! \brief спрайт класса*/
    sf::Sprite _sprite;
    /*! \brief Ширина и высота спрайта персонажа*/
    int _w, _h; 

    /*! \brief Виртуальная функция установки спрайта*/
    virtual void setupSprite() = 0;
};

/*---------------------------------------------------------------------------------------*/

#endif // ENTITY_H