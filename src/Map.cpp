#include "Map.h"
#include "Game.h"
#include <fstream>
#include <string>
#include "ECS\ECS.h"
#include "ECS\Components.h"
#include "Game.h"
#include "Vector2D.h"

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

	rows = sizeY;
	columns = sizeX;

	for (int y = 0; y < sizeY; y++)		// for each row, iterate through all the columns
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(index);
			srcY = atoi(&index) * tileSize;
			//grid.emplace(/*true, true*/);		// walkable terrain
			
			mapFile.get(index);
			srcX = atoi(&index) * tileSize;
			//grid.emplace(true, true);		// walkable terrain
			grid[x][y] = 't';

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
				tCol.addComponent<ColliderComponent>("terrain", x * scaleSize, y * scaleSize, scaleSize, false);
				tCol.addGroup(Game::groupColliders);
				//grid.emplace(true, false);		// collision/invisible wall/barrier/unwalkable terrain
				grid[x][y] = 'c';
				collisionMap.emplace(x, y);
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

char Map::getGrid(int row, int col)
{
	/*return grid[((row - 1) * columns) + col];*/
	return grid[row][col];
}

Vector2D Map::getSpawn(int adjacent, char type)
{
	//switch (type) {
	//case 'c':
	//	std::map<int, int>::iterator it;
	//	for (it = collisionMap.begin(); it != collisionMap.end(); it++)
	//	{
	//		int x = it->first;
	//		int y = it->second;

	//		// checks if corner
	//		bool up = collisionMap.contains(x+1, y);
	//		bool down;
	//		bool left;
	//		bool right;

	//	}
	//	break;
	//}
	std::map<int, int>::iterator it;
	for (it = collisionMap.begin(); it != collisionMap.end(); it++)
	{
		return Vector2D(it->first * 32 * 4, it->second * 32 * 4);
	}
}

void Map::clearGrid()
{
	/*grid.clear();*/
	memset(grid, 0, sizeof(grid[0][0]) * 10 * 10);
}

void Map::printGrid()
{
	int rows = sizeof(grid) / sizeof(grid[0]);
	int columns = sizeof(grid[0]) / sizeof(grid[0][0]);

	for (int col = 0; col < columns; col++)
	{
		for (int row = 0; row < rows; row++)
		{
			std::cout << grid[row][col] << ", ";
		}
		std::cout << std::endl;
	}
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