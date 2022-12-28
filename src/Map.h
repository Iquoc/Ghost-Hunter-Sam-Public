#pragma once
#include <string>

class Map {
public:
	Map(std::string tID, int mS, int tS);
	~Map();

	void loadMap(std::string filePath, int sizeX, int sizeY);
	void addTile(int srcX, int srcY, int xPos, int yPos);

private:
	std::string textureID;
	int mapScale;
	int tileSize;
	int scaleSize;
};
