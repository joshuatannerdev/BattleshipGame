#pragma once

#include "Vector.h"

static const unsigned int gridWidth = 12;
static const unsigned int gridHeight = 8;

enum GridType
{
	EMPTY,
	MISS,
	HIT,
	SHIP,
	SHIP_SUNK,

	GRIDTYPE_COUNT
};

class Grid
{
public:
	Grid();
	~Grid();

	void Draw( int _startPosX, int _startPosY ) const;
	void SetGridTypeAtPos( int _posX, int _posY, GridType _gridType );
	GridType GetGridTypeAtPos( int _posX, int _posY ) const;
	bool IsPosInGridBounds( Vector2dInt _pos ) const {
		return ( _pos.x >= 0 && _pos.x < gridWidth ) && ( _pos.y >= 0 && _pos.y < gridHeight ); }	

private:
	GridType m_gridTypes[gridHeight][gridWidth];
};

