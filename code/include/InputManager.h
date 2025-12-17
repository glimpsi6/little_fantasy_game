#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

class InputManager {
public:
    void update();
    bool isKeyPressed(sf::Keyboard::Key key) const;

private:
    // Хранилище состояний
    std::unordered_map<sf::Keyboard::Key, bool> m_keyStates;
};

#endif // INPUTMANAGER_H