#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

/*---------------------------------------------------------------------------------------*/

/*! \brief Класс обработки ввода*/
class InputManager {
public:
    /*! \brief Функция обновления состояний вводимых в данный момент клавиш*/
    void update();
    /*! \brief Функция проверки нажатия клавиши в данный момент*/
    /*! \param key значение клавиши*/
    /*! \return true - клавиша нажата, false - клавиша не нажата*/
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isKeyJustPressed(sf::Keyboard::Key key) const;

private:
    /*! \brief Хранилище состояний клавиш*/
    std::unordered_map<sf::Keyboard::Key, bool> m_keyStates;
    std::unordered_map<sf::Keyboard::Key, bool> m_prevKeyStates;
};

/*---------------------------------------------------------------------------------------*/

#endif // INPUTMANAGER_H