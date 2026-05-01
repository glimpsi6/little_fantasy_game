#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entities/Entity.h"
#include "World/Collisions.h"

/*---------------------------------------------------------------------------------------*/

/*! \brief Перечисление направлений движения объекта*/
enum Direction
{
    RIGHT, //0
    LEFT, //1
    DOWN, //2
    UP //3
};

/*---------------------------------------------------------------------------------------*/

/*! \brief Структура контекста о пермещении*/
struct movingData
{
    float dx; // ускорение по х 
    float dy; // ускорение по у
    float speed; // скорость
    Direction direct; // направление персонажа
};

/*---------------------------------------------------------------------------------------*/

/*! \brief Структура контекста о здоровье объекта*/
struct health
{
    int maxH; // максимальное значение здоровья
    int minH; // минимальное значение здоровья
    int currH; // текущее значение здоровья
};

/*---------------------------------------------------------------------------------------*/

/*! \brief Абстрактный класс персонажа, дочерний от класса Entity*/
class Character : public Entity
{
public:
    /*! \brief Конструктор класса, инициализирует координаты, ресурсы персонажа, его высоту и ширину*/
    /*! \param X координата x*/
    /*! \param Y координата y*/
    /*! \param resManager ссылка на ресурсы*/
    /*! \param W ширина персонажа*/
    /*! \param H высота персонажа*/
    Character(float X, float Y, ResourceManager& resManager, int W, int H, Collisions& collis) :
        Entity(X, Y, resManager, W, H), 
        _mD{0, 0, 0, Direction::RIGHT}, _collis(collis) {};
    /*! \brief Виртуальная функция деструктора*/
    virtual ~Character() = default;
    /*! \brief Функция обновления параметров класса*/
    /*! \param time время обновления кадра*/
    void update(float time) override;
    /*! \brief Функция сбрасывания параметров класса*/
    void reset() override = 0;
    /*! \brief Функция установки спрайта*/
    void setupSprite() override = 0;
    /*! \brief Функция установления скорости*/
    /*! \param s скорость*/
    void setSpeed(float s) { _mD.speed = s; }
    /*! \brief Функция установления направления*/
    /*! \param d направление*/
    void setDirection(enum Direction d) { _mD.direct = d; }
protected:
    /*! \brief Контекст перемещения персонажа*/
    movingData _mD;
    Collisions& _collis;
};

/*---------------------------------------------------------------------------------------*/

#endif // CHARACTER_H