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
    resourceMn.loadResource(IdnLocation::CASTLE);
    Map map("trone_tiles", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE, resourceMn);
    Collisions collis(map);
    
    float currentFrame = 0; //хранит текущий кадр
	sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	Player p(310, 360, resourceMn, 13, 16, inputMn, collis);

    Npc npc("npc", 310, 200, resourceMn, 13, 16, collis);
    map.loadNpc(npc);
    
    
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
        map.updateMap(time);
		window.setView(p.getView());
        
        map.drawFloorLatyer(window);
        map.drawWallsLatyer(window);
        p.drawEntity(window);
        map.drawNPC(window);
        map.drawFringeLatyer(window);
        
        window.display();
    }
    
    resourceMn.unloadResource();

    return 0;
}