#ifndef CHARACTER_H
#define CHARACTER_H
#include "Entities/Entity.h"

enum Direction
{
    RIGHT, //0
    LEFT, //1
    DOWN, //2
    UP //3
};

struct movingData
{
    float dx; // ускорение по х 
    float dy; // ускорение по у
    float speed; // скорость
    Direction direct; // направление персонажа
};

struct health
{
    int maxH; // максимальное значение здоровья
    int minH; // минимальное значение здоровья
    int currH; // текущее значение здоровья
};

class Character : public Entity
{
public:
    Character(float X, float Y, ResourceManager& resManager, float W, float H) :
        Entity(X, Y, resManager), _w(W), _h(H), 
        _mD{0, 0, 0, Direction::RIGHT} {};
    virtual ~Character() = default;

    void update(float time) override = 0;
    void reset() override = 0;
    void setupSprite() override = 0;

    void setSpeed(float s) { _mD.speed = s; }
    void setDirection(enum Direction d) { _mD.direct = d; }

    float getWidth() { return _w; }
    float getHeight() { return _h; }
protected:
    float _w, _h; //ширина и высота спрайта персонажа
    movingData _mD;
};

#endif // CHARACTER_H