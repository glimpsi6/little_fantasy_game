#ifndef DIALOGUEWINDOW_H
#define DIALOGUEWINDOW_H
#include "Systems/UIElement.h"
#include "Core/InputManager.h"
#include "Core/Game.h"

class DialogueWindow : public UIElement
{
public:
    DialogueWindow(std::string npcName, bool& dialogueStatus, ResourceManager& resMng, InputManager& inputMng);
    ~DialogueWindow() = default;
    void startDialogue();
    void update() override;
    void drawInterface(sf::RenderWindow& window) override;
private:
    InputManager& _inputMng;
    bool& _dialogueStatus;
};

#endif // DIALOGUEWINDOW_H