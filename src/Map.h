#pragma once
#include <string>
#include <map>
#include <vector>

class Vector2D;

class Map {
public:
	Map(std::string tID, int mS, int tS);
	~Map();

	void loadMap(std::string filePath, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int xPos, int yPos);

	void clearGrid();
	char getGrid(int row, int col);		// returns the values at the row/col of the grid
	Vector2D getSpawn(int adjacent, char type);
	void printGrid();

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaleSize;

	int rows;
	int columns;

	// array { map(bool isMap, bool true/false), map(true means terrain, true means walkable), map(false means interactable object, true means active) }
	
	char grid[25][25];
	std::map<int, int> collisionMap;
};
