#include "player.h"
#include "map.h"
#include <sstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Test");

    Player p("sleeper.png", 50, 50, 32, 32);
	Map map("../assets/map.png");

	float currentFrame = 0;//хранит текущий кадр
	sf::Clock clock;

	sf::Font font;
	font.loadFromFile("../assets/CyrilicOld.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

    while (window.isOpen())
	{
		if(p.isAlive == false) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				p.reset();
			}
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        
		window.clear();

        p.handleInput(time, currentFrame);
		p.update(time);
		window.setView(p.getView());
		map.update(window);
		
		std::stringstream ss;
		ss << "Stone score: " << p.playerScore << " | Health: " << p.health;
		text.setString(ss.str());
		text.setPosition(p.getView().getCenter().x - 165, p.getView().getCenter().y - 200);
		window.draw(text);

		if(!p.isAlive) {
			sf::Text gameOverText("Game Over\nPress Enter", font, 50);
			gameOverText.setFillColor(sf::Color::Red);
			gameOverText.setStyle(sf::Text::Bold);
			gameOverText.setPosition(p.getView().getCenter().x - 100, p.getView().getCenter().y - 25);
			window.draw(gameOverText);
			window.display();
			continue;
		}

		window.draw(p.getSprite());
		window.display();
	}
 
	return 0;
}