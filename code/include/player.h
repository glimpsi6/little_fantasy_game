#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "map.h"

enum Direction
{
    RIGHT, //0
    LEFT, //1
    DOWN, //2
    UP //3
};

class Player { // класс Игрока
public:
    Player(sf::String F, float X, float Y, float W, float H);
    ~Player(){}

    int playerScore;
    int health;
    bool isAlive;

    void update(float time);
    void handleInput(float time, float& currentFrame);
    sf::Sprite getSprite() { return sprite; }
    sf::View getView() { return view; }
    void reset();

private:
    sf::String File;
    sf::Image Image;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::View view;
    int direct;
    float x, y; //координаты игрока х и у
    float w, h; // ширина высота
    float dx, dy, speed; // ускорение (по х и по у), сама скорость

    void loadTextures();
    void setupSprite();
    void setDirection(enum Direction d) { direct = d; }
    void setSpeed(float s) { speed = s; }
    sf::View getPlayerView(float x, float y);
    void interactionWithMap();
};

#endif // PLAYER_H