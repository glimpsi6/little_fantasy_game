#include "Entities/Character.h"

void Character::update(float time)
{
    switch (_mD.direct)
    {
    case Direction::RIGHT: _mD.dx = _mD.speed;    _mD.dy = 0;        break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
    case Direction::LEFT:  _mD.dx = -_mD.speed;   _mD.dy = 0;        break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
    case Direction::DOWN:  _mD.dx = 0;         _mD.dy = _mD.speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
    case Direction::UP:    _mD.dx = 0;         _mD.dy = -_mD.speed;  break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    _coord.x += _mD.dx * time;// ускорение на время получаем смещение координат и как следствие движение
    _coord.y += _mD.dy * time;//аналогично по игреку

    _mD.speed = 0;//зануляем скорость, чтобы персонаж остановился
    _collis.interactionWithMap(*this, _coord, _mD);
    _sprite.setPosition(_coord.x, _coord.y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
}
