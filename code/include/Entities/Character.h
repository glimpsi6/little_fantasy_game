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

class Character : public Entity
{
public:
    /*! \brief Конструктор класса, инициализирует координаты, ресурсы персонажа, его высоту и ширину*/
    /*! \param X координата x*/
    /*! \param Y координата y*/
    /*! \param resMng ссылка на ресурсы*/
    /*! \param W ширина персонажа*/
    /*! \param H высота персонажа*/
    Character(float X, float Y, ResourceManager& resMng, int W, int H, InputManager& inputMng, Collisions& collis) :
        Entity(X, Y, resMng, W, H, inputMng), 
        _mD{0, 0, 0, Direction::RIGHT}, _collis(collis) {};
    virtual ~Character() = default;
    void update(float time) override = 0;
    void reset() override = 0;
    void setupSprite() override = 0;
    void setSpeed(float s) { _mD.speed = s; }
    movingData getSeed() { return _mD; }
    void setDirection(enum Direction d) { _mD.direct = d; }
protected:
    movingData _mD;
    Collisions& _collis;
};

/*---------------------------------------------------------------------------------------*/

#endif // CHARACTER_H