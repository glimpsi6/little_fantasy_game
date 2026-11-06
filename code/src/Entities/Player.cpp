#include "Entities/Player.h"

Player::Player(float X, float Y, ResourceManager& resManager, 
               int W, int H, InputManager& inputMng, Collisions& collis)
               : Character(X, Y, resManager, W, H, inputMng, collis)
{
    _view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    setupSprite();
}

void Player::reset()
{
    _coord.x = 70; //надо в каком нибудь классе менеджере сделать дефолтные координаты
    _coord.y = 288;
    _sprite.setPosition(_coord.x, _coord.y);
    getPlayerView();
}

void Player::handleInput(float time, float& currentFrame)
{
    if (_inputMng.isKeyPressed(sf::Keyboard::Left) || _inputMng.isKeyPressed(sf::Keyboard::A)) {
        setDirection(Direction::LEFT);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2; 
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 16, _w, _h));
    }

    if (_inputMng.isKeyPressed(sf::Keyboard::Right) || _inputMng.isKeyPressed(sf::Keyboard::D)) {
        setDirection(Direction::RIGHT);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 32,  _w, _h));
    }

    if (_inputMng.isKeyPressed(sf::Keyboard::Up) || _inputMng.isKeyPressed(sf::Keyboard::W)) { 
        setDirection(Direction::UP);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 48,  _w, _h));
    }

    if (_inputMng.isKeyPressed(sf::Keyboard::Down) ||_inputMng.isKeyPressed(sf::Keyboard::S)) {
        setDirection(Direction::DOWN);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 0,  _w, _h));
    }

    getPlayerView();
}

void Player::setupSprite()
{
    _sprite.setTexture(_resMng.getGlobalTexture("hero"));
    _sprite.setTextureRect(sf::IntRect(0, 64, _w, _h));
} 

sf::View Player::getPlayerView()
{
    float tempX = _coord.x;
    float tempY = _coord.y;

    if(_coord.x < WINDOW_WIDTH / 2)        
        tempX = WINDOW_WIDTH / 2;
    if(_coord.y < WINDOW_HEIGHT / 2)     
        tempY = WINDOW_HEIGHT / 2;
    if(_coord.y > WINDOW_HEIGHT * 2)     
        tempY = WINDOW_HEIGHT * 2;  
    if(_coord.y > WINDOW_WIDTH / 2 + WINDOW_HEIGHT / 2)    
        tempY = WINDOW_WIDTH / 2 + WINDOW_HEIGHT / 2;

    _view.setCenter(tempX, tempY);

    return _view;
}