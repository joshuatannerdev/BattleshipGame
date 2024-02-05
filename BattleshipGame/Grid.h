#pragma once

#include "Vector.h"

static const unsigned int g_gridWidth = 10;
static const unsigned int g_gridHeight = 10;

enum GridType
{
	EMPTY,
	MISS,
	HIT,
	SHIP,
	SHIP_SUNK,

	GRIDTYPE_COUNT
};

/// <summary>
/// Grid class for tracking ships, hits, misses etc.
/// </summary>
class Grid
{
public:
	Grid( int _xDrawOffset, bool _hideShipGridType );
	~Grid();

	void Draw() const;
	void SetGridTypeAtPos( const Vector2dInt& _pos, GridType _gridType );
	GridType GetGridTypeAtPos( const Vector2dInt& _pos ) const;
	bool IsPosInGridBounds( const Vector2dInt& _pos ) const {
		return ( _pos.x >= 0 && _pos.x < g_gridWidth ) && ( _pos.y >= 0 && _pos.y < g_gridHeight ); }	

private:
	Grid();

private:
	GridType m_gridTypes[g_gridHeight][g_gridWidth];
	int m_xDrawOffset;
	bool m_hideShipGridType;
};

