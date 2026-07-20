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
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Little fantasy game");

	auto p = std::make_shared<Player>(310, 360, resourceMn, 13, 16, collis, inputMn);
    map.addEntity(p);

    auto npc = std::make_shared<Npc>("npc", 310, 200, resourceMn, 13, 16, collis);
    map.addEntity(npc);

    auto chest = std::make_shared<Object>("chest_mini", 312, 300, resourceMn, 16, 16);
    map.addEntity(chest);

    sf::Sprite sprite;
    sprite.setTexture(resourceMn.getGlobalTexture("interface"));
    sprite.setTextureRect(sf::IntRect(0, 16,  16, 16));

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
        sprite.setPosition(p->getCoord().x, p->getCoord().y - 20);
        window.draw(sprite);

        window.display();
    }
    
    resourceMn.unloadResource();

    return 0;
}