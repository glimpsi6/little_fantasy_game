#ifndef PLAYER_H
#define PLAYER_H
#include "Entities/Character.h"
#include "Core/InputManager.h"

/*---------------------------------------------------------------------------------------*/

class Player : public Character
{
public:
    Player(float X, float Y, ResourceManager& resManager, 
           int W, int H, Collisions& collis, InputManager& inManager);
    ~Player() override = default;
    /*! \brief Функция обновления параметров класса*/
    /*! \param time время обновления кадра*/
    void reset() override;
    void handleInput(float time, float& currentFrame);
    const sf::View& getView() const { return _view; }
    void setInteractionIcon(bool flag) override {}
    
protected:
    InputManager& _inManager;
    sf::View _view;
    
    void setupSprite() override;
    sf::View getPlayerView();
};

/*---------------------------------------------------------------------------------------*/

#endif // PLAYER_H