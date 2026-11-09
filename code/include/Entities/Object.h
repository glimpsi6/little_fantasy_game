#ifndef OBJECT_H
#define OBJECT_H
#include "Entities/Entity.h"

/*---------------------------------------------------------------------------------------*/

/*! \brief Класс объектов, дочерний от класса Entity*/
class Object : public Entity
{
public:
    Object(std::string npcName, float X, float Y, ResourceManager& resMng, int W, int H, InputManager& inputMng);
    ~Object() = default;
    /*! \brief Функция обновления параметров класса*/
    /*! \param time время обновления кадра*/
    void update(float time) override;
    void reset() override;

protected:
    void setupSprite() override;
    std::string _objectName;
};

/*---------------------------------------------------------------------------------------*/

#endif // OBJECT_H