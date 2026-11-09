#ifndef NPC_H
#define NPC_H
#include "Entities/Character.h"
#include "Systems/InteractiveIcon.h"
#include "Systems/DialogueWindow.h"

class Collisions;

/*---------------------------------------------------------------------------------------*/

/*! \brief Класс мирных NPC, дочерний от класса Character*/
class Npc : public Character
{
public:
    Npc(std::string npcName, float X, float Y, ResourceManager& resMng, 
        int W, int H, InputManager& inputMng, Collisions& collis);
    ~Npc() = default;
    void update(float time) override;
    void reset() override;
    void setMoving(float x, float y, float time, float& currentFrame);
    void drawDialogue(sf::RenderWindow& window) { _dialogue.drawInterface(window); }
    void updateDialogue() { _dialogue.update(); }
    bool getDialogueStatus() { return _isDialogue; }

private:
    void setupSprite() override;
    bool _isMoving;
    std::string _npcName;
    DialogueWindow _dialogue;
    bool _isDialogue;
};

/*---------------------------------------------------------------------------------------*/

#endif // NPC_H