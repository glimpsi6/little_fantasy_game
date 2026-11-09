#include "Systems/DialogueWindow.h"

DialogueWindow::DialogueWindow(std::string npcName, bool& dialogueStatus, ResourceManager& resMng, InputManager& inputMng) :
    UIElement(resMng), _inputMng(inputMng), _dialogueStatus(dialogueStatus)
{
    //загрузка текстур и текста для npcName
}

void DialogueWindow::startDialogue()
{
    state = GameState::Dialogue;
    _dialogueStatus = true;
}

void DialogueWindow::update()
{
    //вывод текста построчно из txt, если нажат энтер в inputMng переходим на новую строчку
    // когда дошли до конца нужно сменить state

    // if(state == GameState::Dialogue) {


    //     state = GameState::Playing;
    //     _dialogueStatus = false;
    // }
}

void DialogueWindow::drawInterface(sf::RenderWindow& window)
{
    //отрисовка пнг с нпс на весь экран
    //отрисовка окна

}