#include "map.h"

Map::Map(sf::String F)
    : File(F)
{
	map_image.loadFromFile(File);
	map.loadFromImage(map_image);
	s_map.setTexture(map);
}

void Map::update(sf::RenderWindow &window)
{
    for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
			if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
			if (TileMap[i][j] == '0') s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
			if (TileMap[i][j] == 'd') s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
			if (TileMap[i][j] == 'h') s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
 
			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
 
			window.draw(s_map);//рисуем квадратики на экран
		}
}