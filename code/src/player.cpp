#include "player.h"
#include <iostream>

Player::Player(sf::String F, float X, float Y, float W, float H)
        : File(F), x(X), y(Y), w(W), h(H), dx(0), dy(0), speed(0), 
        direct(0), playerScore(0), health(100), isAlive(true)
{
    view.reset(sf::FloatRect(0, 0, 640, 480));
    loadTextures();
    setupSprite();
}

void Player::interactionWithMap()
{
    for (int i = y / 32; i < (y + h) / 32; i++) {
        for (int j = x / 32; j < (x + w) / 32; j++) {
            if (TileMap[i][j] == '0') {
                if (dy > 0) y = i * 32 - h;   // столкновение снизу
                if (dy < 0) y = i * 32 + 32;  // сверху
                if (dx > 0) x = j * 32 - w;   // справа
                if (dx < 0) x = j * 32 + 32;  // слева
            }

            if (TileMap[i][j] == 's') {
                playerScore++;
                TileMap[i][j] = ' ';
            }

            if (TileMap[i][j] == 'd') {
                health -= 40;
                TileMap[i][j] = ' ';
                if (health <= 0) {
                    health = 0;
                    isAlive = false;
                }
            }

            if (TileMap[i][j] == 'h') {
                health += 20;
                if (health > 100) health = 100;
                TileMap[i][j] = ' ';
            }
        }
    }
}

void Player::update(float time)
{
    if(!isAlive) return;

    switch (direct)
    {
    case Direction::RIGHT: dx = speed; dy = 0;  break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
    case Direction::LEFT:  dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
    case Direction::DOWN:  dx = 0; dy = speed;  break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
    case Direction::UP:    dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
    y += dy*time;//аналогично по игреку

    speed = 0;//зануляем скорость, чтобы персонаж остановился.
    interactionWithMap();
    sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
}

void Player::loadTextures() 
{
    Image.loadFromFile("../assets/" + File);
    texture.loadFromImage(Image);
}

void Player::setupSprite() 
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Player::handleInput(float time, float& currentFrame)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
        setDirection(Direction::LEFT);
        setSpeed(0.1);
        currentFrame += 0.005*time;
        if (currentFrame > 2) currentFrame -= 2; 
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 32, 32, 32));
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
        setDirection(Direction::RIGHT);
        setSpeed(0.1);
        currentFrame += 0.005*time;
        if (currentFrame > 2) currentFrame -= 2;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 64, 32, 32));
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) { 
        setDirection(Direction::UP);
        setSpeed(0.1);
        currentFrame += 0.005*time;
        if (currentFrame > 2) currentFrame -= 2;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 96, 32, 32));
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
        setDirection(Direction::DOWN);
        setSpeed(0.1);
        currentFrame += 0.005*time;
        if (currentFrame > 2) currentFrame -= 2;
        sprite.setTextureRect(sf::IntRect(32 * int(currentFrame), 0, 32, 32));
    }

    getPlayerView(x, y);
}

sf::View Player::getPlayerView(float x, float y)
{
    float tempX = x;
    float tempY = y;

    if(x < 320)
        tempX = 320;
    if(x > 960)
        tempX = 960;
    if(y < 240)
        tempY = 240;    
    if(y > 560)    
        tempY = 560;

    view.setCenter(tempX, tempY);

    return view;
}

void Player::reset() 
{
    health = 100;
    playerScore = 0;
    isAlive = true;
    x = 50;
    y = 50;
    sprite.setPosition(x, y);
    getPlayerView(x, y);
}