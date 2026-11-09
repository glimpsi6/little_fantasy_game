#ifndef PLAYER_H
#define PLAYER_H
#include "Entities/Character.h"

/*---------------------------------------------------------------------------------------*/

class Player : public Character
{
public:
    Player(float X, float Y, ResourceManager& resMng, 
           int W, int H, InputManager& inputMng, Collisions& collis);
    ~Player() override = default;
    /*! \brief Функция обновления параметров класса*/
    /*! \param time время обновления кадра*/
    void update(float time) override;
    void reset() override;
    void handleInput(float time, float& currentFrame);
    const sf::View& getView() const { return _view; }
    void setEIcon(bool flag) override {}
    
private:
    sf::View _view;
    
    void setupSprite() override;
    sf::View getPlayerView();
};

/*---------------------------------------------------------------------------------------*/

#endif // PLAYER_H