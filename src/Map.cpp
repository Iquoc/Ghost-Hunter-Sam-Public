#include "Map.h"
#include "Game.h"
#include <fstream>
#include <string>
#include "ECS\ECS.h"
#include "ECS\Components.h"
#include "Game.h"

extern Manager manager;		// extern makes this the same variable as in Game.cpp

Map::Map(std::string tID, int mS, int tS) : textureID(tID), mapScale(mS), tileSize(tS)
{
	scaleSize = mS * tS;
}
Map::~Map() {
}

void Map::loadMap(std::string filePath, int sizeX, int sizeY)
{
	char index;
	std::fstream mapFile;
	mapFile.open(filePath);

	int sc = 4;

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)		// for each row, iterate through all the columns
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(index);
			srcY = atoi(&index) * tileSize;
			mapFile.get(index);
			srcX = atoi(&index) * tileSize;
			addTile(srcX, srcY, x * scaleSize, y * scaleSize);
			mapFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');		// ignores the next character; which is a COMMA (,)
		}
		mapFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(index);
			if (index == '1')
			{
				auto& tCol(manager.addEntity());
				tCol.addComponent<ColliderComponent>("terrain", x * scaleSize, y * scaleSize, scaleSize);
				tCol.addGroup(Game::groupColliders);
			}
			mapFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
		}
		mapFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	mapFile.close();
}

void Map::addTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, textureID);
	tile.addGroup(Game::groupMap);
}

//void Map::drawMap()
//{
//	int type = 0;
//
//	for (int row = 0; row < 20; row++) {
//		for (int col = 0; col < 25; col++) {
//			type = map[row][col];
//			destRect.x = col * 32;
//			destRect.y = row * 32;
//
//			switch (type) {
//			case 0:
//				TextureManager::draw(floor, srcRect, destRect);
//				break;
//			case 1:
//				TextureManager::draw(wall, srcRect, destRect);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}