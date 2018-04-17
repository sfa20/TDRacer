#pragma once

#include <SFML/Graphics.hpp>
#include <maths.h>
#include <memory>
#include <string>
#include <vector>

#define ls LevelSystem

class LevelSystem {
public:
	static void loadLevelFile(const std::string&, float tileSize = 100.0f);
	static void unload();
	static void render(sf::RenderWindow& window);

	//added
//	Sprite sprite;

	typedef unsigned char Tile;

	enum TILES {
		//Top
		//Right
		//Left
		//Bottom
		//Track
		//Corner1
		//Corner2
		//Corner3
		//Corner4

		//Top
		//Right
		//Left
		//Bottom
		//Track
		//Corner1
		//Corner2
		//Corner3
		//Corner4

		TOP = 'p',
		LEFT = 'l', //this is an L
		CHECKPOINT1 = '1',
		RIGHT = 'r',
		CHECKPOINT3 = '3',	
		BOTTOM = 'b',
		TRACK = 't',
		CHECKPOINT2 = '2',
		CORNER1 = 'c',
		CORNER2 = 'd',
		CORNER3 = 'e',
		CORNER4 = 'f',
		STARTLEFT = '<',
		STARTRIGHT = '>',
		START = 's',
		END = 'q',
		GRASS = 'g',
		WALL = 'w',
		WAYPOINT = '+',
		REDTENT = 'v',
		BLUETENT = 'z',
		TREEL = 'x',
		STANDUP = 'i',
		STANDDWN = 'o'
	};

	static Tile getTile(sf::Vector2ul);

	static Tile getTileAt(sf::Vector2f);

	static bool isOnGrid(sf::Vector2f);

	static size_t getWidth();

	static size_t getHeight();

	static sf::Vector2f getTilePosition(sf::Vector2ul);

	static std::vector<sf::Vector2ul> findTiles(Tile);

	static sf::Color getColor(Tile t);

	static void setColor(Tile t, sf::Color c);

	static void setOffset(const sf::Vector2f& _offset);

	static const sf::Vector2f& getOffset();

	static float getTileSize();

protected:
	static std::unique_ptr<Tile[]> _tiles;
	static size_t _width;
	static size_t _height;
	static sf::Vector2f _offset;

	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

	static void buildSprites(bool optimise = true);

	static float _tileSize; // for rendering
	static std::map<Tile, sf::Color> _colours;

private:
	LevelSystem() = delete;

	~LevelSystem() = delete;
};