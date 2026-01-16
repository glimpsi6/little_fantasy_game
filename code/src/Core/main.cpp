#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "Entities/Player.h"
#include "Entities/Npc.h"
#include "Core/Game.h"
#include "World/Map.h"
#include "World/Collisions.h"

int main() {
    const int MAP_WIDTH = 40;
    const int MAP_HEIGHT = 30;
    ResourceManager resourceMn;
    InputManager inputMn;
    std::vector<std::shared_ptr<Character>> characters;
    resourceMn.loadResource(IdnLocation::CASTLE);
    Map map("trone_tiles", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE, resourceMn);
    Collisions collis(map);
    
    float currentFrame = 0; //хранит текущий кадр
	sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	Player p(310, 360, resourceMn, 16, 16, inputMn, collis);
    characters.push_back(std::make_shared<Player>(p));
    Npc npc(310, 200, resourceMn, 16, 16, collis);
    characters.push_back(std::make_shared<Npc>(npc));
    
    
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

        inputMn.update();
		p.handleInput(time, currentFrame);
		p.update(time);
        npc.update(time);
		window.setView(p.getView());
        
        map.drawFloorLatyer(window);
        map.drawWallsLatyer(window);
        p.drawEntity(window);
        npc.drawEntity(window);
        map.drawObjectsLatyer(window);
        
        window.display();
    }
    
    resourceMn.unloadResource();

    return 0;
}