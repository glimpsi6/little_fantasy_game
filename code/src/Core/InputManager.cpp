#include "Core/InputManager.h"

void InputManager::update() {
    // WASD
    m_keyStates[sf::Keyboard::W] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    m_keyStates[sf::Keyboard::A] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    m_keyStates[sf::Keyboard::S] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    m_keyStates[sf::Keyboard::D] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    // Стрелки
    m_keyStates[sf::Keyboard::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    m_keyStates[sf::Keyboard::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    m_keyStates[sf::Keyboard::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    m_keyStates[sf::Keyboard::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    // Карта
    m_keyStates[sf::Keyboard::M] = sf::Keyboard::isKeyPressed(sf::Keyboard::M);
    // Меню
    m_keyStates[sf::Keyboard::Escape] = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    // Подтверджение выбора
    m_keyStates[sf::Keyboard::Enter] = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    // Взаимодействие
    m_keyStates[sf::Keyboard::E] = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
}
    
bool InputManager::isKeyPressed(sf::Keyboard::Key key) const {
    auto it = m_keyStates.find(key);
    return (it != m_keyStates.end()) ? it->second : false;
}