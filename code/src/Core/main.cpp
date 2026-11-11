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
#include "Systems/Frame.h"

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

    std::vector<std::shared_ptr<Npc>> npcs;

	auto p = std::make_shared<Player>(310, 360, resourceMng, 13, 16, inputMn, collis);
    map.addEntity(p);

    auto king = std::make_shared<Npc>("king", 310, 137, resourceMng, 20, 32, inputMn, collis);
    map.addEntity(king);
    npcs.push_back(king);

    auto npc = std::make_shared<Npc>("npc", 305, 250, resourceMng, 13, 14, inputMn, collis);
    map.addEntity(npc);
    npcs.push_back(npc);

    Frame fr(resourceMng);

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

        if(state == GameState::Playing) {
            p->handleInput(time, currentFrame);
            map.update(time);
        }
            
        window.setView(p->getView());
        map.drawFloorLayer(window);
        map.drawWallsLayer(window);
        map.drawEntities(window);
        map.drawFringeLayer(window);

        //ниже UI отрисовка
        window.setView(window.getDefaultView()); 
        fr.drawInterface(window);
    
        if(state == GameState::Dialogue) {
            for(auto n : npcs) {
                if(n->getDialogueStatus()) {
                    n->updateDialogue();
                    n->drawDialogue(window);
                    break;
                }
            }
        }

        window.display();
    }
    
    resourceMng.unloadResource();

    return 0;
}