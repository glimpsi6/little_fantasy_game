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
#include "Entities/Object.h"
#include "Core/Game.h"
#include "World/Map.h"
#include "World/Collisions.h"
#include "Systems/InteractiveIcon.h"

int main() {
    const int MAP_WIDTH = 40;
    const int MAP_HEIGHT = 30;
    ResourceManager resourceMng;
    InputManager inputMn;
    resourceMng.loadResource(IdnLocation::CASTLE);
    Map map("trone_tiles", MAP_WIDTH, MAP_HEIGHT, TILE_SIZE, resourceMng);
    Collisions collis(map);
    
    float currentFrame = 0; //хранит текущий кадр
	sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Little fantasy game");

	auto p = std::make_shared<Player>(310, 360, resourceMng, 13, 16, collis, inputMn);
    map.addEntity(p);

    auto npc = std::make_shared<Npc>("npc", 310, 200, resourceMng, 13, 16, collis);
    map.addEntity(npc);

    // auto chest = std::make_shared<Object>("chest_mini", 312, 300, resourceMng, 16, 16);
    // map.addEntity(chest);

    // InteractiveIcon eIcon(resourceMng);

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
		p->handleInput(time, currentFrame);
        map.update(time);
		window.setView(p->getView());
        
        map.drawFloorLayer(window);
        map.drawWallsLayer(window);
        map.drawEntities(window);
        map.drawFringeLayer(window);

        // eIcon.setInteractiveZone(true);
        // eIcon.setPosition(p->getCoord());
        // eIcon.drawInterface(window);

        window.display();
    }
    
    resourceMng.unloadResource();

    return 0;
}