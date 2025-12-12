#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 

inline sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0         0        s   0         h     0",
	"0   s 0        d       0     s         0",
	"0 ddd 0  d     000000000               0",
	"0000000                    d           0",
	"0             s                        0",
	"0    h                                 0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};

class Map {
public:
	Map(sf::String F);
	~Map() {}
	void update(sf::RenderWindow &window);

private:
	sf::String File;
	sf::Image map_image;
	sf::Texture map;
	sf::Sprite s_map;
};

#endif // MAP_H