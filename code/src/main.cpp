#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "Player.h"
#include "Game.h"
#include "Map.h"
#include "Collisions.h"

int main() {
    const int MAP_WIDTH = 40;
    const int MAP_HEIGHT = 30;
    ResourceManager resManager;
    InputManager inManager;
    resManager.loadResource(IdnLocation::CASTLE);
    Map map("trone_tiles", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE, resManager);
    Collisions collis(map);
    
    float currentFrame = 0; //хранит текущий кадр
	sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	Player p(310, 360, resManager, 16, 16, inManager, collis);
    
    // Главный игровой цикл
    while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);

        inManager.update();
		p.handleInput(time, currentFrame);
		p.update(time);
		window.setView(p.getView());
        
        map.drawFloorLatyer(window);
        map.drawWallsLatyer(window);
        window.draw(p.getSprite());
        map.drawObjectsLatyer(window);
        
        window.display();
    }
    
    resManager.unloadResource();

    return 0;
}