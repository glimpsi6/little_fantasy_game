#include "Entities/Player.h"

Player::Player(float X, float Y, ResourceManager& resManager, 
               float W, float H, InputManager& inManager, Collisions& collis)
               : Character(X, Y, resManager, W, H), _inManager(inManager), _collis(collis)
{
    _view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    setupSprite();
}

void Player::update(float time)
{
    switch (_mD.direct)
    {
    case Direction::RIGHT: _mD.dx = _mD.speed;    _mD.dy = 0;        break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
    case Direction::LEFT:  _mD.dx = -_mD.speed;   _mD.dy = 0;        break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
    case Direction::DOWN:  _mD.dx = 0;         _mD.dy = _mD.speed;   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
    case Direction::UP:    _mD.dx = 0;         _mD.dy = -_mD.speed;  break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    _coord.x += _mD.dx * time;// ускорение на время получаем смещение координат и как следствие движение
    _coord.y += _mD.dy * time;//аналогично по игреку

    _mD.speed = 0;//зануляем скорость, чтобы персонаж остановился
    _collis.interactionWithMap(_coord, _mD, _w, _h);
    _sprite.setPosition(_coord.x, _coord.y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
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
    if (_inManager.isKeyPressed(sf::Keyboard::Left) || _inManager.isKeyPressed(sf::Keyboard::A)) {
        setDirection(Direction::LEFT);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2; 
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 16, 16, 16));
    }

    if (_inManager.isKeyPressed(sf::Keyboard::Right) || _inManager.isKeyPressed(sf::Keyboard::D)) {
        setDirection(Direction::RIGHT);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 32, 16, 16));
    }

    if (_inManager.isKeyPressed(sf::Keyboard::Up) || _inManager.isKeyPressed(sf::Keyboard::W)) { 
        setDirection(Direction::UP);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 48, 16, 16));
    }

    if (_inManager.isKeyPressed(sf::Keyboard::Down) ||_inManager.isKeyPressed(sf::Keyboard::S)) {
        setDirection(Direction::DOWN);
        setSpeed(0.1);
        currentFrame += 0.004*time;
        if (currentFrame > 2) currentFrame -= 2;
        _sprite.setTextureRect(sf::IntRect(16 * int(currentFrame), 0, 16, 16));
    }

    getPlayerView();
}

void Player::setupSprite()
{
    _sprite.setTexture(_resManager.getGlobalTexture("hero"));
    _sprite.setTextureRect(sf::IntRect(0, 0, _w, _h));
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