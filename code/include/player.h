#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "InputManager.h"
#include "Сollisions.h"

class Player : public Character
{
public:
    Player(float X, float Y, ResourceManager& resManager, 
           float W, float H, InputManager& inManager, Collisions& collis);
    ~Player() override = default;

    void update(float time) override;
    void reset() override;

    void handleInput(float time, float& currentFrame);
    const sf::View& getView() const { return _view; }
    
protected:
    InputManager& _inManager;
    Collisions& _collis;
    sf::View _view;

    void setupSprite() override;
    sf::View getPlayerView();
};

#endif // PLAYER_H