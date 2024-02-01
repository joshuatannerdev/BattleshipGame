#pragma once

static const unsigned int gridWidth = 12;
static const unsigned int gridHeight = 8;

enum GridType
{
	EMPTY,
	MISS,
	HIT,
	SHIP,

	GRIDTYPE_COUNT
};

class Grid
{
public:
	Grid();
	~Grid();

	void Draw( int startPosX, int startPosY ) const;

private:
	GridType m_gridTypes[gridWidth][gridHeight];
};

